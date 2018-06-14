/*
 * VENImpl.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: dupes
 */

#include "VENImpl.h"

#include <iostream>

#include <oadr/request/report/ReportHelper.h>

#include <stdlib.h>


/* include DateTimeConverter.h for method DateTimeConverter::DateTimeToTime_t() */
#include "../../oadr/oadr/helper/DateTimeConverter.h"

/* include ISO8601Duration.h for method ISO8601Duration::TotalSeconds() */
#include "../../oadr/oadr/helper/ISO8601Duration.h"

/**/
#include <string>


using namespace std;

namespace samplevenmanager
{

VENImpl::VENImpl(string venName, bool logToStdout)
{
	el::Configurations conf;


	conf.setGlobally(el::ConfigurationType::ToStandardOutput, (logToStdout ? "true" : "false"));

	conf.setGlobally(el::ConfigurationType::ToFile, "true");
	conf.setGlobally(el::ConfigurationType::Filename, "logs/" + venName + ".log");

	el::Loggers::reconfigureLogger("default", conf);
        
        /* use another logger for receiving events */
        el::Configurations eventlog_conf;
        
        eventlog_conf.setGlobally(el::ConfigurationType::ToStandardOutput, (logToStdout ? "true" : "false"));
        
        eventlog_conf.setGlobally(el::ConfigurationType::ToFile, "true");
	eventlog_conf.setGlobally(el::ConfigurationType::Filename, "logs/" + venName + "----Event-List" +".log");
        
        el::Loggers::reconfigureLogger("eventlog", eventlog_conf);
        
        
}

/********************************************************************************/

VENImpl::~VENImpl()
{
}

/********************************************************************************/

void VENImpl::OnPeriodicReportStart(const oadrReportRequestType& reportRequest)
{
	LOG(INFO) << " periodic report start";
}

/********************************************************************************/

void VENImpl::OnPeriodicReportComplete(
		const oadrReportRequestType& reportRequest)
{
	LOG(INFO) << " periodic report complete";
}

/********************************************************************************/

void VENImpl::OnGenerateOneshotReport(
		const oadrReportRequestType& reportRequest,
		oadrUpdateReportType::oadrReport_sequence &sequence)
{
	LOG(INFO) << " generate oneshot report";
}

/********************************************************************************/

void VENImpl::OnGeneratePeriodicReport(
		const oadrReportRequestType& reportRequest,
		oadrUpdateReportType::oadrReport_sequence &sequence, time_t dtstart,
		unsigned int durationInSeconds)
{
	LOG(INFO) << "generate periodic report: " << reportRequest.reportRequestID();

	time_t dtend = dtstart - durationInSeconds;
	intervals::interval_sequence intervals;

	// find the nearest time_t that ends on the minute
	dtend = dtend + (60 - (dtend % 60));

	while (dtend <= dtstart)
	{
		IntervalType intervalType = ReportHelper::generateInterval(dtend, 1, &DurationModifier::MINUTES);

		// for each rid, add a payload to IntervalType
		for (auto &specifier : reportRequest.reportSpecifier().specifierPayload())
		{
			string rid = specifier.rID();

			float value = (float)(rand() % 10);

			oadrReportPayloadType payload = ReportHelper::generateOadrReportPayloadFloat(rid, value,
					oadr2b::oadr::oadrDataQualityType::Quality_Good___Non_Specific,
					1, 1);

			intervalType.streamPayloadBase().push_back(payload);
		}

		intervals.push_back(intervalType);

		// increment to the next minute
		dtend += 60;
	}

	if (intervals.size() > 0)
	{
		time_t now = time(NULL);

		oadrReportType report = ReportHelper::generateReport(&ReportName::TELEMETRY_USAGE, reportRequest.reportSpecifier().reportSpecifierID(),
				reportRequest.reportRequestID(), now, intervals);

		sequence.push_back(report);
	}
}

/********************************************************************************/

void VENImpl::OnGenerateHistoricalReport(
		const oadrReportRequestType& reportRequest,
		oadrUpdateReportType::oadrReport_sequence &sequence, time_t dtstart,
		unsigned int durationInSeconds)
{
	LOG(INFO) << "generate historical report";
}

/********************************************************************************/

void VENImpl::OnGenerateRegisterReport(oadrRegisterReportType::oadrReport_sequence &sequence)
{
	LOG(INFO) << "register report";

	oadrReportType::oadrReportDescription_sequence description;
        
	// 1 minute energy interval
        /* this is to generate (oadrReportDescription) element; */
        /* a {oadrRegisterReport} contains 1 report which can be telemetry_usage, historical_usage and telemetry_status; 
           1 report e.g. telemetry can contain multiple (oadrReportDescription) elements */
	oadrReportDescriptionType energy = ReportHelper::generateDescriptionEnergyItem("rid_energy_4184bb93", "DEVICE1", ReportEnumeratedType::reading,
			ReadingTypeEnumeratedType::Direct_Read, "", 1, 1, false, &DurationModifier::MINUTES,
			ReportHelper::eEnergyReal, "Wh", SiScaleCodeType::none);

	// 1 minute power interval
	oadrReportDescriptionType power = ReportHelper::generateDescriptionPowerItem("rid_power_4184bb93", "DEVICE1", ReportEnumeratedType::reading,
			ReadingTypeEnumeratedType::Direct_Read, "", 1, 1, false, &DurationModifier::MINUTES,
			ReportHelper::ePowerReal, "W", SiScaleCodeType::none, 60.0, 120, true);

	// ...
	// Create additional oadrReportDescriptionType objects...
	// ...

	// put each oadrReportDescriptionType into the description container
	description.push_back(energy);
	description.push_back(power);

	// create a report with the descriptions
	// there are two main report types: TELEMETRY_USAGE and HISTORY_USAGE
	// the structure of these report types is identical.  the only difference is how the reports can be used
	oadrReportType telemetryUsage = ReportHelper::generateReportDescription(&ReportName::TELEMETRY_USAGE, 120, &DurationModifier::MINUTES,
			"DEMO_TELEMETRY_USAGE", 0, description);

	// push the telemtry usage report onto the container
	// if there are additional reports (such as a history usage report), push those
	// reports as well.
	sequence.push_back(telemetryUsage);
}

/********************************************************************************/

void VENImpl::OnEventStart(const std::string& eventID,
		const oadr2b::oadr::oadrEvent* event, unsigned int remainingDurationInSeconds)
{
	LOG(INFO) << "event start: "  << eventID;
}

/********************************************************************************/

void VENImpl::OnEventComplete(const std::string& eventID,
		const oadr2b::oadr::oadrEvent* event)
{
	LOG(INFO) << "event complete: "  << eventID;
}

/********************************************************************************/

void VENImpl::OnEventIntervalStart(const std::string& eventID,
		const oadr2b::oadr::oadrEvent* event,
		const oadr2b::ei::eiEventSignalType* eventSignal, std::string uid,
		float payload, time_t dtstart, unsigned int remainingDurationInSeconds)
{
	LOG(INFO) << "event interval start: " << eventID << payload << " " << remainingDurationInSeconds;
}

/********************************************************************************/

void VENImpl::OnEventNew(const std::string& eventID,
		const oadr2b::oadr::oadrEvent* event, oadr2b::ei::OptTypeType::value &optType)
{
	LOG(INFO) << "new event received: " << eventID;
        
        logEventList(eventID, event, optType);
               
}

/********************************************************************************/

void VENImpl::OnEventModify(const std::string& eventID,
		const oadr2b::oadr::oadrEvent* newEvent,
		const oadr2b::oadr::oadrEvent* oldEvent, oadr2b::ei::OptTypeType::value &optType)
{
	LOG(INFO) << "event modified: " << eventID;
}

/********************************************************************************/

void VENImpl::OnEventCancel(const std::string& eventID,
		const oadr2b::oadr::oadrEvent* event, oadr2b::ei::OptTypeType::value &optType)
{
	LOG(INFO) << "event cancelled: " << eventID;
}

/********************************************************************************/

void VENImpl::OnEventImplicitCancel(const std::string& eventID,
		const oadr2b::oadr::oadrEvent* event)
{
	LOG(INFO) << "event imiplicitly cancelled: " << eventID;
}

/********************************************************************************/

void VENImpl::OnProcessDistributeEventStart()
{
	LOG(INFO) << "processing distribute event message";
}

/********************************************************************************/

void VENImpl::OnGenerateCreatedEvent(
		oadr2b::ei::eventResponses::eventResponse_sequence& eventResponses)
{
	LOG(INFO) << "generate created event";
}

/********************************************************************************/

void VENImpl::OnProcessDistributeEventComplete()
{
	LOG(INFO) << "processing distribute event message complete";
}

/********************************************************************************/

void VENImpl::OnOadrMessageReceived(std::string &message)
{
	LOG(INFO) << "\nVEN <--- VTN\n" << message << "\n=================================\n";
}

/********************************************************************************/

void VENImpl::OnOadrMessageSent(std::string &message)
{
	LOG(INFO) << "\nVEN ---> VTN\n" << message << "\n=================================\n";
}

/********************************************************************************/

void VENImpl::OnCurlException(CurlException &ex)
{
	LOG(ERROR) << "curl exception : " << ex.what();
}

/********************************************************************************/

void VENImpl::VENImpl::OnException(std::exception &ex)
{
	LOG(ERROR) << "std exception : " << ex.what();
}

void VENImpl::logEventList(const std::string& eventID,
		const oadr2b::oadr::oadrEvent* event, oadr2b::ei::OptTypeType::value &optType)
{       
        /*time_t eventDtstart = DateTimeConverter::DateTimeToTime_t(event->eiEvent().eiActivePeriod().properties().dtstart().date_time());*/
        
        /* obtain the event start date time with type of data_time_type */
        icalendar_2_0::dtstart::date_time_type eventDtstart = event->eiEvent().eiActivePeriod().properties().dtstart().date_time();
        
        
        int day = eventDtstart.day();
        std::string day_str;
        if (day < 10){
        
            day_str = "0" + std::to_string(day);
        } else {
        
            day_str = std::to_string(day);
        }
        
        int month = eventDtstart.month();
        std::string month_str;
        if (month < 10){
        
            month_str = "0" + std::to_string(month);
        } else {
        
            month_str = std::to_string(month);
        }
        
        int hour = eventDtstart.hours();
        std::string hour_str;
        if (hour < 10){
        
            hour_str = "0" + std::to_string(hour);
        } else {
        
            hour_str = std::to_string(hour);
        }
        
        int minute = eventDtstart.minutes();
        std::string minute_str;
        if (minute < 10){
        
            minute_str = "0" + std::to_string(minute);
        } else {
        
            minute_str = std::to_string(minute);
        }
        
        int second = eventDtstart.seconds();
        std::string second_str;
        if (second < 10){
        
            second_str = "0" + std::to_string(second);
        } else {
        
            second_str = std::to_string(second);
        }
        
        /* No need to use time zone because all timestamps sent from VTN is presented in UTC time; */
        /* For example, local time is 22:23 UTC+03:00, VTN only sends 19:23 UTC+00:00 */
        /*
        int zone_hour = eventDtstart.zone_hours();
        std::string zone_hour_str;
        if (zone_hour >= 0){
            
            if (zone_hour >= 10){
            
                zone_hour_str = "+" + std::to_string(zone_hour) + ":00";
            
            } else if (zone_hour < 10){
            
                zone_hour_str = "+0" + std::to_string(zone_hour) + ":00";
            }
        } else if (zone_hour < 0){
        
            if (zone_hour <= -10){
            
                zone_hour_str = "-" + std::to_string(zone_hour) + ":00"; 
            } else if (zone_hour > -10){
            
                zone_hour_str = "-0" + std::to_string(zone_hour) + ":00";
            }        
        } */
            
     
        
        
        /* construct time string in the formate dd/mm/yyyy hh:mm:ss */
        std::ostringstream eventDtstart_temp;    
   
        eventDtstart_temp << day_str << "/" << month_str << "/" << eventDtstart.year() << " " << hour_str << ":" << minute_str << ":" << second_str << " UTC+00:00";
        
        std::string eventDtstart_string = eventDtstart_temp.str();
        
               
	/*int durationInSeconds = ISO8601Duration::TotalSeconds(event->eiEvent().eiActivePeriod().properties().duration().duration());*/
        /*int durationInMinutes = durationInSeconds / 60;*/
        std::string duration = event->eiEvent().eiActivePeriod().properties().duration().duration().data();
    
        
        std::string eventStatus = event->eiEvent().eventDescriptor().eventStatus().data();
        
        /* The event data will be logged using the eventlog_conf; LOG(INFO) is using the default log which is conf*/
        /* The information involves: Event ID, Start Time, Duration, Status, Opt State, Market Context, Signal Type, Current Value, VTN Comment, Test Event, Response */
        /*CLOG(INFO, "eventlog") << eventID << "              " << eventDtstart << "              " << durationInMinutes << endl;*/
        
        CLOG(INFO, "eventlog") << "\nEvent ID" << "                   " << "Start Time"        << "                         " << "Duration"             << "      "     << "Status"    << "      \n"       
                               << eventID      << "       "             << eventDtstart_string << "      "                    << duration               << "          " << eventStatus << "\n\n=================================\n";

}

} /* namespace samplevenmanager */

