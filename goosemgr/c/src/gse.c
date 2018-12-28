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

#include "ied.h"
#include "gsePacketData.h"
#include "gseDecode.h"
#include "gseEncode.h"






// returns 1 if buf contains valid packet data
int gse_send_E1Q1SB1_C1_Performance(unsigned char *buf, CTYPE_BOOLEAN statusChange, CTYPE_INT32U timeAllowedToLive) {
	E1Q1SB1.S1.C1.LN0.Performance.timeAllowedToLive = timeAllowedToLive;

	if (statusChange) {
		E1Q1SB1.S1.C1.LN0.Performance.stNum++;
		if (E1Q1SB1.S1.C1.LN0.Performance.stNum == 0) {
			E1Q1SB1.S1.C1.LN0.Performance.stNum = 1;
		}
		E1Q1SB1.S1.C1.LN0.Performance.sqNum = 0;
	}
	else {
		E1Q1SB1.S1.C1.LN0.Performance.sqNum++;
		if (E1Q1SB1.S1.C1.LN0.Performance.sqNum == 0) {
			E1Q1SB1.S1.C1.LN0.Performance.sqNum = 1;
		}
	}

	return gseEncodePacket(&E1Q1SB1.S1.C1.LN0.Performance, buf);
}

// returns 1 if buf contains valid packet data
int gse_send_E1Q1SB1_C1_ItlPositions(unsigned char *buf, CTYPE_BOOLEAN statusChange, CTYPE_INT32U timeAllowedToLive) {
	E1Q1SB1.S1.C1.LN0.ItlPositions.timeAllowedToLive = timeAllowedToLive;

	if (statusChange) {
		E1Q1SB1.S1.C1.LN0.ItlPositions.stNum++;
		if (E1Q1SB1.S1.C1.LN0.ItlPositions.stNum == 0) {
			E1Q1SB1.S1.C1.LN0.ItlPositions.stNum = 1;
		}
		E1Q1SB1.S1.C1.LN0.ItlPositions.sqNum = 0;
	}
	else {
		E1Q1SB1.S1.C1.LN0.ItlPositions.sqNum++;
		if (E1Q1SB1.S1.C1.LN0.ItlPositions.sqNum == 0) {
			E1Q1SB1.S1.C1.LN0.ItlPositions.sqNum = 1;
		}
	}

	return gseEncodePacket(&E1Q1SB1.S1.C1.LN0.ItlPositions, buf);
}

// returns 1 if buf contains valid packet data
int gse_send_E1Q1SB1_C1_AnotherPositions(unsigned char *buf, CTYPE_BOOLEAN statusChange, CTYPE_INT32U timeAllowedToLive) {
	E1Q1SB1.S1.C1.LN0.AnotherPositions.timeAllowedToLive = timeAllowedToLive;

	if (statusChange) {
		E1Q1SB1.S1.C1.LN0.AnotherPositions.stNum++;
		if (E1Q1SB1.S1.C1.LN0.AnotherPositions.stNum == 0) {
			E1Q1SB1.S1.C1.LN0.AnotherPositions.stNum = 1;
		}
		E1Q1SB1.S1.C1.LN0.AnotherPositions.sqNum = 0;
	}
	else {
		E1Q1SB1.S1.C1.LN0.AnotherPositions.sqNum++;
		if (E1Q1SB1.S1.C1.LN0.AnotherPositions.sqNum == 0) {
			E1Q1SB1.S1.C1.LN0.AnotherPositions.sqNum = 1;
		}
	}

	return gseEncodePacket(&E1Q1SB1.S1.C1.LN0.AnotherPositions, buf);
}

