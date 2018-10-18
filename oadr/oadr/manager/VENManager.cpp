/*
 * VENManager.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: dupes
 */

#include "../manager/VENManager.h"




// init() method is called first and then inside the init(), VENManager constructor new VENManager() is called later
VENManager::VENManager(unique_ptr<VEN2b> ven, IEventService *eventService, IReportService *reportService, IOADRExceptionService *exceptionService) :
	m_ven(std::move(ven)), // m_ven is object of Class VEN2b.cpp (/source_code_Folder/ven/VEN2b.cpp)
	m_reportService(reportService),
	m_exceptionService(exceptionService)
{
	m_scheduler = unique_ptr<Scheduler>(new Scheduler());

	m_eventManager = unique_ptr<EventManager>(new EventManager(
			m_scheduler.get(),
			eventService,
			this
			));

	m_reportManager = unique_ptr<ReportManager>(new ReportManager(
			m_scheduler.get(),
			reportService,
			this
			));

	m_shutdown = false;
        
        /* initialize MyDB db */
        db.initDB("localhost", "xx", "xx", "test");
        
}

/********************************************************************************/

VENManager::~VENManager()
{
}

/********************************************************************************/

void VENManager::sendCreatedEvent(string responseCode, string responseDescription, string requestID, oadr2b::ei::eventResponses::eventResponse_sequence &eventResponses)
{
	m_ven->createdEvent(responseCode, responseDescription, eventResponses);
}

/********************************************************************************/

void VENManager::sendUpdateReport(oadrUpdateReportType::oadrReport_sequence &sequence, time_t dtstart, string reportRequestID, time_t createdDateTime)
{       
        /* sequence is the content of the report, in VENImpl.cpp, */
        /* the defined report content, e.g. telemetry_usage is push back into the sequence */
	m_ven->updateReport(sequence, dtstart, reportRequestID, createdDateTime);
}

/********************************************************************************/

void VENManager::sendCreatedReport(const set<string> &pendingReports, string requestID, string responseCode, string responseDescription)
{
	m_ven->createdReport(requestID, responseCode, responseDescription, pendingReports);
}

/********************************************************************************/

void VENManager::sendCanceledReport(const set<string> &pendingReports, string requestID, string responseCode, string responseDescription)
{
	m_ven->canceledReport(requestID, responseCode, responseDescription, pendingReports);
}

/********************************************************************************/

// init() method is called first and then inside the init(), VENManager constructor new VENManager() is called later
IVENManager *VENManager::init(VENManagerConfig &config)
{
	unique_ptr<HttpCurl> http(new HttpCurl());

	http->setTimeouts(config.timeouts.connectTimeout, config.timeouts.requestTimeout);

	if (config.tls.useTls)
	{
		http->setParameters(config.tls.certPath,
				config.tls.privateKeyPath,
				config.tls.caBundlePath,
				config.tls.verifyHostname,
				config.tls.cipherList,
				config.tls.sslVersion);
	}

	unique_ptr<VEN2b> ven(new VEN2b(std::move(http),
			config.vtnURL,
			config.venName,
			config.venID,
			config.registrationID));

	ven->setOadrMessage(config.services.oadrMessage);
        
        // init() method is called first and then inside the init(), VENManager constructor new VENManager() is called later
	VENManager *venManager = new VENManager(std::move(ven),
			config.services.eventService,
			config.services.reportService,
			config.services.exceptionService);
       
        
        
	return venManager;
}

/********************************************************************************/

void VENManager::exceptionWait()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_condition.wait_for(lock, seconds(10));
}

/********************************************************************************/

