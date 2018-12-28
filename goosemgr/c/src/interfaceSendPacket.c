/**
 * Rapid-prototyping protection schemes with IEC 61850
 *
 * Copyright (c) 2014 Steven Blair
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "interfaceSendPacket.h"

// include <unistd.h> for sleep() function 
#include <unistd.h>




int event_interval_start = 0; // initialise the event_interval_start flag;
                              // 0 means event interval not start or completed
                              // 1 means event interval started and GOOSE should be send periodically

int load_shift_after_event_interval = 0; // initialise the load_shift_after_event_interval flag;
                                         // 0 means load shift not start or completed
                                         // 1 means load shift started and GOOSE should be send periodically

//int event_and_load_shift_whole_process_start = 0; // initialise the event_and_load_shift_whole_process_start flag;
                                                  // 0 means whole process not start or completed and should not enter the GOOSE periodic while loop
                                                  // 1 means whole process started and GOOSE should be send periodically

time_t load_shift_end_time = 0;

int interface_sv_update_E1Q1SB1_C1_PerformanceSV() {
	int len = sv_update_E1Q1SB1_C1_PerformanceSV(bufOut);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;
}

int interface_gse_send_E1Q1SB1_C1_Performance(int statusChange, int timeAllowedToLive) {
	int len = gse_send_E1Q1SB1_C1_Performance(bufOut, (CTYPE_BOOLEAN) statusChange, (CTYPE_INT32U) timeAllowedToLive);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;
}

int interface_gse_send_E1Q1SB1_C1_ItlPositions(int statusChange, int timeAllowedToLive) {
	int len = gse_send_E1Q1SB1_C1_ItlPositions(bufOut, (CTYPE_BOOLEAN) statusChange, (CTYPE_INT32U) timeAllowedToLive);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;
}

int interface_gse_send_E1Q1SB1_C1_AnotherPositions(int statusChange, int timeAllowedToLive) {
	int len = gse_send_E1Q1SB1_C1_AnotherPositions(bufOut, (CTYPE_BOOLEAN) statusChange, (CTYPE_INT32U) timeAllowedToLive);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;
}

int interface_sv_update_E1Q1SB1_C1_Volt() {
	int len = sv_update_E1Q1SB1_C1_Volt(bufOut);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;
}

int interface_sv_update_E1Q1SB1_C1_rmxuCB() {
	int len = sv_update_E1Q1SB1_C1_rmxuCB(bufOut);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;
}

int interface_gse_send_D1Q1SB4_C1_SyckResult(int statusChange, int timeAllowedToLive) {
	int len = gse_send_D1Q1SB4_C1_SyckResult(bufOut, (CTYPE_BOOLEAN) statusChange, (CTYPE_INT32U) timeAllowedToLive);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;
}

int interface_gse_send_D1Q1SB4_C1_MMXUResult(int statusChange, int timeAllowedToLive) {
	int len = gse_send_D1Q1SB4_C1_MMXUResult(bufOut, (CTYPE_BOOLEAN) statusChange, (CTYPE_INT32U) timeAllowedToLive);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;
}

int interface_gse_send_SendVENIED1_C1_outputs1(int statusChange, int timeAllowedToLive) {
        int len = gse_send_SendVENIED1_C1_outputs1(bufOut, (CTYPE_BOOLEAN) statusChange, (CTYPE_INT32U) timeAllowedToLive);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;

}

int interface_gse_send_SendVENIED2_C1_outputs2(int statusChange, int timeAllowedToLive) {
        int len = gse_send_SendVENIED2_C1_outputs2(bufOut, (CTYPE_BOOLEAN) statusChange, (CTYPE_INT32U) timeAllowedToLive);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;

}

int interface_gse_send_SendVENIED3_C1_outputs3(int statusChange, int timeAllowedToLive) {
        int len = gse_send_SendVENIED3_C1_outputs3(bufOut, (CTYPE_BOOLEAN) statusChange, (CTYPE_INT32U) timeAllowedToLive);

	if (len > 0) {
		pcap_sendpacket(fp, bufOut, len);
	}

	return len;

}

void periodic_interface_gse_send() {
        //int len = 0;
        
    while (1) {
        // if event interval starts or load shift is in process, send GOOSE periodically
        //if( event_and_load_shift_whole_process_start && (event_interval_start || load_shift_after_event_interval) ){
        if (event_interval_start){
        
            interface_gse_send_SendVENIED1_C1_outputs1(1, 600000);
            interface_gse_send_SendVENIED2_C1_outputs2(1, 600000);
            interface_gse_send_SendVENIED3_C1_outputs3(1, 600000);
        
        }else if (load_shift_after_event_interval) {          
            
            if (load_shift_end_time <= time(NULL)){
                
                load_shift_after_event_interval = 0;
                fprintf(stdout, "Load shift ends and the time is: %u", time(NULL));
                
                // set all P values in SendVENIED1 GOOSE as 0
                SendVENIED1.P1.C1.GGIO_1_21P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_3_22P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_5_23P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_7_24P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_9_25P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_11_26P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_13_27P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_15_28P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_17_29P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_19_30P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_21_31P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_23_48P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_25_49P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_27_50P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_29_51P.AnIn.mag.f = 0;
                SendVENIED1.P1.C1.GGIO_31_52P.AnIn.mag.f = 0;

                // set all P values in SendVENIED2 GOOSE as 0
                SendVENIED2.P1.C1.GGIO_1_53P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_3_54P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_5_55P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_7_56P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_9_57P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_11_59P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_13_60P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_15_61P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_17_62P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_19_63P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_21_64P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_23_65P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_25_66P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_27_67P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_29_68P.AnIn.mag.f = 0;
                SendVENIED2.P1.C1.GGIO_31_69P.AnIn.mag.f = 0;

                // set all P values in SendVENIED3 GOOSE as 0
                SendVENIED3.P1.C1.GGIO_1_70P.AnIn.mag.f = 0;
                SendVENIED3.P1.C1.GGIO_3_42P.AnIn.mag.f = 0;
                SendVENIED3.P1.C1.GGIO_5_43P.AnIn.mag.f = 0;
                SendVENIED3.P1.C1.GGIO_7_44P.AnIn.mag.f = 0;
                SendVENIED3.P1.C1.GGIO_9_45P.AnIn.mag.f = 0;
                SendVENIED3.P1.C1.GGIO_11_46P.AnIn.mag.f = 0;
                SendVENIED3.P1.C1.GGIO_13_47P.AnIn.mag.f = 0;
                SendVENIED3.P1.C1.GGIO_15_47BP.AnIn.mag.f = 0;
                }
            
            interface_gse_send_SendVENIED1_C1_outputs1(1, 600000);
            interface_gse_send_SendVENIED2_C1_outputs2(1, 600000);
            interface_gse_send_SendVENIED3_C1_outputs3(1, 600000);
        } 
            
            
            
        //else if( event_and_load_shift_whole_process_start && (!event_interval_start) && (!load_shift_after_event_interval) ) {
            // both event interval and load shift are completed; need to reset GOOSE for RTDS
            
            
                        
            // send the final SendVENIED1, SendVENIED2, SendVENIED3 GOOSE
            //interface_gse_send_SendVENIED1_C1_outputs1(1, 600000);
            //interface_gse_send_SendVENIED2_C1_outputs2(1, 600000);
            //interface_gse_send_SendVENIED3_C1_outputs3(1, 600000);
            
            // whole process for event and load shift is finished and set the flag to 0
            //event_and_load_shift_whole_process_start = 0;
            
        //}
        
        sleep(10);
    }       
}