// returns 1 if buf contains valid packet data
int gse_send_D1Q1SB4_C1_SyckResult(unsigned char *buf, CTYPE_BOOLEAN statusChange, CTYPE_INT32U timeAllowedToLive) {
	D1Q1SB4.S1.C1.LN0.SyckResult.timeAllowedToLive = timeAllowedToLive;

	if (statusChange) {
		D1Q1SB4.S1.C1.LN0.SyckResult.stNum++;
		if (D1Q1SB4.S1.C1.LN0.SyckResult.stNum == 0) {
			D1Q1SB4.S1.C1.LN0.SyckResult.stNum = 1;
		}
		D1Q1SB4.S1.C1.LN0.SyckResult.sqNum = 0;
	}
	else {
		D1Q1SB4.S1.C1.LN0.SyckResult.sqNum++;
		if (D1Q1SB4.S1.C1.LN0.SyckResult.sqNum == 0) {
			D1Q1SB4.S1.C1.LN0.SyckResult.sqNum = 1;
		}
	}

	return gseEncodePacket(&D1Q1SB4.S1.C1.LN0.SyckResult, buf);
}

// returns 1 if buf contains valid packet data
int gse_send_D1Q1SB4_C1_MMXUResult(unsigned char *buf, CTYPE_BOOLEAN statusChange, CTYPE_INT32U timeAllowedToLive) {
	D1Q1SB4.S1.C1.LN0.MMXUResult.timeAllowedToLive = timeAllowedToLive;

	if (statusChange) {
		D1Q1SB4.S1.C1.LN0.MMXUResult.stNum++;
		if (D1Q1SB4.S1.C1.LN0.MMXUResult.stNum == 0) {
			D1Q1SB4.S1.C1.LN0.MMXUResult.stNum = 1;
		}
		D1Q1SB4.S1.C1.LN0.MMXUResult.sqNum = 0;
	}
	else {
		D1Q1SB4.S1.C1.LN0.MMXUResult.sqNum++;
		if (D1Q1SB4.S1.C1.LN0.MMXUResult.sqNum == 0) {
			D1Q1SB4.S1.C1.LN0.MMXUResult.sqNum = 1;
		}
	}

	return gseEncodePacket(&D1Q1SB4.S1.C1.LN0.MMXUResult, buf);
}


// returns 1 if buf contains valid packet data
int gse_send_SendVENIED1_C1_outputs1(unsigned char *buf, CTYPE_BOOLEAN statusChange, CTYPE_INT32U timeAllowedToLive) { 
        SendVENIED1.P1.C1.LN0.outputs1.timeAllowedToLive = timeAllowedToLive;

	if (statusChange) {
                SendVENIED1.P1.C1.LN0.outputs1.stNum++;
                if (SendVENIED1.P1.C1.LN0.outputs1.stNum == 0) {
                        SendVENIED1.P1.C1.LN0.outputs1.stNum = 1;
                }
                SendVENIED1.P1.C1.LN0.outputs1.sqNum = 0;
        }
        else {
               SendVENIED1.P1.C1.LN0.outputs1.sqNum++;
		if (SendVENIED1.P1.C1.LN0.outputs1.sqNum == 0) {
			SendVENIED1.P1.C1.LN0.outputs1.sqNum = 1;
		}
        }
        
	return gseEncodePacket_sourceMAC(&SendVENIED1.P1.C1.LN0.outputs1, buf, VEN_IED1_MAC_ADDRESS);
}


// returns 1 if buf contains valid packet data
int gse_send_SendVENIED2_C1_outputs2(unsigned char *buf, CTYPE_BOOLEAN statusChange, CTYPE_INT32U timeAllowedToLive) { 
        SendVENIED2.P1.C1.LN0.outputs2.timeAllowedToLive = timeAllowedToLive;

	if (statusChange) {
                SendVENIED2.P1.C1.LN0.outputs2.stNum++;
                if (SendVENIED2.P1.C1.LN0.outputs2.stNum == 0) {
                        SendVENIED2.P1.C1.LN0.outputs2.stNum = 1;
                }
                SendVENIED2.P1.C1.LN0.outputs2.sqNum = 0;
        }
        else {
               SendVENIED2.P1.C1.LN0.outputs2.sqNum++;
		if (SendVENIED2.P1.C1.LN0.outputs2.sqNum == 0) {
			SendVENIED2.P1.C1.LN0.outputs2.sqNum = 1;
		}
        }
        
	return gseEncodePacket_sourceMAC(&SendVENIED2.P1.C1.LN0.outputs2, buf, VEN_IED2_MAC_ADDRESS);
}


