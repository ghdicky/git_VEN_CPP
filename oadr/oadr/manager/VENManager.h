/*
 * VENManager.h
 *
 *  Created on: Sep 15, 2014
 *      Author: dupes
 */

#ifndef VENMANAGER_H_
#define VENMANAGER_H_

#include "VENManagerConfig.h"

#include "../ven/VEN2b.h"
#include "../ven/http/HttpCurl.h"

#include "../request/report/ReportHelper.h"

#include "../helper/RandomHex.h"
#include "../helper/thread/IRun.h"
#include "../helper/thread/ThreadRunner.h"

#include "eventmanager/EventManager.h"
#include "reportmanager/ReportManager.h"
#include "reportmanager/ISendReport.h"

#include "../scheduler/Scheduler.h"

#include "IVENManager.h"
#include "IOADRExceptionService.h"

#include <thread>
#include <condition_variable>
#include <mutex>

/* Use global variable global_optType which is defined in global_variable.h */
/* #include "../../../samplevenmanager/samplevenmanager/global_variable.h" */
/* Note that global_variable.h has already been included in EventManager.h; so do not need to include here */

/* Include <string> for string comparison */
#include <string>

/* Include <unistd.h> for sleep() method */
#include <unistd.h> 

/* include "MyDB.h" and <iostream>*/
#include "../../../mysqlmgr/MyDB.h"
#include <iostream>

/* Use global variable global_optType which is defined in global_variable.h */
#include "../../../samplevenmanager/samplevenmanager/global_variable.h"

// include globalDB.h to use the global database 
//#include "../../../mysqlmgr/globalDB.h"

// declare global database 
//extern MyDB db;

class VENManager : public ISendCreatedEvent, public ISendReport, public IVENManager
{
private:
	unique_ptr<VEN2b> m_ven;
	unique_ptr<Scheduler> m_scheduler;
	unique_ptr<EventManager> m_eventManager;
	unique_ptr<ReportManager> m_reportManager;

	IReportService *m_reportService;

	IOADRExceptionService *m_exceptionService;

        condition_variable m_condition;
        mutex m_mutex;

	bool m_shutdown;
        
        
        /* declared a string that will take the input optType */
        string input_optType;

        /* declared a string that will represent the existing opt status */
        string existing_opt_status = "OptIn";  
        
        /* declared a string that will take the input optFunction */
        string input_optFunction;
        
        /* declared a bool that represent if it is in selectOptType method */
        bool in_optType_menu;
        
        
        /* declare a MyDB object */
        //MyDB db;
        
        
        
	virtual void sendCreatedEvent(string responseCode, string responseDescription, string requestID, oadr2b::ei::eventResponses::eventResponse_sequence &eventResponses);

	virtual void sendUpdateReport(oadrUpdateReportType::oadrReport_sequence &sequence, time_t dtstart, string reportRequestID, time_t createdDateTime);
	virtual void sendCreatedReport(const set<string> &pendingReports, string requestID, string responseCode, string responseDescription);
	virtual void sendCanceledReport(const set<string> &pendingReports, string requestID, string responseCode, string responseDescription);

	VENManager(unique_ptr<VEN2b> ven, IEventService *eventService, IReportService *reportService, IOADRExceptionService *exceptionService);

	void exceptionWait();

	void poll();

	void registerReports();

	void requestEvents();

	void registerVen();

	void registerVenState();

	void pollState();
        
        /* method declaration for selectOptType() */
        void selectOptType();
        
       

public:

	virtual ~VENManager();

	static IVENManager *init(VENManagerConfig &config);

	virtual void run();

	virtual void stop();

	Scheduler *getScheduler();
        
        
       
       /* method declaration for selectOptFunction()*/
       virtual void selectOptFunction();
       
       /* method declaration for configDefaultOpt() */
       virtual string configDefaultOpt(string http_opt);
       
       /* method declaration for configVENName() */
       virtual void configVENInfo();
       
       /* method declaration for getVENInfoDB() */
       virtual string getVENInfoDB();
       
       /* method declaration for configIndividualOpt() */
       virtual string configIndividualOpt(string eventID, string individualOpt);
};

#endif /* VENMANAGER_H_ */
