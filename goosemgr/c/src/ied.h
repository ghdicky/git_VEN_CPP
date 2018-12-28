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

#ifndef IED_H
#define IED_H

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

#include "datatypes.h"
#include "sv.h"
#include "gse.h"

// According to scd.hml in /emf/src/rapid61850/scd.xml
// IED E1Q1SB1 contains 7 logical nodes LN0, exampleRMXU, LPHDa, CSWIa, CSWIa, MMXUa and TVTRa 
struct E1Q1SB1_t {
	struct {
		struct {
			struct {
				struct LN0 LLN0;
				struct svControl PerformanceSV;
				struct gseControl Performance;
				struct gseControl ItlPositions;
				struct gseControl AnotherPositions;
				struct svControl Volt;
				struct svControl rmxuCB;
			} LN0;
			struct exampleRMXU exampleRMXU_1;
			struct LPHDa LPHDa_1;
			struct CSWIa CSWIa_1;
			struct CSWIa CSWIa_2;
			struct MMXUa MMXUa_1;
			struct TVTRa TVTRa_1;
		} C1;
	} S1;
};

struct E1Q1BP2_t {
	struct {
	} S1;
};

struct E1Q1BP3_t {
	struct {
	} S1;
};

struct E1Q2SB1_t {
	struct {
	} S1;
};

struct E1Q3SB1_t {
	struct {
	} S1;
};

struct E1Q3KA1_t {
	struct {
	} S1;
};

struct E1Q3KA2_t {
	struct {
	} S1;
};

struct E1Q3KA3_t {
	struct {
	} S1;
};

struct D1Q1SB1_t {
	struct {
	} S1;
};

struct D1Q1BP2_t {
	struct {
	} S1;
};

struct D1Q1BP3_t {
	struct {
	} S1;
};

// According to scd.hml in /emf/src/rapid61850/scd.xml
// IED D1Q1SB4 contains 4 logical nodes LN0, exampleMMXU, LPHDa and RSYNa 
struct D1Q1SB4_t {
	struct {
		struct {
			struct {
				struct LN0 LLN0;
				struct gseControl SyckResult;
				struct gseControl MMXUResult;
			} LN0;
			struct exampleMMXU exampleMMXU_1;
			struct LPHDa LPHDa_1;
			struct RSYNa RSYNa_1;
		} C1;
	} S1;
};

// define struct type ReceiveGTNET1_t which would store the received GOOSE of IED GTNET1
// to keep it simple, this ReceiveGTNET1 only contains one struct to store all 64 data items GGIO_1 TO GGIO_64
// the exact data structure [logical node]$[Data Object]$[data attribute] is not modelled.
struct ReceiveGTNET1_t {
        //struct {
        //        struct {
        //                struct {
        //                        struct LN0 LLN0;
        //                        struct gseControl Gcb01; // map to the name in <GSEControl name="Gcb01" datSet="outputs1" confRev="1" appID="1"/> of LN0
        //                } LN0;
        //        } GTNET_CTRL1;
        //} P1;
        
        struct GTNET1_C1_outputs1 received_gtnet_c1_outputs1;
        
};

// define struct type ReceiveGTNET2_t which would store the received GOOSE of IED GTNET2
// to keep it simple, this ReceiveGTNET2 only contains one struct to store all 64 data items GGIO_65 TO GGIO_128
// the exact data structure [logical node]$[Data Object]$[data attribute] is not modelled.
struct ReceiveGTNET2_t {
        //struct {
        //        struct {
        //                struct {
        //                        struct LN0 LLN0;
        //                        struct gseControl Gcb01; // map to the name in <GSEControl name="Gcb01" datSet="outputs1" confRev="1" appID="1"/> of LN0
        //                } LN0;
        //        } GTNET_CTRL1;
        //} P1;
        
        struct GTNET2_C1_outputs2 received_gtnet_c1_outputs2;
        
};

// define struct type ReceiveGTNET3_t which would store the received GOOSE of IED GTNET3
// to keep it simple, this ReceiveGTNET3 only contains one struct to store all 64 data items GGIO_126 TO GGIO_192
// the exact data structure [logical node]$[Data Object]$[data attribute] is not modelled.
struct ReceiveGTNET3_t {
        //struct {
        //        struct {
        //                struct {
        //                        struct LN0 LLN0;
        //                        struct gseControl Gcb01; // map to the name in <GSEControl name="Gcb01" datSet="outputs1" confRev="1" appID="1"/> of LN0
        //                } LN0;
        //        } GTNET_CTRL1;
        //} P1;
        
