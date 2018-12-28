/*
 * EventManager.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: dupes
 */

#include "../../helper/globaltime/GlobalTime.h"
#include "EventManager.h"

#include "../../helper/ISO8601Duration.h"
#include "../../helper/DateTimeConverter.h"

#include "../../request/Oadr2bHelper.h"

#include <sstream>

#include "job/event/JobEventComplete.h"
#include "job/event/JobEventIntervalStart.h"
#include "job/event/JobEventStart.h"

// include <iostream> for std::cout (printf) function: added by Hao
#include <iostream>
#include <ratio>





using namespace oadr2b::oadr;
using namespace oadr2b::ei;
using namespace payloads;
using namespace stream;

/********************************************************************************/

const string EventManager::C_EVENT = "event.";

const string EventManager::C_START = ".start";
const string EventManager::C_COMPLETE = ".complete";

const string EventManager::C_INTERVAL = ".interval";

/********************************************************************************/

EventManager::EventManager(IScheduler *scheduler, IEventService *service, ISendCreatedEvent *sendCreatedEvent) :
	m_scheduler(scheduler),
	m_service(service),
	m_sendCreatedEvent(sendCreatedEvent)
{
}

/********************************************************************************/

EventManager::~EventManager()
{
}

/********************************************************************************/

void EventManager::removeSchedule(const string &eventID)
{
	auto itr = m_jobIDs.find(eventID);

	if (itr == m_jobIDs.end())
		return;


	for (auto &id : itr->second)
	{
		m_scheduler->removeJob(id);
	}

	m_jobIDs.erase(itr);
}

/********************************************************************************/

void EventManager::scheduleEventStart(const string &eventID, const oadr2b::oadr::oadrEvent *event, time_t dtstart)
{
	time_t now = GlobalTime::Instance()->now();

	if (now >= dtstart)
	{
		string duration = event->eiEvent().eiActivePeriod().properties().duration().duration();
		int durationInSeconds = ISO8601Duration::TotalSeconds(duration);

		// The event is active; send a start message
		// durationInSeconds == 0 means the event runs forever
		if (dtstart + durationInSeconds > now)
		{
			m_service->OnEventStart(eventID, event, durationInSeconds - (now - dtstart));
		}
		else if (durationInSeconds == 0)
		{
			m_service->OnEventStart(eventID, event, 0);
		}

		return;
	}

	string jobID = string(C_EVENT + eventID + C_START);

	m_jobIDs[eventID].push_back(jobID);

	unique_ptr<JobEventStart> jobEventStart(new JobEventStart(m_service, event));
	unique_ptr<SchedulerJob> schedulerJob = SchedulerJob::CreateOnetimeSchedulerJob(std::move(jobEventStart), jobID, dtstart);

	m_scheduler->addJob(std::move(schedulerJob));
}

/********************************************************************************/

void EventManager::scheduleEventComplete(const string &eventID, const oadr2b::oadr::oadrEvent *event, time_t dtend)
{
	time_t now = GlobalTime::Instance()->now();

	if (now > dtend)
		return;

	string jobID = string(C_EVENT + eventID + C_COMPLETE);

	m_jobIDs[eventID].push_back(jobID);

	unique_ptr<JobEventComplete> jobEventStart(new JobEventComplete(m_service, event));
	unique_ptr<SchedulerJob> schedulerJob = SchedulerJob::CreateOnetimeSchedulerJob(std::move(jobEventStart), jobID, dtend);

	m_scheduler->addJob(std::move(schedulerJob));
}

/********************************************************************************/