void VENManager::poll()
{
	unique_ptr<Poll> poll = m_ven->poll();

	oadrPayload *response = poll->response();
        

	if (response == NULL)
	{
		stringstream s;

		s << "invalid response from poll: " << poll->responseBody() << endl;

		std::runtime_error ex(s.str());

		m_exceptionService->OnException(ex);

		return;
	}

	if (response->oadrSignedObject().oadrResponse().present())
	{
		// processMessage(response->oadrSignedObject().oadrResponse().get());
	}
	else if (response->oadrSignedObject().oadrDistributeEvent().present())
	{
		m_eventManager->manageEvents(response->oadrSignedObject().oadrDistributeEvent().get());
	}
	else if (response->oadrSignedObject().oadrCreateReport().present())
	{
		m_reportManager->manageCreateReport(response->oadrSignedObject().oadrCreateReport().get());
	}
	else if (response->oadrSignedObject().oadrRegisterReport().present())
	{
		m_ven->registeredReport(response->oadrSignedObject().oadrRegisterReport()->requestID(), "200", "OK");
	}
	else if (response->oadrSignedObject().oadrCancelReport().present())
	{
		m_reportManager->manageCancelReport(response->oadrSignedObject().oadrCancelReport().get());
	}
	else if (response->oadrSignedObject().oadrUpdateReport().present())
	{
		// Not supported
	}
	else if (response->oadrSignedObject().oadrCancelPartyRegistration().present())
	{
		// processMessage(response->oadrSignedObject().oadrCancelPartyRegistration().get());
		// TODO: what's the proper response when a cancel registration message is received?

		m_ven->clearRegistration();
	}
	else if (response->oadrSignedObject().oadrRequestReregistration().present())
	{
		m_ven->clearRegistration();
	}

}

/********************************************************************************/

void VENManager::registerReports()
{
	oadrRegisterReportType::oadrReport_sequence sequence;
        
        // OnGenerateRegisterReport() is override in Class VENImpl.cpp in (/source_code/samplevenmanager/samplevenmanager)
        // In the OnGenerateRegisterReport() function, the report capability of VEN C++ is defined as RealEnergy and RealPower
        // with periodic duration PT1M and duration PT120M
        // can add more Report components in this function
        /* sequence contains the telemetry_usage and telemetry_status contents */
	m_reportService->OnGenerateRegisterReport(sequence);
        
        /* this method will record the sequence containing content of {oadrRegisterReport} in m_registeredReport of the reportManager.cpp */
       	m_reportManager->setRegisteredReports(sequence);

	m_ven->registerReport(sequence);
}

/********************************************************************************/

void VENManager::requestEvents()
{
	unique_ptr<RequestEvent> request = m_ven->requestEvent();

	m_eventManager->manageEvents(request->response()->oadrSignedObject().oadrDistributeEvent().get());
}

/********************************************************************************/

void VENManager::registerVen()
{
	// register as an HTTP pull VEN
        // m_ven(of class VEN2b.cpp)->createPartyRegistration() call for setIDs() which will read "duration" field from
        // VTN and this value will be assigned to m_pollFrequency of m_ven and the VEN will poll period is this value
	unique_ptr<CreatePartyRegistration> createPartyRegistration = m_ven->createPartyRegistration(oadrProfileType(oadrProfileType::cxx_2_0b),
			oadrTransportType(oadrTransportType::simpleHttp), "", false, false, true);

	oadrPayload *response = createPartyRegistration->response();

	if (response == NULL || !response->oadrSignedObject().oadrCreatedPartyRegistration().present())
	{
		// TODO: throw an exception
		return;
	}
        
        

	oadrCreatedPartyRegistrationType *cpr = &response->oadrSignedObject().oadrCreatedPartyRegistration().get();

	if (cpr->eiResponse().responseCode().compare("200") != 0)
	{
		// TODO: throw an exception
		return;
	}
        
        // after VTN sends the oadrCreatedPartyRegistration, VEN is registered
        // oadrCreatedPartyRegistration from VTN contains the assigned VEN ID and this should be updated to the MySQL database
        // until now everything is correct and the venName, venID and vtnURL in SQL will be updated
     
        configVENInfo();
        
        
        /* VEN to send {oadrRegisterReport} to VTN */
	registerReports();

	poll();

	requestEvents();
}