        struct GTNET3_C1_outputs3 received_gtnet_c1_outputs3;
        
};

// define struct type SendVENIED1_t which will be represent as VENIED1 seen by RTDS
// IED VENIED1 contains 1 logical node LN0 
struct SendVENIED1_t {
	struct {
		struct {
			struct {
				struct LN0 LLN0;
				struct gseControl outputs1;
			} LN0;
                        struct GGIO GGIO_1_21P; // LN GGIO_1 for House 21 P
                        struct GGIO GGIO_2_21Q; // LN GGIO_2 for House 21 Q
                        struct GGIO GGIO_3_22P; // LN GGIO_3 for House 22 P
                        struct GGIO GGIO_4_22Q; // LN GGIO_4 for House 22 Q
                        struct GGIO GGIO_5_23P; // LN GGIO_5 for House 23 P
                        struct GGIO GGIO_6_23Q; // LN GGIO_6 for House 23 Q
                        struct GGIO GGIO_7_24P; // LN GGIO_7 for House 24 P
                        struct GGIO GGIO_8_24Q; // LN GGIO_8 for House 24 Q
                        struct GGIO GGIO_9_25P; // LN GGIO_9 for House 25 P
                        struct GGIO GGIO_10_25Q; // LN GGIO_10 for House 25 Q
                        
                        struct GGIO GGIO_11_26P; // LN GGIO_11 for House 26 P
                        struct GGIO GGIO_12_26Q; // LN GGIO_12 for House 26 Q
                        struct GGIO GGIO_13_27P; // LN GGIO_13 for House 27 P
                        struct GGIO GGIO_14_27Q; // LN GGIO_14 for House 27 Q
                        struct GGIO GGIO_15_28P; // LN GGIO_15 for House 28 P
                        struct GGIO GGIO_16_28Q; // LN GGIO_16 for House 28 Q
                        struct GGIO GGIO_17_29P; // LN GGIO_17 for House 29 P
                        struct GGIO GGIO_18_29Q; // LN GGIO_18 for House 29 Q
                        struct GGIO GGIO_19_30P; // LN GGIO_19 for House 30 P
                        struct GGIO GGIO_20_30Q; // LN GGIO_20 for House 30 Q
                        
                        struct GGIO GGIO_21_31P; // LN GGIO_21 for House 31 P
                        struct GGIO GGIO_22_31Q; // LN GGIO_22 for House 31 Q
                        struct GGIO GGIO_23_48P; // LN GGIO_23 for House 48 P
                        struct GGIO GGIO_24_48Q; // LN GGIO_24 for House 48 Q
                        struct GGIO GGIO_25_49P; // LN GGIO_25 for House 49 P
                        struct GGIO GGIO_26_49Q; // LN GGIO_26 for House 49 Q
                        struct GGIO GGIO_27_50P; // LN GGIO_27 for House 50 P
                        struct GGIO GGIO_28_50Q; // LN GGIO_28 for House 50 Q
                        struct GGIO GGIO_29_51P; // LN GGIO_29 for House 51 P
                        struct GGIO GGIO_30_51Q; // LN GGIO_30 for House 51 Q
                        
                        struct GGIO GGIO_31_52P; // LN GGIO_31 for House 52 P
                        struct GGIO GGIO_32_52Q; // LN GGIO_32 for House 52 Q
                        //struct GGIO GGIO_33_53P; // LN GGIO_33 for House 53 P
                        //struct GGIO GGIO_34_53Q; // LN GGIO_34 for House 53 Q
                        //struct GGIO GGIO_35_54P; // LN GGIO_35 for House 54 P
                        //struct GGIO GGIO_36_54Q; // LN GGIO_36 for House 54 Q
                        //struct GGIO GGIO_37_55P; // LN GGIO_37 for House 55 P
                        //struct GGIO GGIO_38_55Q; // LN GGIO_38 for House 55 Q
                        //struct GGIO GGIO_39_56P; // LN GGIO_39 for House 56 P
                        //struct GGIO GGIO_40_56Q; // LN GGIO_40 for House 56 Q
                        