void EventManager::scheduleEventIntervalStart(const string &eventID, const oadr2b::oadr::oadrEvent *event,
		const oadr2b::ei::eiEventSignalType *eventSignal, string uid, float payload, time_t dtstart, int durationInSeconds)
{
	time_t now = GlobalTime::Instance()->now();

	if (now >= dtstart)
	{
		// The event interval is active
		if (dtstart + durationInSeconds > now)
		{
			m_service->OnEventIntervalStart(eventID, event, eventSignal, uid, payload, dtstart, durationInSeconds - (now - dtstart));
                }
		else if (durationInSeconds == 0)
		{
			m_service->OnEventIntervalStart(eventID, event, eventSignal, uid, payload, dtstart, durationInSeconds);
		}

		return;
	}

	stringstream jobID;

	jobID << C_EVENT << eventID << C_INTERVAL << "." << eventSignal->signalID() << "." << uid << C_START;

	m_jobIDs[eventID].push_back(jobID.str());

	unique_ptr<JobEventIntervalStart> jobEventIntervalStart(new JobEventIntervalStart(m_service, event, eventSignal, uid, payload, dtstart, durationInSeconds));
	unique_ptr<SchedulerJob> schedulerJob = SchedulerJob::CreateOnetimeSchedulerJob(std::move(jobEventIntervalStart), jobID.str(), dtstart);

	m_scheduler->addJob(std::move(schedulerJob));
}

/********************************************************************************/

void EventManager::scheduleEvent(const string &eventID, const oadr2b::oadr::oadrEvent *event)
{
	try
	{
		auto eventStatus = event->eiEvent().eventDescriptor().eventStatus();

		// Don't schedule cancelled or completed events
		if (eventStatus == oadr2b::ei::EventStatusEnumeratedType::cancelled || eventStatus == oadr2b::ei::EventStatusEnumeratedType::completed)
			return;

		time_t eventDtstart = DateTimeConverter::DateTimeToTime_t(event->eiEvent().eiActivePeriod().properties().dtstart().date_time());
		int durationInSeconds = ISO8601Duration::TotalSeconds(event->eiEvent().eiActivePeriod().properties().duration().duration());

		scheduleEventStart(eventID, event, eventDtstart);

		// durationInSeconds == 0 means run forever so don't schedule an eventComplete job
		if (durationInSeconds != 0)
			scheduleEventComplete(eventID, event, eventDtstart + durationInSeconds);

		for (const auto &signal : event->eiEvent().eiEventSignals().eiEventSignal())
		{
			int durationOffset = 0;

			for (const auto &interval : signal.intervals().interval())
			{
				string uid = interval.uid()->text(); 

				const signalPayloadType *spt = (signalPayloadType*)(&(interval.streamPayloadBase().front()));
				PayloadFloatType *pft = &(PayloadFloatType&)spt->payloadBase(); 

				int durationInSeconds = ISO8601Duration::TotalSeconds(interval.duration()->duration());

				scheduleEventIntervalStart(eventID, event, &signal, uid, pft->value(), eventDtstart + durationOffset, durationInSeconds);

				durationOffset += durationInSeconds;
			}
		}
	}
	catch (runtime_error &ex)
	{
		removeSchedule(eventID);

		throw(ex);
	}
}

/********************************************************************************/