// returns 1 if buf contains valid packet data
int gse_send_SendVENIED3_C1_outputs3(unsigned char *buf, CTYPE_BOOLEAN statusChange, CTYPE_INT32U timeAllowedToLive) { 
        SendVENIED3.P1.C1.LN0.outputs3.timeAllowedToLive = timeAllowedToLive;

	if (statusChange) {
                SendVENIED3.P1.C1.LN0.outputs3.stNum++;
                if (SendVENIED3.P1.C1.LN0.outputs3.stNum == 0) {
                        SendVENIED3.P1.C1.LN0.outputs3.stNum = 1;
                }
                SendVENIED3.P1.C1.LN0.outputs3.sqNum = 0;
        }
        else {
               SendVENIED3.P1.C1.LN0.outputs3.sqNum++;
		if (SendVENIED3.P1.C1.LN0.outputs3.sqNum == 0) {
			SendVENIED3.P1.C1.LN0.outputs3.sqNum = 1;
		}
        }
        
	return gseEncodePacket_sourceMAC(&SendVENIED3.P1.C1.LN0.outputs3, buf, VEN_IED3_MAC_ADDRESS);
}


void init_gse() {
	E1Q1SB1.S1.C1.LN0.Performance.ethHeaderData.destMACAddress[0] = 0x01;
	E1Q1SB1.S1.C1.LN0.Performance.ethHeaderData.destMACAddress[1] = 0x0C;
	E1Q1SB1.S1.C1.LN0.Performance.ethHeaderData.destMACAddress[2] = 0xCD;
	E1Q1SB1.S1.C1.LN0.Performance.ethHeaderData.destMACAddress[3] = 0x01;
	E1Q1SB1.S1.C1.LN0.Performance.ethHeaderData.destMACAddress[4] = 0x00;
	E1Q1SB1.S1.C1.LN0.Performance.ethHeaderData.destMACAddress[5] = 0x04;
	E1Q1SB1.S1.C1.LN0.Performance.ethHeaderData.APPID = 0x3000;
	E1Q1SB1.S1.C1.LN0.Performance.ethHeaderData.VLAN_PRIORITY = 0x4;
	E1Q1SB1.S1.C1.LN0.Performance.ethHeaderData.VLAN_ID = 0;
	E1Q1SB1.S1.C1.LN0.Performance.goID = (unsigned char *) calloc(1, 12);
	strncpy((char *) E1Q1SB1.S1.C1.LN0.Performance.goID, "Performance\0", 12);
	E1Q1SB1.S1.C1.LN0.Performance.t = 0;
	E1Q1SB1.S1.C1.LN0.Performance.gocbRef = (unsigned char *) calloc(1, 30);
	strncpy((char *) E1Q1SB1.S1.C1.LN0.Performance.gocbRef, "E1Q1SB1C1/LLN0$GO$Performance\0", 30);
	E1Q1SB1.S1.C1.LN0.Performance.datSet = (unsigned char *) calloc(1, 27);
	strncpy((char *) E1Q1SB1.S1.C1.LN0.Performance.datSet, "E1Q1SB1C1/LLN0$Performance\0", 27);
	E1Q1SB1.S1.C1.LN0.Performance.timeAllowedToLive = 0;
	E1Q1SB1.S1.C1.LN0.Performance.stNum = 1;
	E1Q1SB1.S1.C1.LN0.Performance.sqNum = 0;
	E1Q1SB1.S1.C1.LN0.Performance.test = 0;
	E1Q1SB1.S1.C1.LN0.Performance.confRev = 1;
	E1Q1SB1.S1.C1.LN0.Performance.ndsCom = 0;
	E1Q1SB1.S1.C1.LN0.Performance.numDatSetEntries = 2;
	E1Q1SB1.S1.C1.LN0.Performance.encodeDataset = &ber_encode_E1Q1SB1_C1_Performance;
	E1Q1SB1.S1.C1.LN0.Performance.getDatasetLength = &ber_get_length_E1Q1SB1_C1_Performance;
	E1Q1SB1.S1.C1.LN0.Performance.send = &gse_send_E1Q1SB1_C1_Performance;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ethHeaderData.destMACAddress[0] = 0x01;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ethHeaderData.destMACAddress[1] = 0x0C;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ethHeaderData.destMACAddress[2] = 0xCD;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ethHeaderData.destMACAddress[3] = 0x01;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ethHeaderData.destMACAddress[4] = 0x00;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ethHeaderData.destMACAddress[5] = 0x04;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ethHeaderData.APPID = 0x3000;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ethHeaderData.VLAN_PRIORITY = 0x4;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ethHeaderData.VLAN_ID = 0;
	E1Q1SB1.S1.C1.LN0.ItlPositions.goID = (unsigned char *) calloc(1, 4);
	strncpy((char *) E1Q1SB1.S1.C1.LN0.ItlPositions.goID, "Itl\0", 4);
	E1Q1SB1.S1.C1.LN0.ItlPositions.t = 0;
	E1Q1SB1.S1.C1.LN0.ItlPositions.gocbRef = (unsigned char *) calloc(1, 31);
	strncpy((char *) E1Q1SB1.S1.C1.LN0.ItlPositions.gocbRef, "E1Q1SB1C1/LLN0$GO$ItlPositions\0", 31);
	E1Q1SB1.S1.C1.LN0.ItlPositions.datSet = (unsigned char *) calloc(1, 25);
	strncpy((char *) E1Q1SB1.S1.C1.LN0.ItlPositions.datSet, "E1Q1SB1C1/LLN0$Positions\0", 25);
	E1Q1SB1.S1.C1.LN0.ItlPositions.timeAllowedToLive = 0;
	E1Q1SB1.S1.C1.LN0.ItlPositions.stNum = 1;
	E1Q1SB1.S1.C1.LN0.ItlPositions.sqNum = 0;
	E1Q1SB1.S1.C1.LN0.ItlPositions.test = 0;
	E1Q1SB1.S1.C1.LN0.ItlPositions.confRev = 1;
	E1Q1SB1.S1.C1.LN0.ItlPositions.ndsCom = 0;
	E1Q1SB1.S1.C1.LN0.ItlPositions.numDatSetEntries = 4;
	E1Q1SB1.S1.C1.LN0.ItlPositions.encodeDataset = &ber_encode_E1Q1SB1_C1_Positions;
	E1Q1SB1.S1.C1.LN0.ItlPositions.getDatasetLength = &ber_get_length_E1Q1SB1_C1_Positions;
	E1Q1SB1.S1.C1.LN0.ItlPositions.send = &gse_send_E1Q1SB1_C1_ItlPositions;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ethHeaderData.destMACAddress[0] = 0x01;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ethHeaderData.destMACAddress[1] = 0x0C;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ethHeaderData.destMACAddress[2] = 0xCD;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ethHeaderData.destMACAddress[3] = 0x01;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ethHeaderData.destMACAddress[4] = 0x00;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ethHeaderData.destMACAddress[5] = 0x04;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ethHeaderData.APPID = 0x3000;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ethHeaderData.VLAN_PRIORITY = 0x4;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ethHeaderData.VLAN_ID = 0;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.goID = (unsigned char *) calloc(1, 4);
	strncpy((char *) E1Q1SB1.S1.C1.LN0.AnotherPositions.goID, "Itl\0", 4);
	E1Q1SB1.S1.C1.LN0.AnotherPositions.t = 0;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.gocbRef = (unsigned char *) calloc(1, 35);
	strncpy((char *) E1Q1SB1.S1.C1.LN0.AnotherPositions.gocbRef, "E1Q1SB1C1/LLN0$GO$AnotherPositions\0", 35);
	E1Q1SB1.S1.C1.LN0.AnotherPositions.datSet = (unsigned char *) calloc(1, 25);
	strncpy((char *) E1Q1SB1.S1.C1.LN0.AnotherPositions.datSet, "E1Q1SB1C1/LLN0$Positions\0", 25);
	E1Q1SB1.S1.C1.LN0.AnotherPositions.timeAllowedToLive = 0;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.stNum = 1;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.sqNum = 0;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.test = 0;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.confRev = 1;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.ndsCom = 0;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.numDatSetEntries = 4;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.encodeDataset = &ber_encode_E1Q1SB1_C1_Positions;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.getDatasetLength = &ber_get_length_E1Q1SB1_C1_Positions;
	E1Q1SB1.S1.C1.LN0.AnotherPositions.send = &gse_send_E1Q1SB1_C1_AnotherPositions;
	D1Q1SB4.S1.C1.LN0.SyckResult.ethHeaderData.destMACAddress[0] = 0x01;
	D1Q1SB4.S1.C1.LN0.SyckResult.ethHeaderData.destMACAddress[1] = 0x0C;
	D1Q1SB4.S1.C1.LN0.SyckResult.ethHeaderData.destMACAddress[2] = 0xCD;
	D1Q1SB4.S1.C1.LN0.SyckResult.ethHeaderData.destMACAddress[3] = 0x01;
	D1Q1SB4.S1.C1.LN0.SyckResult.ethHeaderData.destMACAddress[4] = 0x00;
	D1Q1SB4.S1.C1.LN0.SyckResult.ethHeaderData.destMACAddress[5] = 0x02;
	D1Q1SB4.S1.C1.LN0.SyckResult.ethHeaderData.APPID = 0x3001;
	D1Q1SB4.S1.C1.LN0.SyckResult.ethHeaderData.VLAN_PRIORITY = 0x4;
	D1Q1SB4.S1.C1.LN0.SyckResult.ethHeaderData.VLAN_ID = 0;
	D1Q1SB4.S1.C1.LN0.SyckResult.goID = (unsigned char *) calloc(1, 7);
	strncpy((char *) D1Q1SB4.S1.C1.LN0.SyckResult.goID, "SynChk\0", 7);
	D1Q1SB4.S1.C1.LN0.SyckResult.t = 0;
	D1Q1SB4.S1.C1.LN0.SyckResult.gocbRef = (unsigned char *) calloc(1, 29);
	strncpy((char *) D1Q1SB4.S1.C1.LN0.SyckResult.gocbRef, "D1Q1SB4C1/LLN0$GO$SyckResult\0", 29);
	D1Q1SB4.S1.C1.LN0.SyckResult.datSet = (unsigned char *) calloc(1, 26);
	strncpy((char *) D1Q1SB4.S1.C1.LN0.SyckResult.datSet, "D1Q1SB4C1/LLN0$SyckResult\0", 26);
	D1Q1SB4.S1.C1.LN0.SyckResult.timeAllowedToLive = 0;
	D1Q1SB4.S1.C1.LN0.SyckResult.stNum = 1;
	D1Q1SB4.S1.C1.LN0.SyckResult.sqNum = 0;
	D1Q1SB4.S1.C1.LN0.SyckResult.test = 0;
	D1Q1SB4.S1.C1.LN0.SyckResult.confRev = 0;
	D1Q1SB4.S1.C1.LN0.SyckResult.ndsCom = 0;
	D1Q1SB4.S1.C1.LN0.SyckResult.numDatSetEntries = 1;
	D1Q1SB4.S1.C1.LN0.SyckResult.encodeDataset = &ber_encode_D1Q1SB4_C1_SyckResult;
	D1Q1SB4.S1.C1.LN0.SyckResult.getDatasetLength = &ber_get_length_D1Q1SB4_C1_SyckResult;
	D1Q1SB4.S1.C1.LN0.SyckResult.send = &gse_send_D1Q1SB4_C1_SyckResult;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ethHeaderData.destMACAddress[0] = 0x01;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ethHeaderData.destMACAddress[1] = 0x0C;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ethHeaderData.destMACAddress[2] = 0xCD;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ethHeaderData.destMACAddress[3] = 0x01;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ethHeaderData.destMACAddress[4] = 0x00;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ethHeaderData.destMACAddress[5] = 0x02;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ethHeaderData.APPID = 0x3001;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ethHeaderData.VLAN_PRIORITY = 0x4;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ethHeaderData.VLAN_ID = 0;
	D1Q1SB4.S1.C1.LN0.MMXUResult.goID = (unsigned char *) calloc(1, 11);
	strncpy((char *) D1Q1SB4.S1.C1.LN0.MMXUResult.goID, "MMXUResult\0", 11);
	D1Q1SB4.S1.C1.LN0.MMXUResult.t = 0;
	D1Q1SB4.S1.C1.LN0.MMXUResult.gocbRef = (unsigned char *) calloc(1, 29);
	strncpy((char *) D1Q1SB4.S1.C1.LN0.MMXUResult.gocbRef, "D1Q1SB4C1/LLN0$GO$MMXUResult\0", 29);
	D1Q1SB4.S1.C1.LN0.MMXUResult.datSet = (unsigned char *) calloc(1, 26);
	strncpy((char *) D1Q1SB4.S1.C1.LN0.MMXUResult.datSet, "D1Q1SB4C1/LLN0$MMXUResult\0", 26);
	D1Q1SB4.S1.C1.LN0.MMXUResult.timeAllowedToLive = 0;
	D1Q1SB4.S1.C1.LN0.MMXUResult.stNum = 1;
	D1Q1SB4.S1.C1.LN0.MMXUResult.sqNum = 0;
	D1Q1SB4.S1.C1.LN0.MMXUResult.test = 0;
	D1Q1SB4.S1.C1.LN0.MMXUResult.confRev = 0;
	D1Q1SB4.S1.C1.LN0.MMXUResult.ndsCom = 0;
	D1Q1SB4.S1.C1.LN0.MMXUResult.numDatSetEntries = 1;
	D1Q1SB4.S1.C1.LN0.MMXUResult.encodeDataset = &ber_encode_D1Q1SB4_C1_MMXUResult;
	D1Q1SB4.S1.C1.LN0.MMXUResult.getDatasetLength = &ber_get_length_D1Q1SB4_C1_MMXUResult;
	D1Q1SB4.S1.C1.LN0.MMXUResult.send = &gse_send_D1Q1SB4_C1_MMXUResult;
        
        
        //initialize VENIED1.P1.C1.LN0.outputs1 (logical node)
        SendVENIED1.P1.C1.LN0.outputs1.ethHeaderData.destMACAddress[0] = 0x01;
        SendVENIED1.P1.C1.LN0.outputs1.ethHeaderData.destMACAddress[1] = 0x0C;
        SendVENIED1.P1.C1.LN0.outputs1.ethHeaderData.destMACAddress[2] = 0xCD;
        SendVENIED1.P1.C1.LN0.outputs1.ethHeaderData.destMACAddress[3] = 0x01;
        SendVENIED1.P1.C1.LN0.outputs1.ethHeaderData.destMACAddress[4] = 0x01;
        SendVENIED1.P1.C1.LN0.outputs1.ethHeaderData.destMACAddress[5] = 0x34;
        SendVENIED1.P1.C1.LN0.outputs1.ethHeaderData.APPID = 0x0003;
        SendVENIED1.P1.C1.LN0.outputs1.ethHeaderData.VLAN_PRIORITY = 0x04;
        SendVENIED1.P1.C1.LN0.outputs1.ethHeaderData.VLAN_ID = 0;
        SendVENIED1.P1.C1.LN0.outputs1.goID = (unsigned char *) calloc(1, 2);
        strncpy((char *) SendVENIED1.P1.C1.LN0.outputs1.goID, "1\0", 2);
        SendVENIED1.P1.C1.LN0.outputs1.t = 0;
        SendVENIED1.P1.C1.LN0.outputs1.gocbRef = (unsigned char *) calloc(1, 24);
        strncpy((char *) SendVENIED1.P1.C1.LN0.outputs1.gocbRef, "VENIED1C1/LLN0$GO$Gcb01\0", 24);
        SendVENIED1.P1.C1.LN0.outputs1.datSet = (unsigned char *) calloc(1, 24);
        strncpy((char *) SendVENIED1.P1.C1.LN0.outputs1.datSet, "VENIED1C1/LLN0$outputs1\0", 24);
        SendVENIED1.P1.C1.LN0.outputs1.timeAllowedToLive = 0;
        SendVENIED1.P1.C1.LN0.outputs1.stNum = 1;
        SendVENIED1.P1.C1.LN0.outputs1.sqNum = 0;
        SendVENIED1.P1.C1.LN0.outputs1.test = 0;
        SendVENIED1.P1.C1.LN0.outputs1.confRev = 1;
        SendVENIED1.P1.C1.LN0.outputs1.ndsCom = 0;
        SendVENIED1.P1.C1.LN0.outputs1.numDatSetEntries = 32;
        SendVENIED1.P1.C1.LN0.outputs1.encodeDataset = &ber_encode_SendVENIED1_C1_outputs1;
        SendVENIED1.P1.C1.LN0.outputs1.getDatasetLength = &ber_get_length_SendVENIED1_C1_outputs1;
        SendVENIED1.P1.C1.LN0.outputs1.send = &gse_send_SendVENIED1_C1_outputs1;
        
        
        //initialize VENIED2.P1.C1.LN0.outputs2 (logical node)
        SendVENIED2.P1.C1.LN0.outputs2.ethHeaderData.destMACAddress[0] = 0x01;
        SendVENIED2.P1.C1.LN0.outputs2.ethHeaderData.destMACAddress[1] = 0x0C;
        SendVENIED2.P1.C1.LN0.outputs2.ethHeaderData.destMACAddress[2] = 0xCD;
        SendVENIED2.P1.C1.LN0.outputs2.ethHeaderData.destMACAddress[3] = 0x01;
        SendVENIED2.P1.C1.LN0.outputs2.ethHeaderData.destMACAddress[4] = 0x01;
        SendVENIED2.P1.C1.LN0.outputs2.ethHeaderData.destMACAddress[5] = 0x35;
        SendVENIED2.P1.C1.LN0.outputs2.ethHeaderData.APPID = 0x0003;
        SendVENIED2.P1.C1.LN0.outputs2.ethHeaderData.VLAN_PRIORITY = 0x04;
        SendVENIED2.P1.C1.LN0.outputs2.ethHeaderData.VLAN_ID = 0;
        SendVENIED2.P1.C1.LN0.outputs2.goID = (unsigned char *) calloc(1, 2);
        strncpy((char *) SendVENIED2.P1.C1.LN0.outputs2.goID, "1\0", 2);
        SendVENIED2.P1.C1.LN0.outputs2.t = 0;
        SendVENIED2.P1.C1.LN0.outputs2.gocbRef = (unsigned char *) calloc(1, 24);
        strncpy((char *) SendVENIED2.P1.C1.LN0.outputs2.gocbRef, "VENIED2C1/LLN0$GO$Gcb01\0", 24);
        SendVENIED2.P1.C1.LN0.outputs2.datSet = (unsigned char *) calloc(1, 24);
        strncpy((char *) SendVENIED2.P1.C1.LN0.outputs2.datSet, "VENIED2C1/LLN0$outputs2\0", 24);
        SendVENIED2.P1.C1.LN0.outputs2.timeAllowedToLive = 0;
        SendVENIED2.P1.C1.LN0.outputs2.stNum = 1;
        SendVENIED2.P1.C1.LN0.outputs2.sqNum = 0;
        SendVENIED2.P1.C1.LN0.outputs2.test = 0;
        SendVENIED2.P1.C1.LN0.outputs2.confRev = 1;
        SendVENIED2.P1.C1.LN0.outputs2.ndsCom = 0;
        SendVENIED2.P1.C1.LN0.outputs2.numDatSetEntries = 32;
        SendVENIED2.P1.C1.LN0.outputs2.encodeDataset = &ber_encode_SendVENIED2_C1_outputs2;
        SendVENIED2.P1.C1.LN0.outputs2.getDatasetLength = &ber_get_length_SendVENIED2_C1_outputs2;
        SendVENIED2.P1.C1.LN0.outputs2.send = &gse_send_SendVENIED2_C1_outputs2;
        
        
        //initialize VENIED3.P1.C1.LN0.outputs3 (logical node)
        SendVENIED3.P1.C1.LN0.outputs3.ethHeaderData.destMACAddress[0] = 0x01;
        SendVENIED3.P1.C1.LN0.outputs3.ethHeaderData.destMACAddress[1] = 0x0C;
        SendVENIED3.P1.C1.LN0.outputs3.ethHeaderData.destMACAddress[2] = 0xCD;
        SendVENIED3.P1.C1.LN0.outputs3.ethHeaderData.destMACAddress[3] = 0x01;
        SendVENIED3.P1.C1.LN0.outputs3.ethHeaderData.destMACAddress[4] = 0x01;
        SendVENIED3.P1.C1.LN0.outputs3.ethHeaderData.destMACAddress[5] = 0x36;
        SendVENIED3.P1.C1.LN0.outputs3.ethHeaderData.APPID = 0x0003;
        SendVENIED3.P1.C1.LN0.outputs3.ethHeaderData.VLAN_PRIORITY = 0x04;
        SendVENIED3.P1.C1.LN0.outputs3.ethHeaderData.VLAN_ID = 0;
        SendVENIED3.P1.C1.LN0.outputs3.goID = (unsigned char *) calloc(1, 2);
        strncpy((char *) SendVENIED3.P1.C1.LN0.outputs3.goID, "1\0", 2);
        SendVENIED3.P1.C1.LN0.outputs3.t = 0;
        SendVENIED3.P1.C1.LN0.outputs3.gocbRef = (unsigned char *) calloc(1, 24);
        strncpy((char *) SendVENIED3.P1.C1.LN0.outputs3.gocbRef, "VENIED2C1/LLN0$GO$Gcb01\0", 24);
        SendVENIED3.P1.C1.LN0.outputs3.datSet = (unsigned char *) calloc(1, 24);
        strncpy((char *) SendVENIED3.P1.C1.LN0.outputs3.datSet, "VENIED2C1/LLN0$outputs2\0", 24);
        SendVENIED3.P1.C1.LN0.outputs3.timeAllowedToLive = 0;
        SendVENIED3.P1.C1.LN0.outputs3.stNum = 1;
        SendVENIED3.P1.C1.LN0.outputs3.sqNum = 0;
        SendVENIED3.P1.C1.LN0.outputs3.test = 0;
        SendVENIED3.P1.C1.LN0.outputs3.confRev = 1;
        SendVENIED3.P1.C1.LN0.outputs3.ndsCom = 0;
        SendVENIED3.P1.C1.LN0.outputs3.numDatSetEntries = 16;
        SendVENIED3.P1.C1.LN0.outputs3.encodeDataset = &ber_encode_SendVENIED3_C1_outputs3;
        SendVENIED3.P1.C1.LN0.outputs3.getDatasetLength = &ber_get_length_SendVENIED3_C1_outputs3;
        SendVENIED3.P1.C1.LN0.outputs3.send = &gse_send_SendVENIED3_C1_outputs3;
}

