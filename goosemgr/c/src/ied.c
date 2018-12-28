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
#include "datatypes.h"


struct E1Q1SB1_t E1Q1SB1;
struct E1Q1BP2_t E1Q1BP2;
struct E1Q1BP3_t E1Q1BP3;
struct E1Q2SB1_t E1Q2SB1;
struct E1Q3SB1_t E1Q3SB1;
struct E1Q3KA1_t E1Q3KA1;
struct E1Q3KA2_t E1Q3KA2;
struct E1Q3KA3_t E1Q3KA3;
struct D1Q1SB1_t D1Q1SB1;
struct D1Q1BP2_t D1Q1BP2;
struct D1Q1BP3_t D1Q1BP3;
struct D1Q1SB4_t D1Q1SB4;

// declare struct type ReceiveGTNET1_t for IED GTNET1 
// which is used to decode the incoming GOOSE from IED GTNET1 of RTDS
struct ReceiveGTNET1_t ReceiveGTNET1;

// declare struct type ReceiveGTNET2_t for IED GTNET2 
// which is used to decode the incoming GOOSE from IED GTNET2 of RTDS
struct ReceiveGTNET2_t ReceiveGTNET2;

// declare struct type ReceiveGTNET3_t for IED GTNET3 
// which is used to decode the incoming GOOSE from IED GTNET3 of RTDS
struct ReceiveGTNET3_t ReceiveGTNET3;


// declare struct type SendVENIED1_t for IED VENIED1
// which is used to encode and send outgoing GOOSE to IED GTNET1 of RTDS
struct SendVENIED1_t SendVENIED1;

// declare struct type SendVENIED2_t for IED VENIED2
// which is used to encode and send outgoing GOOSE to IED GTNET2 of RTDS
struct SendVENIED2_t SendVENIED2;

// declare struct type SendVENIED3_t for IED VENIED3
// which is used to encode and send outgoing GOOSE to IED GTNET3 of RTDS
struct SendVENIED3_t SendVENIED3;