/********************************************************************************/

void VENManager::registerVenState()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	while (!m_shutdown)
	{
		registerVen();

		if (m_ven->isRegistered())
			return;
                
                //Specify the polling interval of VEN, here is to poll after 10 seconds for the 1st request from VEN
		m_condition.wait_for(lock, seconds(10));
	}
}

/********************************************************************************/

void VENManager::pollState()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	while (!m_shutdown)
	{
		poll();

		if (!m_ven->isRegistered())
			break;

		m_condition.wait_for(lock, seconds(m_ven->pollFrequencyInSeconds()));
	}
}

/********************************************************************************/

void VENManager::run()
{
	ThreadRunner schedulerThread(m_scheduler.get());

	schedulerThread.start();

	while (!m_shutdown)
	{
		try
		{
			if (!m_ven->isRegistered())
                            /* if the VEN is not yet registered in VTN, method registerVenState() will be called; */
                            /* VEN will then send {oadrCreatePartyRegistration} and {oadrRegisterReport} to VTN */
				registerVenState();
			else
				pollState();
		}
		catch (CurlException &ex)
		{
			m_exceptionService->OnCurlException(ex);
			exceptionWait();
		}
		catch (exception &ex)
		{
			m_exceptionService->OnException(ex);
			exceptionWait();
		}
	}
}

/********************************************************************************/

void VENManager::stop()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_shutdown = true;

	m_condition.notify_all();
}

/********************************************************************************/

Scheduler *VENManager::getScheduler()
{
	return m_scheduler.get();
}

/********************************************************************************/

void VENManager::selectOptType()
{
      
    while (in_optType_menu)
    {
    /*cout << "I am thread 1 and waiting for input indefinitely. " << endl; */
    
        if (global_optType == oadr2b::ei::OptTypeType::optIn)
        /*if (global_optType.compare("Opt_In") == 0)*/
        {
            
            existing_opt_status = "Opt_In";
              
        } else if (global_optType == oadr2b::ei::OptTypeType::optOut)
        /*else if (global_optType.compare("Opt_Out") == 0)*/
        {
            
            existing_opt_status = "Opt_Out";
        
        }
        
        cout << "\nDefault Opt type menu" << endl;
        cout << "Existing Opt status is: " << existing_opt_status << " " << endl;  
        cout << "Please Enter:" << endl;
        cout << "-Opt_In (automatically opt in for all incoming DR events)" << endl;
        cout << "-Opt_Out (automatically opt out for all incoming DR events)" << endl;
        cout << "-Exit (return to Opt Service function menu)" << endl;
    
        /* Get the input for optType and store in input_optType */
        cin >> input_optType;
    
        /* If the input is neither Opt_In nor Opt_Out, break */
        if (input_optType.compare("Opt_In") == 0){
            /* assign value Opt_In to global_optType */
            global_optType = oadr2b::ei::OptTypeType::optIn;
            /*global_optType = "Opt_In";*/
            
            cout << "Successful! You have selected Opt_In." << endl;
         
        } else if (input_optType.compare("Opt_Out") == 0){
            /* assign value Opt_Out to global_optType */
            global_optType = oadr2b::ei::OptTypeType::optOut;
            /*global_optType = "Opt_Out";*/
            
            cout << "Successful! You have selected Opt_Out." << endl;
            
        } else if (input_optType.compare("Exit") == 0){
            
            cout << "Back to Opt Service function menu." << endl;
            
            /* wait for 3 seconds before return to Opt Service menu */
            sleep(3);
            
            in_optType_menu = false;
        } else {
        
            /* If neither Opt_In nor Opt_Out is input, output a wrong message */
            cout << "\nWrong input! Please try again.\n \n";
            
            /* wait for 2 seconds before return to the existing Opt Type menu */
            sleep(2);
        }
    }
    
} 


