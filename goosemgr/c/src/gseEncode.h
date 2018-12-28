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

#ifndef GSE_ENCODE_H
#define GSE_ENCODE_H

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

#include "gseEncodeBasic.h"
#include "gsePacketData.h"




int ber_get_length_E1Q1SB1_C1_Performance();
int ber_encode_E1Q1SB1_C1_Performance(unsigned char *buf);
int ber_encode_control_E1Q1SB1_C1_Performance(unsigned char *buf);
int ber_get_length_E1Q1SB1_C1_Positions();
int ber_encode_E1Q1SB1_C1_Positions(unsigned char *buf);
int ber_encode_control_E1Q1SB1_C1_ItlPositions(unsigned char *buf);
int ber_encode_control_E1Q1SB1_C1_AnotherPositions(unsigned char *buf);
int ber_get_length_E1Q1SB1_C1_Measurands();
int ber_encode_E1Q1SB1_C1_Measurands(unsigned char *buf);
int ber_get_length_E1Q1SB1_C1_smv();
int ber_encode_E1Q1SB1_C1_smv(unsigned char *buf);
int ber_get_length_E1Q1SB1_C1_rmxu();
int ber_encode_E1Q1SB1_C1_rmxu(unsigned char *buf);
int ber_get_length_D1Q1SB4_C1_SyckResult();
int ber_encode_D1Q1SB4_C1_SyckResult(unsigned char *buf);
int ber_encode_control_D1Q1SB4_C1_SyckResult(unsigned char *buf);
int ber_get_length_D1Q1SB4_C1_MMXUResult();
int ber_encode_D1Q1SB4_C1_MMXUResult(unsigned char *buf);
int ber_encode_control_D1Q1SB4_C1_MMXUResult(unsigned char *buf);
int gseEncodePacket(struct gseControl *gseControl, unsigned char *buf);


int gseEncodePacket_sourceMAC(struct gseControl *gseControl, unsigned char *buf, unsigned char *sourceMAC);


int ber_encode_SendVENIED1_C1_outputs1(unsigned char *buf);
int ber_get_length_SendVENIED1_C1_outputs1();
//int ber_encode_myAnalogValue_no_struct();
//int gseEncodePacket_noVLAN(struct gseControl *gseControl, unsigned char *buf);

int ber_encode_SendVENIED2_C1_outputs2(unsigned char *buf);
int ber_get_length_SendVENIED2_C1_outputs2();

int ber_encode_SendVENIED3_C1_outputs3(unsigned char *buf);
int ber_get_length_SendVENIED3_C1_outputs3();



#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