void EventManager::handleExistingEvent(const string &eventID, const oadr2b::oadr::oadrEvent *event, const string &requestID, oadr2b::ei::eventResponses::eventResponse_sequence &eventResponses)
{
	oadr2b::oadr::oadrEvent *existingEvent = m_events[eventID].get();

	// The event hasn't been modified
	if (existingEvent->eiEvent().eventDescriptor().modificationNumber() ==
			event->eiEvent().eventDescriptor().modificationNumber())
	{
		return;
	}

	oadr2b::oadr::oadrEvent *eventCopy = event->_clone();
        
        oadr2b::ei::OptTypeType::value optType;
        
        // initialise a new db connection
        db.connectDB("localhost", "hao", "111111", "test");
        
        if (db.getDefaultOptSQL().compare("OptIn") == 0) {
            optType = oadr2b::ei::OptTypeType::value::optIn;
        } 
        else if (db.getDefaultOptSQL().compare("OptOut") == 0) {
            optType = oadr2b::ei::OptTypeType::value::optOut;
        }
        

	if (event->eiEvent().eventDescriptor().eventStatus() == EventStatusEnumeratedType::cancelled)
	{
		//optType = oadr2b::ei::OptTypeType::value::optOut;
                                
		m_service->OnEventCancel(eventID, event, optType);

		Oadr2bHelper::appendEventResponse(eventResponses, "200", "OK", eventID,
				event->eiEvent().eventDescriptor().modificationNumber(), optType, requestID);

		removeSchedule(eventID);
	}
	else
	{
		/*oadr2b::ei::OptTypeType::value optType = oadr2b::ei::OptTypeType::optOut;*/
                //optType = global_optType;
                
                m_service->OnEventModify(eventID, event, existingEvent, optType);

		Oadr2bHelper::appendEventResponse(eventResponses, "200", "OK", eventID,
				event->eiEvent().eventDescriptor().modificationNumber(), optType, requestID);

		removeSchedule(eventID);
		scheduleEvent(eventID, eventCopy);
	}
        
        string optTypeTemp;
        if (optType == oadr2b::ei::OptTypeType::optIn) {
            
            optTypeTemp = "OptIn";
        
        } else if (optType == oadr2b::ei::OptTypeType::optOut) {
            
             optTypeTemp = "OptOut";
            
        }
        
        
        string dateString;
        struct tm tm;
        time_t unixTimestamp;
        
        // build the string date time using info from Event message 
        dateString =   std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().year()) + "-"
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().month()) + "-"
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().day()) + " "
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().hours()) + ":"
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().minutes()) + ":"
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().seconds()) + "";
        
        //cout << dateString << endl;
        
        // convert string date time to struct tm
        strptime(dateString.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
        
        // convert struct tm to unix timestamp 
        unixTimestamp = mktime(&tm);  
        
        // update the existing event record in the db
        // Note that: everytime the VTN publish an event, the reuqestID will be changed !!
        db.updateVENEventSQL("UPDATE eventinfo SET startTime=FROM_UNIXTIME(" + std::to_string(unixTimestamp) + 
                                               "), duration='" + eventCopy->eiEvent().eiActivePeriod().properties().duration().duration().c_str() +
                                               "', eventStatus='" + eventCopy->eiEvent().eventDescriptor().eventStatus() +
                                               "', optState='" + optTypeTemp +
                                               "', marketContext='" + eventCopy->eiEvent().eventDescriptor().eiMarketContext().marketContext() +
                                               //"', signalType='" + eventCopy->eiEvent().eiEventSignals().eiEventSignal().front().signalType() +
                                               //"', currentValue='" + std::to_string(eventCopy->eiEvent().eiEventSignals().eiEventSignal().front().currentValue()->payloadFloat().value()) +
                                               "', vtnComment='" + eventCopy->eiEvent().eventDescriptor().vtnComment()->c_str() +
                                               "', testEvent='" + eventCopy->eiEvent().eventDescriptor().testEvent()->c_str() +
                                               "', responseRequired='" + eventCopy->oadrResponseRequired() +
                                               "', modificationNumber='" + std::to_string(eventCopy->eiEvent().eventDescriptor().modificationNumber()) +
                                               "', startAfter='" + eventCopy->eiEvent().eiActivePeriod().properties().tolerance()->tolerate().startafter()->c_str() +
                                               "', eiNotification='" + eventCopy->eiEvent().eiActivePeriod().properties().x_eiNotification()->duration().c_str() +
                                               "', eiRampUp='" + eventCopy->eiEvent().eiActivePeriod().properties().x_eiRampUp()->duration().c_str() +
                                               "', eiRecovery='" + eventCopy->eiEvent().eiActivePeriod().properties().x_eiRecovery()->duration().c_str() +
                                               "' WHERE eventID='" + eventID + "'");     
        
        // delete the existing event signal record and insert the "new" corresponding event signal
        db.deleteVENEventSignalSQL("DELETE FROM eventsignal WHERE eventID='" + eventID + "'");
        
        // use the interator to get multiple EventSignal and multiple interval 
        // the structure is: EventSignals -> EventSignal -> intervals -> interval
        // signalID, signalName, signalType, currentValue in EventSignal
        // duration, UID and targetValue/payload in interval
        for(const auto &signal : eventCopy->eiEvent().eiEventSignals().eiEventSignal()) {
            
            for (const auto &interval : signal.intervals().interval())
		{
                    //cout << "The signalID is: " << signal.signalID().c_str() << endl;
                            
                    const signalPayloadType *spt = (signalPayloadType*)(&(interval.streamPayloadBase().front()));
                    PayloadFloatType *pft = &(PayloadFloatType&)spt->payloadBase(); 
                            
                    db.updateVENEventSignalSQL("INSERT INTO eventsignal (eventID, signalID, signalName, signalType, signalInterval, UID, targetValue, currentValue, modificationNumber) VALUES ('"
                                                                       + eventID + "', '"
                                                                       + signal.signalID().c_str() + "', '"
                                                                       + signal.signalName().c_str() + "', '"
                                                                       + signal.signalType().c_str() + "', '"
                                                                       + interval.duration()->duration().c_str() + "', '"
                                                                       + interval.uid()->text() + "', '"
                                                                       + std::to_string(pft->value()) + "', '"
                                                                       + std::to_string(signal.currentValue()->payloadFloat().value()) + "', '"
                                                                       + std::to_string(eventCopy->eiEvent().eventDescriptor().modificationNumber()) + "')");                                                                                               
                          
                }
        }           
        
        db.closeDB();

	m_events[eventID] = unique_ptr<oadr2b::oadr::oadrEvent>(eventCopy);
}