void VENManager::selectOptFunction()
{

    while(1)
    {
    
        cout << "\nPlease select the Opt Service function 1, 2 or 3:" << endl;
        cout << "1. Default Opt type (Opt_In or Opt_Out) for incoming DR events" << endl;
        cout << "2. Create Opt type for specific events" << endl;
        cout << "3. Create Opt schedule" << endl;
        
        
        cin >> input_optFunction;
        
        if (input_optFunction.compare("1") == 0)
        {
        
            /* Select the Default Opt Type function */
            in_optType_menu = true;
            selectOptType();
        
        }
    
    
    
    
    
    }

    

/*void VENManager::runHTTPServer(){ */

    /*while(1)*/
    


/*}*/ 




}


/* this configDefaultOpt() function will be called once the Pistache HTTP server receives 
   HTTP POST Request with content of defaultOptMode */
string VENManager::configDefaultOpt(string http_opt){
    
    cout << "Calling venManager->configDefaultOpt(string http_opt)" << endl;
    
    if (http_opt.compare("OptIn") == 0) {
        
        //if OptIn is received from the web GUI, 
        //change the global_optType to oadr2b::ei::OptTypeType::optIn
        //make the existing status as optIn
        global_optType = oadr2b::ei::OptTypeType::optIn;
        existing_opt_status = "OptIn";
        
        //update the field defaultopt in table vendefaultopt in MySQL
        db.updateDefaultOptSQL("UPDATE vendefaultopt SET defaultopt='" + existing_opt_status + "' WHERE recordID=1");
        
               
        
    } else if (http_opt.compare("OptOut") == 0) {
        
        //if OptIn is received from the web GUI, 
        //change the global_optType to oadr2b::ei::OptTypeType::optIn
        //make the existing status as optIn
        global_optType = oadr2b::ei::OptTypeType::optOut;
        existing_opt_status = "OptOut";
        
        //update the field defaultopt in table vendefaultopt in MySQL
        db.updateDefaultOptSQL("UPDATE vendefaultopt SET defaultopt='" + existing_opt_status + "' WHERE recordID=1");   
        
    }
    
    // return the defaultopt value from MySQL
    return db.getDefaultOptSQL();

}



/* this configVENName() function will be called when init() method is called */
void VENManager::configVENInfo(){
    
    string command;
   
    
    cout << "Calling venManager->configVENInfo()" << endl;
    
    command = "UPDATE veninfo SET venName = '" + m_ven->venName() + "', " +
                                          "vtnURL = '" + m_ven->vtnURL() + "', " +
                                          "venID = '"  + m_ven->venID() + "', " +
                                          "vtnID = '"  + m_ven->vtnID() + "', " + 
                                          "pollFrequency = '" + std::to_string(m_ven->pollFrequencyInSeconds()) + "' WHERE recordID=1";
      
    //command = "UPDATE veninfo SET venName = '" + m_ven->venName() + "', vtnURL = '" + vtn_url + "', venID = '" + m_ven->venID() + "', vtnID = '" m_ven->+ "' WHERE recordID = 1";
    
    
    //call db.updateVENInfoSQL() and db.updateDefaultOptSQL() every time the VEN runs 
    db.updateVENInfoSQL(command);
    db.updateDefaultOptSQL("UPDATE vendefaultopt SET defaultopt= 'OptIn' WHERE recordID=1"); // the dafault opt when VEN runs is OptOut
           
}


/* this configVENName() function will be called when init() method is called */
string VENManager::getVENInfoDB(){
    
    
    return "later";
}


/* this configIndividualOpt() function will be called once the Pistache HTTP server receives 
 * HTTP Post Request with content of eventID and individualOptMod */
string VENManager::configIndividualOpt(string eventID, string individualOptValue){
    
    m_eventManager->manageIndividualEventOpt(eventID, individualOptValue);
    
    string individualOptValueDB = db.getIndividualOptSQL(eventID);
    
    string message = "{\"eventID\":" + eventID + ", \"individualOptMode\":" + individualOptValueDB + "}"; 
    
    return message;
        
}



