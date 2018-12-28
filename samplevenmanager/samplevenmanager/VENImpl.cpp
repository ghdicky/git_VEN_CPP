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

extern "C" {
/* include ied.h to access the IED ReceivedGTNET1, ReceivedGTNET2, ReceivedGTNET3 and ReceivedGTNET4 which contains P and Q of the Insch substation 
 *                         the IED SendVENIED1, SendVENIED2 and SendVENIED3 which contains P and Q setpoint */
#include "../../goosemgr/c/src/ied.h"
    
// include the rapid61850.h and interface.h header files for receiving and sending GOOSE
// use rapid61850 as high level interface
#include "../../goosemgr/c/src/iec61850.h"
#include "../../goosemgr/c/src/interface.h"    

}

    


/* include MyDB.h to access db_VENImpl for opt of individual houses */
#include "../../mysqlmgr/MyDB.h"


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
        
        P21_changed_by_VTN = false;
        P22_changed_by_VTN = false;
        P23_changed_by_VTN = false;
        P24_changed_by_VTN = false;
        P25_changed_by_VTN = false;
        P26_changed_by_VTN = false;
        P27_changed_by_VTN = false;
        P28_changed_by_VTN = false;
        P29_changed_by_VTN = false;
        P30_changed_by_VTN = false;
        P31_changed_by_VTN = false;
        P48_changed_by_VTN = false;
        P49_changed_by_VTN = false;      
        P50_changed_by_VTN = false;
        P51_changed_by_VTN = false;
        P52_changed_by_VTN = false;
        
        P53_changed_by_VTN = false;
        P54_changed_by_VTN = false;
        P55_changed_by_VTN = false;
        P56_changed_by_VTN = false;
        P57_changed_by_VTN = false;
        P59_changed_by_VTN = false;
        P60_changed_by_VTN = false;
        P61_changed_by_VTN = false;
        P62_changed_by_VTN = false;
        P63_changed_by_VTN = false;
        P64_changed_by_VTN = false;
        P65_changed_by_VTN = false;
        P66_changed_by_VTN = false;      
        P67_changed_by_VTN = false;
        P68_changed_by_VTN = false;
        P69_changed_by_VTN = false;      
        
        P70_changed_by_VTN = false;
        P42_changed_by_VTN = false;
        P43_changed_by_VTN = false;
        P44_changed_by_VTN = false;
        P45_changed_by_VTN = false;
        P46_changed_by_VTN = false;
        P47_changed_by_VTN = false;
        P47B_changed_by_VTN = false;
        
        event_payload = 0.0;  
        
        
        
        
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
	//dtend = dtend + (60 - (dtend % 60));
        
        // find the nearest time_t ends on the 10 second
        dtend = dtend + (10 - (dtend % 10));
        
	while (dtend <= dtstart)
	{
		//IntervalType intervalType = ReportHelper::generateInterval(dtend, 1, &DurationModifier::MINUTES);
                IntervalType intervalType = ReportHelper::generateInterval(dtend, 10, &DurationModifier::SECONDS);
            
		// for each rid, add a payload to IntervalType
                
                // The real power and reactive power of Insch network is accessed here 
		for (auto &specifier : reportRequest.reportSpecifier().specifierPayload())
		{
			string rid = specifier.rID();

			//float value = (float)(rand() % 10);
                        float value;
                        
                        /* switch (rid)
                            {
                                case "Insch_real_power":
                                        value = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_2_SubP.mag.f;
                                        break;

                                case "Insch_reactive_power":
                                        value = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_3_SubQ.mag.f;
                                        break;

                                default:
                                        value = (float)(rand() % 10);
                                        break;
                        } */
                        
                        if ( rid.compare("Insch_real_power") == 0 ) {
                            
                            value = 1000 * ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_2_SubP.mag.f;
                            
                            
                        } 
                        else if ( rid.compare("Insch_reactive_power") == 0 ) {
                            
                            value = 1000 * ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_3_SubQ.mag.f;
                            
                        } else {
                            
                            value = (float)(rand() % 10);
                            
                        }                       
                            
                            
			oadrReportPayloadType payload = ReportHelper::generateOadrReportPayloadFloat(rid, value,
					oadr2b::oadr::oadrDataQualityType::Quality_Good___Non_Specific,
					1, 1);

			intervalType.streamPayloadBase().push_back(payload);
		}

		intervals.push_back(intervalType);

		// increment to the next minute
		//dtend += 60;
                
                // increment to the next 10 s
                dtend += 10;
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
	/*oadrReportDescriptionType energy = ReportHelper::generateDescriptionEnergyItem("rid_energy_4184bb93", "DEVICE1", ReportEnumeratedType::reading,
			ReadingTypeEnumeratedType::Direct_Read, "", 1, 1, false, &DurationModifier::MINUTES,
			ReportHelper::eEnergyReal, "Wh", SiScaleCodeType::none); */

	// 1 minute power interval 
	//oadrReportDescriptionType power = ReportHelper::generateDescriptionPowerItem("rid_power_4184bb93", "DEVICE1", ReportEnumeratedType::reading,
	//		ReadingTypeEnumeratedType::Direct_Read, "", 1, 1, false, &DurationModifier::MINUTES,
	//		ReportHelper::ePowerReal, "W", SiScaleCodeType::none, 60.0, 120, true);
        
        // 10 second power interval 
        /* oadrReportDescriptionType ReportHelper::generateDescriptionPowerItem(string rID, string resourceID, ReportEnumeratedType::value reportType,
		ReadingTypeEnumeratedType::value readingType, string marketContext,
		int minSamplingPeriod, int maxSamplingPeriod, bool onChange, DurationModifier *durationModifier,
		ePowerItemType powerItemType, string units, SiScaleCodeType::value siScaleCodeType, double hertz,
		double voltage, bool ac, string description) */
	oadrReportDescriptionType real_power = ReportHelper::generateDescriptionPowerItem("Insch_real_power", "Insch_VEN", ReportEnumeratedType::reading,
			ReadingTypeEnumeratedType::Direct_Read, "", 10, 10, false, &DurationModifier::SECONDS,
			ReportHelper::ePowerReal, "kW", SiScaleCodeType::none, 50.0, 240, true);
        
        oadrReportDescriptionType reactive_power = ReportHelper::generateDescriptionPowerItem("Insch_reactive_power", "Insch_VEN", ReportEnumeratedType::reading,
			ReadingTypeEnumeratedType::Direct_Read, "", 10, 10, false, &DurationModifier::SECONDS,
			ReportHelper::ePowerReal, "kVAr", SiScaleCodeType::none, 50.0, 240, true);

	// ...
	// Create additional oadrReportDescriptionType objects...
	// ...

	// put each oadrReportDescriptionType into the description container
	//description.push_back(energy);
	//description.push_back(power);

        description.push_back(real_power);
        description.push_back(reactive_power);
        
	// create a report with the descriptions
	// there are two main report types: TELEMETRY_USAGE and HISTORY_USAGE
	// the structure of these report types is identical.  the only difference is how the reports can be used
	//oadrReportType telemetryUsage = ReportHelper::generateReportDescription(&ReportName::TELEMETRY_USAGE, 120, &DurationModifier::MINUTES,
	//		"DEMO_TELEMETRY_USAGE", 0, description);

        /* oadrReportType ReportHelper::generateReportDescription(ReportName *reportName, int duration, DurationModifier *durationModifier,
		string reportSpecifierID, time_t createDateTimeUTC, oadrReportType::oadrReportDescription_sequence &sequence) */
        /* duration means how long the report will be generated; 1440 = 1440 second = 24 minutes; 1440 minute = 1 day */
        oadrReportType inschTelemetryUsage = ReportHelper::generateReportDescription(&ReportName::TELEMETRY_USAGE, 1440, &DurationModifier::SECONDS,
			"DEMO_Insch_TELEMETRY_USAGE", 0, description);
        
	// push the telemtry usage report onto the container
	// if there are additional reports (such as a history usage report), push those
	// reports as well.
	//sequence.push_back(telemetryUsage);
        
        sequence.push_back(inschTelemetryUsage);
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
                
        if ( (event->eiEvent().eiEventSignals().eiEventSignal().front().signalName().compare("LOAD_CONTROL") == 0) & 
                (event->eiEvent().eiEventSignals().eiEventSignal().front().signalType().compare("x-loadControlPercentOffset") == 0)) {
            LOG(INFO) << "Load control DR completes; stop GOOSE";
            
               
            
            // Event interval completes:
            // need to shift/compensate the reduced load to the following interval which is double event interval
            // the increased compensation percentage for individual load is 1/2 of the reduced load
            // amount to increased is calculated as: {[current_load/(1 - payload)] - current_load} / 2
            // use MW as unit here; 0.07 = 0.07 MW =70 kW
            
            
            // use SendVENIED1 GOOSE to increase load for load shift for house 21-31, 48-52
            if (P21_changed_by_VTN) {
                P21_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_1_21P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_1_21P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            //db.connectDB("localhost", "hao", "111111", "test");
            
            if (P22_changed_by_VTN) {
                P22_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_3_22P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_3_22P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P23_changed_by_VTN) {
                P23_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_5_23P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_5_23P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P24_changed_by_VTN) {
                P24_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_7_24P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_7_24P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P25_changed_by_VTN) {
                P25_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_9_25P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_9_25P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P26_changed_by_VTN) {
                P26_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_11_26P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_11_26P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P27_changed_by_VTN) {
                P27_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_13_27P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_13_27P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P28_changed_by_VTN) {
                P28_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_15_28P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_15_28P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P29_changed_by_VTN) {
                P29_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_17_29P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_17_29P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P30_changed_by_VTN) {
                P30_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_19_30P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_19_30P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P31_changed_by_VTN) {
                P31_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_21_31P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_21_31P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P48_changed_by_VTN) {
                P48_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_23_48P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_23_48P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P49_changed_by_VTN) {
                P49_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_25_49P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_25_49P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P50_changed_by_VTN) {
                P50_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_27_50P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_27_50P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P51_changed_by_VTN) {
                P51_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_29_51P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_29_51P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P52_changed_by_VTN) {
                P52_changed_by_VTN = false;
                SendVENIED1.P1.C1.GGIO_31_52P.AnIn.mag.f += SendVENIED1.P1.C1.GGIO_31_52P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            
            
            // use SendVENIED2 GOOSE to increase load for load shift for house 53-57, 58-69
            if (P53_changed_by_VTN) {
                P53_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_1_53P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_1_53P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P54_changed_by_VTN) {
                P54_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_3_54P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_3_54P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P55_changed_by_VTN) {
                P55_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_5_55P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_5_55P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P56_changed_by_VTN) {
                P56_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_7_56P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_7_56P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P57_changed_by_VTN) {
                P57_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_9_57P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_9_57P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P59_changed_by_VTN) {
                P59_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_11_59P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_11_59P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P60_changed_by_VTN) {
                P60_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_13_60P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_13_60P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P61_changed_by_VTN) {
                P61_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_15_61P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_15_61P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P62_changed_by_VTN) {
                P62_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_17_62P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_17_62P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P63_changed_by_VTN) {
                P63_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_19_63P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_19_63P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P64_changed_by_VTN) {
                P64_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_21_64P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_21_64P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P65_changed_by_VTN) {
                P65_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_23_65P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_23_65P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P66_changed_by_VTN) {
                P66_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_25_66P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_25_66P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P67_changed_by_VTN) {
                P67_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_27_67P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_27_67P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P68_changed_by_VTN) {
                P68_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_29_68P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_29_68P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P69_changed_by_VTN) {
                P69_changed_by_VTN = false;
                SendVENIED2.P1.C1.GGIO_31_69P.AnIn.mag.f += SendVENIED2.P1.C1.GGIO_31_69P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            
            
            // use SendVENIED3 to increase load for load shift for house 70, Section 42-27B
            if (P70_changed_by_VTN) {
                P70_changed_by_VTN = false;
                SendVENIED3.P1.C1.GGIO_1_70P.AnIn.mag.f += SendVENIED3.P1.C1.GGIO_1_70P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P42_changed_by_VTN) {
                P42_changed_by_VTN = false;
                SendVENIED3.P1.C1.GGIO_3_42P.AnIn.mag.f += SendVENIED3.P1.C1.GGIO_3_42P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P43_changed_by_VTN) {
                P43_changed_by_VTN = false;
                SendVENIED3.P1.C1.GGIO_5_43P.AnIn.mag.f += SendVENIED3.P1.C1.GGIO_5_43P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P44_changed_by_VTN) {
                P44_changed_by_VTN = false;
                SendVENIED3.P1.C1.GGIO_7_44P.AnIn.mag.f += SendVENIED3.P1.C1.GGIO_7_44P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P45_changed_by_VTN) {
                P45_changed_by_VTN = false;
                SendVENIED3.P1.C1.GGIO_9_45P.AnIn.mag.f += SendVENIED3.P1.C1.GGIO_9_45P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P46_changed_by_VTN) {
                P46_changed_by_VTN = false;
                SendVENIED3.P1.C1.GGIO_11_46P.AnIn.mag.f += SendVENIED3.P1.C1.GGIO_11_46P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P47_changed_by_VTN) {
                P47_changed_by_VTN = false;
                SendVENIED3.P1.C1.GGIO_13_47P.AnIn.mag.f += SendVENIED3.P1.C1.GGIO_13_47P.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            if (P47B_changed_by_VTN) {
                P47B_changed_by_VTN = false;
                SendVENIED3.P1.C1.GGIO_15_47BP.AnIn.mag.f += SendVENIED3.P1.C1.GGIO_15_47BP.AnIn.mag.f * 0.5 * event_payload / (1-event_payload);            
            }
            
            
            load_shift_end_time = time(NULL) + 2 * durationInSeconds_load_shift; // calculate the end time for load shift
            
            LOG(INFO) << "load_shift_end_time is: " << load_shift_end_time;
            
            event_interval_start = 0; // event interval is completed
            load_shift_after_event_interval = 1; // load shift starts after event interval  
        }
}

/********************************************************************************/

void VENImpl::OnEventIntervalStart(const std::string& eventID,
		const oadr2b::oadr::oadrEvent* event,
		const oadr2b::ei::eiEventSignalType* eventSignal, std::string uid,
		float payload, time_t dtstart, unsigned int remainingDurationInSeconds)
{
	LOG(INFO) << "event interval start: " << eventID << " " << payload << " " << remainingDurationInSeconds;
                
        if ( (eventSignal->signalName().compare("LOAD_CONTROL") == 0) & 
                (eventSignal->signalType().compare("x-loadControlPercentOffset") == 0)) {
            LOG(INFO) << "Load control DR is received and starts; send GOOSE";
            //db_VENImpl.connectDB("localhost", "hao", "111111", "test");
            //db_VENImpl.closeDB();
            
            // record the payload value
            event_payload = payload;
            
            // record the remainingDurationInSeconds value
            durationInSeconds_load_shift = remainingDurationInSeconds;
            LOG(INFO) << "remaining duration in second is: " << durationInSeconds_load_shift;
            
            //LOG(INFO) << "ReceiveGTNET1.21P is: " << ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_4_21P.mag.f;
            //LOG(INFO) << "ReceiveGTNET1.21Opt is: " << ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_7_21Opt.mag.f;
            
            // Event interval starts:
            // reduce individual load by payload which is the percentage offset from the current value
            // amount to reduced is determined by the received payload: [original P of individual house] x (1 - payload)
            // use MW as unit here; 0.07 = 0.07 MW =70 kW
            
            // use SendVENIED1 GOOSE to suppress load for house 21-31, 48-52
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_4_21P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_7_21Opt.mag.f == 1.0) ) {        
                // set corresponding field in sent GOOSE
                P21_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_1_21P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_4_21P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_8_22P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_11_22Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P22_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_3_22P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_8_22P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_12_23P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_15_23Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P23_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_5_23P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_12_23P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_16_24P.mag.f > (0.07/40.0)) & 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_19_24Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P24_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_7_24P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_16_24P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_20_25P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_23_25Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P25_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_9_25P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_20_25P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_24_26P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_27_26Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P26_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_11_26P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_24_26P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_28_27P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_31_27Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P27_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_13_27P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_28_27P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_32_28P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_35_28Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P28_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_15_28P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_32_28P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_36_29P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_39_29Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P29_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_17_29P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_36_29P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_40_30P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_43_30Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P30_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_19_30P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_40_30P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_44_31P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_47_31Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P31_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_21_31P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_44_31P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_48_48P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_51_48Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P48_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_23_48P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_48_48P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_52_49P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_55_49Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P49_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_25_49P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_52_49P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_56_50P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_59_50Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P50_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_27_50P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_56_50P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_60_51P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_63_51Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P51_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_29_51P.AnIn.mag.f = ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_60_51P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_66_52P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_69_52Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P52_changed_by_VTN = true;
                SendVENIED1.P1.C1.GGIO_31_52P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_66_52P.mag.f * (1.0 - payload);
            }
            
            
            // use SendVENIED2 GOOSE to suppress load for house 53-57, 58-69
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_70_53P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_73_53Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P53_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_1_53P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_70_53P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_74_54P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_77_54Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P54_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_3_54P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_74_54P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_78_55P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_81_55Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P55_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_5_55P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_78_55P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_82_56P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_85_56Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P56_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_7_56P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_82_56P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_86_57P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_89_57Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P57_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_9_57P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_86_57P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_90_59P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_93_59Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P59_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_11_59P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_90_59P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_94_60P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_97_60Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P60_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_13_60P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_94_60P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_98_61P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_101_61Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P61_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_15_61P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_98_61P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_102_62P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_105_62Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P62_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_17_62P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_102_62P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_106_63P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_109_63Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P63_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_19_63P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_106_63P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_110_64P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_113_64Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P64_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_21_64P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_110_64P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_114_65P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_117_65Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P65_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_23_65P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_114_65P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_118_66P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_121_66Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P66_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_25_66P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_118_66P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_122_67P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_125_67Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P67_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_27_67P.AnIn.mag.f = ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_122_67P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_130_68P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_133_68Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P68_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_29_68P.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_130_68P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_134_69P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_137_69Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P69_changed_by_VTN = true;
                SendVENIED2.P1.C1.GGIO_31_69P.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_134_69P.mag.f * (1.0 - payload);
            }
            
            
            // use SendVENIED3 to suppress load for house 70, Section 42-27B
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_138_70P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_141_70Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P70_changed_by_VTN = true;
                SendVENIED3.P1.C1.GGIO_1_70P.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_138_70P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_142_42P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_145_42Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P42_changed_by_VTN = true;
                SendVENIED3.P1.C1.GGIO_3_42P.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_142_42P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_146_43P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_149_43Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P43_changed_by_VTN = true;
                SendVENIED3.P1.C1.GGIO_5_43P.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_146_43P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_150_44P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_153_44Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P44_changed_by_VTN = true;
                SendVENIED3.P1.C1.GGIO_7_44P.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_150_44P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_154_45P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_157_45Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P45_changed_by_VTN = true;
                SendVENIED3.P1.C1.GGIO_9_45P.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_154_45P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_158_46P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_161_46Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P46_changed_by_VTN = true;
                SendVENIED3.P1.C1.GGIO_11_46P.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_158_46P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_162_47P.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_165_47Opt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P47_changed_by_VTN = true;
                SendVENIED3.P1.C1.GGIO_13_47P.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_162_47P.mag.f * (1.0 - payload);
            }
            if ( (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_166_47BP.mag.f > (0.07/40.0)) && 
                    (ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_169_47BOpt.mag.f == 1.0) ) {
                // set corresponding field in sent GOOSE
                P47B_changed_by_VTN = true;
                SendVENIED3.P1.C1.GGIO_15_47BP.AnIn.mag.f = ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_166_47BP.mag.f * (1.0 - payload);
            }
            
            event_interval_start = 1;
            load_shift_after_event_interval = 0;
            //event_and_load_shift_whole_process_start = 1;
            
            
            //third.join();
            
        }
        
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