/********************************************************************************/

void EventManager::handleNewEvent(const string &eventID, const oadr2b::oadr::oadrEvent *event, const string &requestID, oadr2b::ei::eventResponses::eventResponse_sequence &eventResponses)
{
	oadr2b::oadr::oadrEvent *eventCopy = event->_clone();

	m_events[eventID] = unique_ptr<oadr2b::oadr::oadrEvent>(eventCopy);
        
                                     
        /*if (global_optType.compare("Opt_In") == 0){*/
	
        //oadr2b::ei::OptTypeType::value optType = global_optType;
        oadr2b::ei::OptTypeType::value optType;
        
        // initialise a new db connection 
        db.connectDB("localhost", "hao", "111111", "test");
             
        if (db.getDefaultOptSQL().compare("OptIn") == 0) {
            optType = oadr2b::ei::OptTypeType::optIn;
        }
        else if (db.getDefaultOptSQL().compare("OptOut") == 0) {
            optType = oadr2b::ei::OptTypeType::optOut;
        }
        /*oadr2b::ei::OptTypeType::value optType = oadr2b::ei::OptTypeType::optIn;*/
        
          // handle the new incoming events from VTN and the the OptType is optIn
        /*std::cout << "A new incoming event from VTN is received and the OptType will be optIn." << endl; */
        
        /* eventCopy contains the event information from {oadrDistributeEvent} */
	m_service->OnEventNew(eventID, eventCopy, optType);
        
        /* eventReponses contains multiple eventResponse; */
        /* each eventResponse contains: 
           - responseCode: e.g 200
           - responseDescription: e.g OK
           - requestID 
           - qualifiedEventID: here is the eventID 
           - modificationNumber
           - optType*/
	Oadr2bHelper::appendEventResponse(eventResponses, "200", "OK", eventID,
			eventCopy->eiEvent().eventDescriptor().modificationNumber(), optType, requestID);

	scheduleEvent(eventID, eventCopy);
        
        /*} else if (global_optType.compare("Opt_Out") == 0){*/
        
        /*oadr2b::ei::OptTypeType::value optType = oadr2b::ei::OptTypeType::optOut;*/
        
         // handle the new incoming events from VTN and the the OptType is optIn
        /*std::cout << "A new incoming event from VTN is received and the OptType will be optIn." << endl; */
        
	/*m_service->OnEventNew(eventID, eventCopy, optType);*/

	/*Oadr2bHelper::appendEventResponse(eventResponses, "200", "OK", eventID,
			eventCopy->eiEvent().eventDescriptor().modificationNumber(), optType, requestID);*/

	/*scheduleEvent(eventID, eventCopy);
        } */
           
        //cout << eventID << endl;
        
       
        string optTypeTemp;
        if (optType == oadr2b::ei::OptTypeType::optIn) {
            
            optTypeTemp = "OptIn";
        
        } else if (optType == oadr2b::ei::OptTypeType::optOut) {
            
             optTypeTemp = "OptOut";
            
        }
        
        string dateString;
        
        struct tm tm;
        
        time_t unixTimestamp;
        
       
        // build the string date time using info from Event message 
        dateString =   std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().year()) + "-"
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().month()) + "-"
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().day()) + " "
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().hours()) + ":"
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().minutes()) + ":"
                     + std::to_string(eventCopy->eiEvent().eiActivePeriod().properties().dtstart().date_time().seconds()) + "";
        
        //cout << dateString << endl;
        
        // convert string date time to struct tm
        strptime(dateString.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
        
        // convert struct tm to unix timestamp 
        unixTimestamp = mktime(&tm);
        
        //cout << unixTimestamp << endl;
        
                
        // check if there is matched event record in DB with the same eventID
        // if there is no eventID, then insert new record for the eveninfo       
        if ( !db.eventRecordExistSQL("SELECT * FROM eventinfo WHERE eventID='" + eventID + "'") ) {
        
            // Note that: everytime the VTN publish an event, the reuqestID will be changed !!
            db.updateVENEventSQL("INSERT INTO eventinfo (eventID, startTime, duration, eventStatus, optState, marketContext, vtnComment, testEvent, responseRequired, modificationNumber, startAfter, eiNotification, eiRampUp, eiRecovery, requestID) VALUES ('" 
                                                         + eventID + "', FROM_UNIXTIME(" + std::to_string(unixTimestamp) + "), '"
                                                         + eventCopy->eiEvent().eiActivePeriod().properties().duration().duration().c_str() + "', '" 
                                                         + eventCopy->eiEvent().eventDescriptor().eventStatus() + "', '" 
                                                         + optTypeTemp + "', '" 
                                                         + eventCopy->eiEvent().eventDescriptor().eiMarketContext().marketContext() + "', '"
                                                         //+ eventCopy->eiEvent().eiEventSignals().eiEventSignal().front().signalType() + "', '"
                                                         //+ std::to_string(eventCopy->eiEvent().eiEventSignals().eiEventSignal().front().currentValue()->payloadFloat().value()) + "', '"
                                                         + eventCopy->eiEvent().eventDescriptor().vtnComment()->c_str() + "', '"
                                                         + eventCopy->eiEvent().eventDescriptor().testEvent()->c_str() + "', '" 
                                                         + eventCopy->oadrResponseRequired() + "', '"
                                                         + std::to_string(eventCopy->eiEvent().eventDescriptor().modificationNumber()) + "', '"
                                                         + eventCopy->eiEvent().eiActivePeriod().properties().tolerance()->tolerate().startafter()->c_str() + "', '"
                                                         + eventCopy->eiEvent().eiActivePeriod().properties().x_eiNotification()->duration().c_str() + "', '"
                                                         + eventCopy->eiEvent().eiActivePeriod().properties().x_eiRampUp()->duration().c_str() + "', '"
                                                         + eventCopy->eiEvent().eiActivePeriod().properties().x_eiRecovery()->duration().c_str() + "', '"
                                                         + requestID + "')");
   
        //else if there is eventID, update the existing event record for the event; 
        //Note that when VEN initially runs, it will regard whatever event as a new event, no matter if that event already exists in the DB because it does not load the event info from the DB 
        } else {
        
            // Note that: everytime the VTN publish an event, the reuqestID will be changed !!
            db.updateVENEventSQL("UPDATE eventinfo SET startTime=FROM_UNIXTIME(" + std::to_string(unixTimestamp) + 
                                                    "), duration='" + eventCopy->eiEvent().eiActivePeriod().properties().duration().duration().c_str() +
                                                    "', eventStatus='" + eventCopy->eiEvent().eventDescriptor().eventStatus() +
                                                    "', optState='" + optTypeTemp +
                                                    "', marketContext='" + eventCopy->eiEvent().eventDescriptor().eiMarketContext().marketContext() +
                                                    //"', signalType='" + eventCopy->eiEvent().eiEventSignals().eiEventSignal().front().signalType() +
                                                    //"', currentValue='" + std::to_string(eventCopy->eiEvent().eiEventSignals().eiEventSignal().front().currentValue()->payloadFloat().value()) +
                                                    "', vtnComment='" + eventCopy->eiEvent().eventDescriptor().vtnComment()->c_str() +
                                                    "', testEvent='" + eventCopy->eiEvent().eventDescriptor().testEvent()->c_str() +
                                                    "', responseRequired='" + eventCopy->oadrResponseRequired() +
                                                    "', modificationNumber='" + std::to_string(eventCopy->eiEvent().eventDescriptor().modificationNumber()) +
                                                    "', startAfter='" + eventCopy->eiEvent().eiActivePeriod().properties().tolerance()->tolerate().startafter()->c_str() +
                                                    "', eiNotification='" + eventCopy->eiEvent().eiActivePeriod().properties().x_eiNotification()->duration().c_str() +
                                                    "', eiRampUp='" + eventCopy->eiEvent().eiActivePeriod().properties().x_eiRampUp()->duration().c_str() +
                                                    "', eiRecovery='" + eventCopy->eiEvent().eiActivePeriod().properties().x_eiRecovery()->duration().c_str() + 
                                                    "', requestID='" + requestID +    
                                                    "' WHERE eventID='" + eventID + "'");     
        
        }
        
        
        // check if there is matched event signal record in DB with the same eventID
        // if there is no eventID, then insert new record for the eveninfo
        if ( !db.eventSignalExistSQL("SELECT * FROM eventsignal WHERE eventID='" + eventID + "'") ) {
        
             // use the interator to get multiple EventSignal and multiple interval 
             // the structure is: EventSignals -> EventSignal -> intervals -> interval
             // signalID, signalName, signalType, currentValue in EventSignal
             // duration, UID and targetValue/payload in interval
             for(const auto &signal : eventCopy->eiEvent().eiEventSignals().eiEventSignal()) {
            
                for (const auto &interval : signal.intervals().interval())
			{
                   
                            const signalPayloadType *spt = (signalPayloadType*)(&(interval.streamPayloadBase().front()));
                            PayloadFloatType *pft = &(PayloadFloatType&)spt->payloadBase(); 
                            
                            db.updateVENEventSignalSQL("INSERT INTO eventsignal (eventID, signalID, signalName, signalType, signalInterval, UID, targetValue, currentValue, modificationNumber) VALUES ('"
                                                                                + eventID + "', '"
                                                                                + signal.signalID().c_str() + "', '"
                                                                                + signal.signalName().c_str() + "', '"
                                                                                + signal.signalType().c_str() + "', '"
                                                                                + interval.duration()->duration().c_str() + "', '"
                                                                                + interval.uid()->text() + "', '"
                                                                                + std::to_string(pft->value()) + "', '"
                                                                                + std::to_string(signal.currentValue()->payloadFloat().value()) + "', '"
                                                                                + std::to_string(eventCopy->eiEvent().eventDescriptor().modificationNumber()) + "')");                                                                      
                               
                        }
            }        
        
             
        //else if there is eventID, update the existing event signal record for the event - first delete all signal belonging to the specific eventID and then insert the record
        //Note that when VEN initially runs, it will regard whatever event signal as a new event signal, no matter if that event signal already exists in the DB because it does not load the event signal info from the DB
        } else {
             
             // delete all signals belonging to the specific eventID
             db.deleteVENEventSignalSQL("DELETE FROM eventsignal WHERE eventID='" + eventID + "'");
             
             // use the interator to get multiple EventSignal and multiple interval 
             // the structure is: EventSignals -> EventSignal -> intervals -> interval
             // signalID, signalName, signalType, currentValue in EventSignal
             // duration, UID and targetValue/payload in interval
             for(const auto &signal : eventCopy->eiEvent().eiEventSignals().eiEventSignal()) {
            
                for (const auto &interval : signal.intervals().interval())
			{
                            //cout << "The signalID is: " << signal.signalID().c_str() << endl;
                            
                            const signalPayloadType *spt = (signalPayloadType*)(&(interval.streamPayloadBase().front()));
                            PayloadFloatType *pft = &(PayloadFloatType&)spt->payloadBase(); 
                            
                            db.updateVENEventSignalSQL("INSERT INTO eventsignal (eventID, signalID, signalName, signalType, signalInterval, UID, targetValue, currentValue, modificationNumber) VALUES ('"
                                                                                + eventID + "', '"
                                                                                + signal.signalID().c_str() + "', '"
                                                                                + signal.signalName().c_str() + "', '"
                                                                                + signal.signalType().c_str() + "', '"
                                                                                + interval.duration()->duration().c_str() + "', '"
                                                                                + interval.uid()->text() + "', '"
                                                                                + std::to_string(pft->value()) + "', '"
                                                                                + std::to_string(signal.currentValue()->payloadFloat().value()) + "', '"
                                                                                + std::to_string(eventCopy->eiEvent().eventDescriptor().modificationNumber()) + "')");                                                                      
                                                       
                          
                        }
            }              
        
        }
        
        
        
        
        db.closeDB();
        
        // write the event info into DB
        //db.updateVENEventSQL();        
        
}