                        //struct GGIO GGIO_41_57P; // LN GGIO_41 for House 57 P
                        //struct GGIO GGIO_42_57Q; // LN GGIO_42 for House 57 Q
                        //struct GGIO GGIO_43_59P; // LN GGIO_43 for House 59 P
                        //struct GGIO GGIO_44_59Q; // LN GGIO_44 for House 59 Q
                        //struct GGIO GGIO_45_60P; // LN GGIO_45 for House 60 P
                        //struct GGIO GGIO_46_60Q; // LN GGIO_46 for House 60 Q
                        //struct GGIO GGIO_47_61P; // LN GGIO_47 for House 61 P
                        //struct GGIO GGIO_48_61Q; // LN GGIO_48 for House 61 Q
                        //struct GGIO GGIO_49_62P; // LN GGIO_49 for House 62 P
                        //struct GGIO GGIO_50_62Q; // LN GGIO_50 for House 62 Q
                        
                        //struct GGIO GGIO_51_63P; // LN GGIO_51 for House 63 P
                        //struct GGIO GGIO_52_63Q; // LN GGIO_52 for House 63 Q
                        //struct GGIO GGIO_53_64P; // LN GGIO_53 for House 64 P
                        //struct GGIO GGIO_54_64Q; // LN GGIO_54 for House 64 Q
                        //struct GGIO GGIO_55_65P; // LN GGIO_55 for House 65 P
                        //struct GGIO GGIO_56_65Q; // LN GGIO_56 for House 65 Q
                        //struct GGIO GGIO_57_66P; // LN GGIO_57 for House 66 P
                        //struct GGIO GGIO_58_66Q; // LN GGIO_58 for House 66 Q
                        //struct GGIO GGIO_59_67P; // LN GGIO_59 for House 67 P
                        //struct GGIO GGIO_60_67Q; // LN GGIO_60 for House 67 Q
                        
                        //struct GGIO GGIO_61_68P; // LN GGIO_61 for House 68 P
                        //struct GGIO GGIO_62_68Q; // LN GGIO_62 for House 68 Q
                        //struct GGIO GGIO_63_69P; // LN GGIO_63 for House 69 P
                        //struct GGIO GGIO_64_69Q; // LN GGIO_64 for House 69 Q   
		} C1;
	} P1;
};

// define struct type SendVENIED2_t which will be represent VENIED2 seen by RTDS
// IED VENIED2 contains 1 logical node LN0 
struct SendVENIED2_t {
	struct {
		struct {
			struct {
				struct LN0 LLN0;
				struct gseControl outputs2;
			} LN0;
                        struct GGIO GGIO_1_53P; // LN GGIO_1 for House 53 P
                        struct GGIO GGIO_2_53Q; // LN GGIO_2 for House 53 Q
                        struct GGIO GGIO_3_54P; // LN GGIO_3 for Section 54 P
                        struct GGIO GGIO_4_54Q; // LN GGIO_4 for Section 54 Q
                        struct GGIO GGIO_5_55P; // LN GGIO_5 for Section 55 P
                        struct GGIO GGIO_6_55Q; // LN GGIO_6 for Section 55 Q
                        struct GGIO GGIO_7_56P; // LN GGIO_7 for Section 56 P
                        struct GGIO GGIO_8_56Q; // LN GGIO_8 for Section 56 Q 
                        struct GGIO GGIO_9_57P; // LN GGIO_7 for Section 57 P
                        struct GGIO GGIO_10_57Q; // LN GGIO_8 for Section 57 Q
                        
                        struct GGIO GGIO_11_59P; // LN GGIO_1 for House 59 P
                        struct GGIO GGIO_12_59Q; // LN GGIO_2 for House 59 Q
                        struct GGIO GGIO_13_60P; // LN GGIO_3 for Section 60 P
                        struct GGIO GGIO_14_60Q; // LN GGIO_4 for Section 60 Q
                        struct GGIO GGIO_15_61P; // LN GGIO_5 for Section 61 P
                        struct GGIO GGIO_16_61Q; // LN GGIO_6 for Section 61 Q
                        struct GGIO GGIO_17_62P; // LN GGIO_7 for Section 62 P
                        struct GGIO GGIO_18_62Q; // LN GGIO_8 for Section 62 Q 
                        struct GGIO GGIO_19_63P; // LN GGIO_7 for Section 63 P
                        struct GGIO GGIO_20_63Q; // LN GGIO_8 for Section 63 Q
                        
