/*
 * VENImpl.h
 *
 *  Created on: Jul 8, 2015
 *      Author: dupes
 */

#ifndef SAMPLEVENMANAGER_SAMPLEVENMANAGER_VENIMPL_H_
#define SAMPLEVENMANAGER_SAMPLEVENMANAGER_VENIMPL_H_

#include <oadr/manager/eventmanager/IEventService.h>
#include <oadr/manager/reportmanager/IReportService.h>

#include <oadr/ven/IOadrMessage.h>

#include <oadr/manager/IOADRExceptionService.h>

#include "easylogging++.h"




namespace samplevenmanager
{

class VENImpl : public IEventService, public IReportService, public IOadrMessage, public IOADRExceptionService
{
    
private:
        bool P21_changed_by_VTN;
        bool P22_changed_by_VTN;
        bool P23_changed_by_VTN;
        bool P24_changed_by_VTN;
        bool P25_changed_by_VTN;
        bool P26_changed_by_VTN;
        bool P27_changed_by_VTN;
        bool P28_changed_by_VTN;
        bool P29_changed_by_VTN;
        bool P30_changed_by_VTN;
        bool P31_changed_by_VTN;
        bool P48_changed_by_VTN;
        bool P49_changed_by_VTN;      
        bool P50_changed_by_VTN;
        bool P51_changed_by_VTN;
        bool P52_changed_by_VTN;
        
        bool P53_changed_by_VTN;
        bool P54_changed_by_VTN;
        bool P55_changed_by_VTN;
        bool P56_changed_by_VTN;
        bool P57_changed_by_VTN;
        bool P59_changed_by_VTN;
        bool P60_changed_by_VTN;
        bool P61_changed_by_VTN;
        bool P62_changed_by_VTN;
        bool P63_changed_by_VTN;
        bool P64_changed_by_VTN;
        bool P65_changed_by_VTN;      
        bool P66_changed_by_VTN;
        bool P67_changed_by_VTN;
        bool P68_changed_by_VTN;
        bool P69_changed_by_VTN; 
        
        bool P70_changed_by_VTN;
        bool P42_changed_by_VTN;
        bool P43_changed_by_VTN;
        bool P44_changed_by_VTN;
        bool P45_changed_by_VTN;
        bool P46_changed_by_VTN;
        bool P47_changed_by_VTN;
        bool P47B_changed_by_VTN; 
        
        float event_payload;
        
        unsigned int durationInSeconds_load_shift;
    
public:    
        
        /* functions for Class VENImpl */
        VENImpl(string venName, bool logToStdout);
	virtual ~VENImpl();
               
                
	virtual void OnPeriodicReportStart(const oadrReportRequestType &reportRequest);

	virtual void OnPeriodicReportComplete(const oadrReportRequestType &reportRequest);

	virtual void OnGenerateOneshotReport(const oadrReportRequestType &reportRequest, oadrUpdateReportType::oadrReport_sequence &sequence);

	virtual void OnGeneratePeriodicReport(const oadrReportRequestType &reportRequest, oadrUpdateReportType::oadrReport_sequence &sequence, time_t dtstart,
			unsigned int durationInSeconds);

	virtual void OnGenerateHistoricalReport(const oadrReportRequestType &reportRequest, oadrUpdateReportType::oadrReport_sequence &sequence, time_t dtstart,
			unsigned int durationInSeconds);

	virtual void OnGenerateRegisterReport(oadrRegisterReportType::oadrReport_sequence &sequence);

	virtual void OnEventStart(const std::string &eventID, const oadr2b::oadr::oadrEvent *event, unsigned int remainingDurationInSeconds);
	virtual void OnEventComplete(const std::string &eventID, const oadr2b::oadr::oadrEvent *event);
	virtual void OnEventIntervalStart(const std::string &eventID, const oadr2b::oadr::oadrEvent *event, const oadr2b::ei::eiEventSignalType *eventSignal, std::string uid, float payload, time_t dtstart, unsigned int remainingDurationInSeconds);

	virtual void OnEventNew(const std::string &eventID, const oadr2b::oadr::oadrEvent *event, oadr2b::ei::OptTypeType::value &optType);
	virtual void OnEventModify(const std::string &eventID, const oadr2b::oadr::oadrEvent *newEvent, const oadr2b::oadr::oadrEvent *oldEvent, oadr2b::ei::OptTypeType::value &optType);
	virtual void OnEventCancel(const std::string &eventID, const oadr2b::oadr::oadrEvent *event, oadr2b::ei::OptTypeType::value &optType);
	virtual void OnEventImplicitCancel(const std::string &eventID, const oadr2b::oadr::oadrEvent *event);

	virtual void OnProcessDistributeEventStart();
	virtual void OnGenerateCreatedEvent(oadr2b::ei::eventResponses::eventResponse_sequence &eventResponses);
	virtual void OnProcessDistributeEventComplete();

	virtual void OnOadrMessageReceived(std::string &message);
	virtual void OnOadrMessageSent(std::string &message);

	virtual void OnCurlException(CurlException &ex);
	virtual void OnException(std::exception &ex);
        
        /* declare the method logEventList() to log events using "eventlog" logger; */
        /* this method is originally declared in IEventService.h */
        /* this method is override in VENImpl.cpp; */
        virtual void logEventList(const std::string &eventID, const oadr2b::oadr::oadrEvent *event, oadr2b::ei::OptTypeType::value &optType);
};

} /* namespace samplevenmanager */

#endif /* SAMPLEVENMANAGER_SAMPLEVENMANAGER_VENIMPL_H_ */