/********************************************************************************/

void EventManager::manageEvents(oadr2b::oadr::oadrDistributeEventType &message)
{
	oadrDistributeEventType::oadrEvent_iterator itr;

	set<string> processedEventIDs;
        
        /* eventReponses takes the major event contents from {oadrDistributeEvent} and */
        /* append the response such as Opt-In and Opt-Out to the events */
	oadr2b::ei::eventResponses::eventResponse_sequence eventResponses;

	for (const auto &event : message.oadrEvent())
	{
		const string eventID = event.eiEvent().eventDescriptor().eventID();  

		// Does the event exist in the current map?
		if (m_events.find(eventID) == m_events.end())
		{
			// This is a new event that needs to be scheduled
                        /* Pass the event contents &event and response to &event will be included in eventResponses */
			handleNewEvent(eventID, &event, message.requestID(), eventResponses);
		}
		else
		{
			// Check if the event has been modified
			handleExistingEvent(eventID, &event, message.requestID(), eventResponses);
		}

		processedEventIDs.insert(eventID);
	}

	// Send a cancel event message for any events not included in the incoming message
	for (const auto &event : m_events)
	{
		const string eventID = event.first;

		if (processedEventIDs.find(eventID) == processedEventIDs.end())
		{
			m_service->OnEventImplicitCancel(eventID, event.second.get());

			removeSchedule(eventID);

			m_events.erase(eventID);
		}
	}

	m_sendCreatedEvent->sendCreatedEvent("200", "OK", message.requestID(), eventResponses);
}