                        struct GGIO GGIO_21_64P; // LN GGIO_1 for House 64 P
                        struct GGIO GGIO_22_64Q; // LN GGIO_2 for House 64 Q
                        struct GGIO GGIO_23_65P; // LN GGIO_3 for Section 65 P
                        struct GGIO GGIO_24_65Q; // LN GGIO_4 for Section 65 Q
                        struct GGIO GGIO_25_66P; // LN GGIO_5 for Section 66 P
                        struct GGIO GGIO_26_66Q; // LN GGIO_6 for Section 66 Q
                        struct GGIO GGIO_27_67P; // LN GGIO_7 for Section 67 P
                        struct GGIO GGIO_28_67Q; // LN GGIO_8 for Section 67 Q 
                        struct GGIO GGIO_29_68P; // LN GGIO_7 for Section 68 P
                        struct GGIO GGIO_30_68Q; // LN GGIO_8 for Section 68 Q
                        
                        struct GGIO GGIO_31_69P; // LN GGIO_7 for Section 69 P
                        struct GGIO GGIO_32_69Q; // LN GGIO_8 for Section 69 Q
		} C1;
	} P1;
};

// define struct type SendVENIED3_t which will be represent VENIED3 seen by RTDS
// IED VENIED3 contains 1 logical node LN0 
struct SendVENIED3_t {
	struct {
		struct {
			struct {
				struct LN0 LLN0;
				struct gseControl outputs3;
			} LN0;
                        struct GGIO GGIO_1_70P; // LN GGIO_1 for House 70 P
                        struct GGIO GGIO_2_70Q; // LN GGIO_2 for House 70 Q
                        struct GGIO GGIO_3_42P; // LN GGIO_3 for Section 42 P
                        struct GGIO GGIO_4_42Q; // LN GGIO_4 for Section 42 Q
                        struct GGIO GGIO_5_43P; // LN GGIO_5 for Section 43 P
                        struct GGIO GGIO_6_43Q; // LN GGIO_6 for Section 43 Q
                        struct GGIO GGIO_7_44P; // LN GGIO_7 for Section 44 P
                        struct GGIO GGIO_8_44Q; // LN GGIO_8 for Section 44 Q 
                        struct GGIO GGIO_9_45P; // LN GGIO_7 for Section 45 P
                        struct GGIO GGIO_10_45Q; // LN GGIO_8 for Section 45 Q
                        
                        struct GGIO GGIO_11_46P; // LN GGIO_1 for House 46 P
                        struct GGIO GGIO_12_46Q; // LN GGIO_2 for House 46 Q
                        struct GGIO GGIO_13_47P; // LN GGIO_3 for Section 47 P
                        struct GGIO GGIO_14_47Q; // LN GGIO_4 for Section 47 Q
                        struct GGIO GGIO_15_47BP; // LN GGIO_5 for Section 47B P
                        struct GGIO GGIO_16_47BQ; // LN GGIO_6 for Section 47B Q
		} C1;
	} P1;
};






extern struct E1Q1SB1_t E1Q1SB1;
extern struct E1Q1BP2_t E1Q1BP2;
extern struct E1Q1BP3_t E1Q1BP3;
extern struct E1Q2SB1_t E1Q2SB1;
extern struct E1Q3SB1_t E1Q3SB1;
extern struct E1Q3KA1_t E1Q3KA1;
extern struct E1Q3KA2_t E1Q3KA2;
extern struct E1Q3KA3_t E1Q3KA3;
extern struct D1Q1SB1_t D1Q1SB1;
extern struct D1Q1BP2_t D1Q1BP2;
extern struct D1Q1BP3_t D1Q1BP3;
extern struct D1Q1SB4_t D1Q1SB4;

extern struct ReceiveGTNET1_t ReceiveGTNET1;
extern struct ReceiveGTNET2_t ReceiveGTNET2;
extern struct ReceiveGTNET3_t ReceiveGTNET3;

extern struct SendVENIED1_t SendVENIED1;
extern struct SendVENIED2_t SendVENIED2;
extern struct SendVENIED3_t SendVENIED3;

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