/********************************************************************************/

void EventManager::handleExistingEventIndividualOpt(const string &eventID, const string &individualOptValue, oadr2b::ei::eventResponses::eventResponse_sequence &eventResponses) {

        oadr2b::oadr::oadrEvent *existingEvent = m_events[eventID].get();
    
        // query the DB for exisiting optState of the individual eventID
        db.connectDB("localhost", "hao", "111111", "test");
        string individualOptValueDB = db.getIndividualOptSQL(eventID);
        
        // query the DB for the requestID for the specific eventID
        string requestIDDB = db.getRequestIDSQL(eventID); 
        
        db.closeDB();
        
        //cout << "individualOptValueDB = " + individualOptValueDB + "; optRequest = " + individualOptValue << endl;

	
	oadr2b::oadr::oadrEvent *eventCopy = existingEvent->_clone();
        
        // assign value of individualOptValue to optType
        oadr2b::ei::OptTypeType::value optType;
        
        if(individualOptValue.compare("OptIn") == 0) {
        
            optType = oadr2b::ei::OptTypeType::optIn;
            
        } else if (individualOptValue.compare("OptOut") == 0) {
        
            optType = oadr2b::ei::OptTypeType::optOut;

        }

	if (existingEvent->eiEvent().eventDescriptor().eventStatus() == EventStatusEnumeratedType::cancelled)
	{
		
            m_service->OnEventCancel(eventID, existingEvent, optType);

                
            Oadr2bHelper::appendEventResponse(eventResponses, "200", "OK", eventID,
                		existingEvent->eiEvent().eventDescriptor().modificationNumber(), optType, requestIDDB);

                                
            removeSchedule(eventID);
	}
	else
	{
            /*oadr2b::ei::OptTypeType::value optType = oadr2b::ei::OptTypeType::optOut;*/
            //optType = global_optType;
            
            // If the request opt change of the individual event is different from the DB record, need to change the event schedule  
            if (individualOptValueDB.compare(individualOptValue) != 0)
            {
                //cout << "individualOptValueDB = your request Opt !!" << endl;
                //return;
                   
                m_service->OnEventModify(eventID, existingEvent, existingEvent, optType);

                
                Oadr2bHelper::appendEventResponse(eventResponses, "200", "OK", eventID,
                                existingEvent->eiEvent().eventDescriptor().modificationNumber(), optType, requestIDDB);

                removeSchedule(eventID);
                scheduleEvent(eventID, eventCopy);
                
                cout << "You should not see this if the individual opt is the same as existing!!" << endl;
                   
                string optTypeTemp;
                    
                if (optType == oadr2b::ei::OptTypeType::optIn) {
            
                    optTypeTemp = "OptIn";
        
                } else if (optType == oadr2b::ei::OptTypeType::optOut) {
            
                    optTypeTemp = "OptOut";
            
                }
               
        
                // update the optState of existing event record in the db
                db.connectDB("localhost", "hao", "111111", "test");
                db.updateVENEventSQL("UPDATE eventinfo SET optState='" + optTypeTemp + "' WHERE eventID='" + eventID + "'"); 
                db.closeDB();
                
            // else if the request opt is the same as the individualOpt in the db, 
            // only generate the eventResponse so that the createdEvent contains valid eventResponse; no need to to anything else  
            } else if (individualOptValueDB.compare(individualOptValue) == 0) {
                
                Oadr2bHelper::appendEventResponse(eventResponses, "200", "OK", eventID,
                                existingEvent->eiEvent().eventDescriptor().modificationNumber(), optType, requestIDDB);
                
            }                  
        
        
        }
        
	m_events[eventID] = unique_ptr<oadr2b::oadr::oadrEvent>(eventCopy);

}

/********************************************************************************/

void EventManager::manageIndividualEventOpt(const string &eventID, const string &individualOptValue)
{
    
        oadr2b::ei::eventResponses::eventResponse_sequence eventResponses;
        
        
        
        //m_events.find(eventID) 
        
	// Does the event exist in the current map?
	if (m_events.find(eventID) == m_events.end())
		{
                    // This is a new event that needs to be scheduled and it is impossible to change opt for a new event
                    // a new event will always use Default Opt
                    //handleNewEvent(eventID, &event, message.requestID(), eventResponses);
                    cout << "Error: cannot change opt for an unscheduled new event!" << endl;
                    return;
		}
	else
		{
                    // Check if the event has been modified
                    handleExistingEventIndividualOpt(eventID, individualOptValue, eventResponses);
		}

	
	

	

         // oadrCreatedEvent following the change of the opt for individual event does not contain the requestID
         // so use empty string "" here 
	m_sendCreatedEvent->sendCreatedEvent("200", "OK", "", eventResponses);
}
