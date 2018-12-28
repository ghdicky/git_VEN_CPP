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

#ifndef DATATYPES_H
#define DATATYPES_H

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

#include "ctypes.h"


// enums
enum ACDdir {
	ACDDIR_UNKNOWN_0 = 0,
	ACDDIR_FORWARD_1 = 1,
	ACDDIR_BACKWARD_2 = 2,
	ACDDIR_BOTH_3 = 3
};
enum seqT {
	SEQT_POS_NEG_ZERO_0 = 0,
	SEQT_DIR_QUAD_ZERO_1 = 1
};
enum Dbpos {
	DBPOS_INTERMEDIATE_0 = 0,
	DBPOS_OFF_1 = 1,
	DBPOS_ON_2 = 2,
	DBPOS_BAD_3 = 3
};
enum Tcmd {
	TCMD_STOP_0 = 0,
	TCMD_LOWER_1 = 1,
	TCMD_HIGHER_2 = 2,
	TCMD_RESERVED_3 = 3
};
enum Beh {
	BEH_ON_1 = 1,
	BEH_BLOCKED_2 = 2,
	BEH_TEST_3 = 3,
	BEH_TEST_BLOCKED_4 = 4,
	BEH_OFF_5 = 5
};
enum Mod {
	MOD_ON_1 = 1,
	MOD_BLOCKED_2 = 2,
	MOD_TEST_3 = 3,
	MOD_TEST_BLOCKED_4 = 4,
	MOD_OFF_5 = 5
};
enum Health {
	HEALTH_OK_1 = 1,
	HEALTH_WARNING_2 = 2,
	HEALTH_ALARM_3 = 3
};


enum ctlModel {
        status_only = 0,
	direct_with_normal_security = 1,
        sbo_with_normal_security = 2,
        direct_with_enhanced_security = 3,
        sbo_with_enhanced_security = 4 
};

// data attributes
struct myAnalogValue {
	CTYPE_FLOAT32 f;
};
struct ScaledValueConfig {
	CTYPE_FLOAT32 scaleFactor;
	CTYPE_FLOAT32 offset;
};
struct myVector {
	struct myAnalogValue mag;
	struct myAnalogValue ang;
};
struct simpleVector {
	struct myAnalogValue mag;
	struct myAnalogValue ang;
};



struct myMod {
	enum Mod ctlVal;
	enum Mod stVal;
	CTYPE_QUALITY q;
	CTYPE_TIMESTAMP t;
};
struct myHealth {
	enum Health stVal;
};
struct myBeh {
	enum Beh stVal;
};
struct myINS {
	CTYPE_INT32 stVal;
};
struct myLPL {
	CTYPE_VISSTRING255 ldNs;
	CTYPE_VISSTRING255 configRev;
};
struct myDPL {
	CTYPE_VISSTRING255 vendor;
	CTYPE_VISSTRING255 hwRev;
};
struct myPos {
	CTYPE_DBPOS stVal;
	CTYPE_QUALITY q;
	CTYPE_TIMESTAMP t;
	CTYPE_BOOLEAN ctlVal;
};
struct mySPS {
	CTYPE_INT32 stVal;
	CTYPE_QUALITY q;
	CTYPE_TIMESTAMP t;
};
struct myMV {
	struct myAnalogValue mag;
	CTYPE_QUALITY q;
	CTYPE_TIMESTAMP t;
	struct ScaledValueConfig sVC;
	CTYPE_INT32 int1;
	CTYPE_INT32 int2;
	CTYPE_INT32 int3;
};
struct simpleMV {
	CTYPE_FLOAT32 mag;
	CTYPE_QUALITY q;
	CTYPE_TIMESTAMP t;
	struct ScaledValueConfig sVC;
};
struct simpleCMV {
	struct mySPS testSecondLayerSDO;
	struct simpleVector cVal;
	CTYPE_QUALITY q;
	CTYPE_TIMESTAMP t;
	CTYPE_INT32 testInteger;
	CTYPE_BOOLEAN testBoolean;
};
struct simpleWYE {
	struct simpleCMV phsA;
	struct simpleCMV phsB;
	struct simpleCMV phsC;
};
struct myCMV {
	struct myVector cVal;
	CTYPE_QUALITY q;
	CTYPE_TIMESTAMP t;
};
struct mySEQ {
	struct myCMV c1;
	struct myCMV c2;
	struct myCMV c3;
	enum seqT seqT;
};
struct mySAV {
	struct myAnalogValue instMag;
	CTYPE_QUALITY q;
};
struct simpleSAV {
	struct myAnalogValue instMag;
	CTYPE_QUALITY q;
};

struct myInd {                      // data object for doName = "Ind" of RTDS
        CTYPE_BOOLEAN stVal;         
        CTYPE_QUALITY q;
        CTYPE_TIMESTAMP t;
};

struct myAnIn {                     // data obejct for doName = "AnIn" of RTDS
        struct myAnalogValue mag;           
        CTYPE_QUALITY q;
        CTYPE_TIMESTAMP t;
        enum ctlModel ctlModel;        
};

struct myIntIn {                    // data obejct for doName = "IntIn" of RTDS
        CTYPE_INT32 stVal;
        CTYPE_QUALITY q;
        CTYPE_TIMESTAMP t;
};

struct myDPC {                      // data obejct for doName = "DPCSO" of RTDS
        CTYPE_BOOLEAN ctlVal;
        enum Dbpos stVal;
        CTYPE_QUALITY q;
        CTYPE_TIMESTAMP t;
};




// datasets
struct E1Q1SB1_C1_Performance {
	struct myMV C1_MMXU_1_Amps;
	struct myMV C1_MMXU_1_Volts;
};
struct E1Q1SB1_C1_Positions {
	struct myAnalogValue C1_TVTR_1_Vol_instMag;
	struct myPos C1_CSWI_1_Pos;
	struct myPos C1_CSWI_2_Pos;
	enum Mod C1_MMXU_1_Mod_stVal;
};
struct E1Q1SB1_C1_Measurands {
	struct myAnalogValue C1_TVTR_1_Vol_instMag;
};
struct E1Q1SB1_C1_smv {
	struct myAnalogValue C1_TVTR_1_Vol_instMag;
	struct myMod C1_CSWI_1_Mod;
	enum Mod C1_MMXU_1_Mod_stVal;
};
struct E1Q1SB1_C1_rmxu {
	struct simpleSAV C1_RMXU_1_AmpLocPhsA;
	struct simpleSAV C1_RMXU_1_AmpLocPhsB;
	struct simpleSAV C1_RMXU_1_AmpLocPhsC;
};
struct D1Q1SB4_C1_SyckResult {
	struct mySPS C1_RSYN_1_Rel;
};
struct D1Q1SB4_C1_MMXUResult {
	struct simpleWYE C1_MMXU_1_A;
};


struct GTNET1_C1_outputs1 {             // dataset for GTNET1_C1_outputs1
	struct myInd C1_GGIO_1_GOOSETrigger;
	struct myAnIn C1_GGIO_2_SubP;
        struct myAnIn C1_GGIO_3_SubQ;
        struct myAnIn C1_GGIO_4_21P;
        struct myAnIn C1_GGIO_5_21Q;
        struct myAnIn C1_GGIO_6_21T;
        struct myAnIn C1_GGIO_7_21Opt;
        struct myAnIn C1_GGIO_8_22P;
        struct myAnIn C1_GGIO_9_22Q;
        struct myAnIn C1_GGIO_10_22T;
        struct myAnIn C1_GGIO_11_22Opt;
        struct myAnIn C1_GGIO_12_23P;
        struct myAnIn C1_GGIO_13_23Q;
        struct myAnIn C1_GGIO_14_23T;
        struct myAnIn C1_GGIO_15_23Opt;
        struct myAnIn C1_GGIO_16_24P;
        struct myAnIn C1_GGIO_17_24Q;
        struct myAnIn C1_GGIO_18_24T;
        struct myAnIn C1_GGIO_19_24Opt;
        struct myAnIn C1_GGIO_20_25P;
        struct myAnIn C1_GGIO_21_25Q;
        struct myAnIn C1_GGIO_22_25T;
        struct myAnIn C1_GGIO_23_25Opt;
        struct myAnIn C1_GGIO_24_26P;
        struct myAnIn C1_GGIO_25_26Q;
        struct myAnIn C1_GGIO_26_26T;
        struct myAnIn C1_GGIO_27_26Opt;
        struct myAnIn C1_GGIO_28_27P;
        struct myAnIn C1_GGIO_29_27Q;
        struct myAnIn C1_GGIO_30_27T;
        struct myAnIn C1_GGIO_31_27Opt;
        struct myAnIn C1_GGIO_32_28P;
        struct myAnIn C1_GGIO_33_28Q;
        struct myAnIn C1_GGIO_34_28T;
        struct myAnIn C1_GGIO_35_28Opt;
        struct myAnIn C1_GGIO_36_29P;
        struct myAnIn C1_GGIO_37_29Q;
        struct myAnIn C1_GGIO_38_29T;
        struct myAnIn C1_GGIO_39_29Opt;
        struct myAnIn C1_GGIO_40_30P;
        struct myAnIn C1_GGIO_41_30Q;
        struct myAnIn C1_GGIO_42_30T;
        struct myAnIn C1_GGIO_43_30Opt;
        struct myAnIn C1_GGIO_44_31P;
        struct myAnIn C1_GGIO_45_31Q;
        struct myAnIn C1_GGIO_46_31T;
        struct myAnIn C1_GGIO_47_31Opt;
        struct myAnIn C1_GGIO_48_48P;
        struct myAnIn C1_GGIO_49_48Q;
        struct myAnIn C1_GGIO_50_48T;
        struct myAnIn C1_GGIO_51_48Opt;
        struct myAnIn C1_GGIO_52_49P;
        struct myAnIn C1_GGIO_53_49Q;
        struct myAnIn C1_GGIO_54_49T;
        struct myAnIn C1_GGIO_55_49Opt;
        struct myAnIn C1_GGIO_56_50P;
        struct myAnIn C1_GGIO_57_50Q;
        struct myAnIn C1_GGIO_58_50T;
        struct myAnIn C1_GGIO_59_50Opt;
        struct myAnIn C1_GGIO_60_51P;
        struct myAnIn C1_GGIO_61_51Q;
        struct myAnIn C1_GGIO_62_51T;
        struct myAnIn C1_GGIO_63_51Opt;
        CTYPE_TIMESTAMP T;
        CTYPE_INT32U stNum;
	CTYPE_INT32U sqNum;   
};

struct GTNET2_C1_outputs2 {             // dataset for GTNET2_C1_outputs2
	struct myInd C1_GGIO_65_GOOSETrigger;
	struct myAnIn C1_GGIO_66_52P;
        struct myAnIn C1_GGIO_67_52Q;
        struct myAnIn C1_GGIO_68_52T;
        struct myAnIn C1_GGIO_69_52Opt;
        struct myAnIn C1_GGIO_70_53P;
        struct myAnIn C1_GGIO_71_53Q;
        struct myAnIn C1_GGIO_72_53T;
        struct myAnIn C1_GGIO_73_53Opt;
        struct myAnIn C1_GGIO_74_54P;
        struct myAnIn C1_GGIO_75_54Q;
        struct myAnIn C1_GGIO_76_54T;
        struct myAnIn C1_GGIO_77_54Opt;
        struct myAnIn C1_GGIO_78_55P;
        struct myAnIn C1_GGIO_79_55Q;
        struct myAnIn C1_GGIO_80_55T;
        struct myAnIn C1_GGIO_81_55Opt;
        struct myAnIn C1_GGIO_82_56P;
        struct myAnIn C1_GGIO_83_56Q;
        struct myAnIn C1_GGIO_84_56T;
        struct myAnIn C1_GGIO_85_56Opt;
        struct myAnIn C1_GGIO_86_57P;
        struct myAnIn C1_GGIO_87_57Q;
        struct myAnIn C1_GGIO_88_57T;
        struct myAnIn C1_GGIO_89_57Opt;
        struct myAnIn C1_GGIO_90_59P;
        struct myAnIn C1_GGIO_91_59Q;
        struct myAnIn C1_GGIO_92_59T;
        struct myAnIn C1_GGIO_93_59Opt;
        struct myAnIn C1_GGIO_94_60P;
        struct myAnIn C1_GGIO_95_60Q;
        struct myAnIn C1_GGIO_96_60T;
        struct myAnIn C1_GGIO_97_60Opt;
        struct myAnIn C1_GGIO_98_61P;
        struct myAnIn C1_GGIO_99_61Q;
        struct myAnIn C1_GGIO_100_61T;
        struct myAnIn C1_GGIO_101_61Opt;
        struct myAnIn C1_GGIO_102_62P;
        struct myAnIn C1_GGIO_103_62Q;
        struct myAnIn C1_GGIO_104_62T;
        struct myAnIn C1_GGIO_105_62Opt;
        struct myAnIn C1_GGIO_106_63P;
        struct myAnIn C1_GGIO_107_63Q;
        struct myAnIn C1_GGIO_108_63T;
        struct myAnIn C1_GGIO_109_63Opt;
        struct myAnIn C1_GGIO_110_64P;
        struct myAnIn C1_GGIO_111_64Q;
        struct myAnIn C1_GGIO_112_64T;
        struct myAnIn C1_GGIO_113_64Opt;
        struct myAnIn C1_GGIO_114_65P;
        struct myAnIn C1_GGIO_115_65Q;
        struct myAnIn C1_GGIO_116_65T;
        struct myAnIn C1_GGIO_117_65Opt;
        struct myAnIn C1_GGIO_118_66P;
        struct myAnIn C1_GGIO_119_66Q;
        struct myAnIn C1_GGIO_120_66T;
        struct myAnIn C1_GGIO_121_66Opt;
        struct myAnIn C1_GGIO_122_67P;
        struct myAnIn C1_GGIO_123_67Q;
        struct myAnIn C1_GGIO_124_67T;
        struct myAnIn C1_GGIO_125_67Opt;
        CTYPE_TIMESTAMP T;
        CTYPE_INT32U stNum;
	CTYPE_INT32U sqNum;    
};

struct GTNET3_C1_outputs3 {             // dataset for GTNET3_C1_outputs3
	struct myInd C1_GGIO_129_GOOSETrigger;
	struct myAnIn C1_GGIO_130_68P;
        struct myAnIn C1_GGIO_131_68Q;
        struct myAnIn C1_GGIO_132_68T;
        struct myAnIn C1_GGIO_133_68Opt;
        struct myAnIn C1_GGIO_134_69P;
        struct myAnIn C1_GGIO_135_69Q;
        struct myAnIn C1_GGIO_136_69T;
        struct myAnIn C1_GGIO_137_69Opt;
        struct myAnIn C1_GGIO_138_70P;
        struct myAnIn C1_GGIO_139_70Q;
        struct myAnIn C1_GGIO_140_70T;
        struct myAnIn C1_GGIO_141_70Opt;
        struct myAnIn C1_GGIO_142_42P;
        struct myAnIn C1_GGIO_143_42Q;
        struct myAnIn C1_GGIO_144_42T;
        struct myAnIn C1_GGIO_145_42Opt;
        struct myAnIn C1_GGIO_146_43P;
        struct myAnIn C1_GGIO_147_43Q;
        struct myAnIn C1_GGIO_148_43T;
        struct myAnIn C1_GGIO_149_43Opt;
        struct myAnIn C1_GGIO_150_44P;
        struct myAnIn C1_GGIO_151_44Q;
        struct myAnIn C1_GGIO_152_44T;
        struct myAnIn C1_GGIO_153_44Opt;
        struct myAnIn C1_GGIO_154_45P;
        struct myAnIn C1_GGIO_155_45Q;
        struct myAnIn C1_GGIO_156_45T;
        struct myAnIn C1_GGIO_157_45Opt;
        struct myAnIn C1_GGIO_158_46P;
        struct myAnIn C1_GGIO_159_46Q;
        struct myAnIn C1_GGIO_160_46T;
        struct myAnIn C1_GGIO_161_46Opt;
        struct myAnIn C1_GGIO_162_47P;
        struct myAnIn C1_GGIO_163_47Q;
        struct myAnIn C1_GGIO_164_47T;
        struct myAnIn C1_GGIO_165_47Opt;
        struct myAnIn C1_GGIO_166_47BP;
        struct myAnIn C1_GGIO_167_47BQ;
        struct myAnIn C1_GGIO_168_47BT;
        struct myAnIn C1_GGIO_169_47BOpt;
        CTYPE_TIMESTAMP T;
        CTYPE_INT32U stNum;
	CTYPE_INT32U sqNum;    
};


// logical nodes
struct LN0 {
	struct myMod Mod;
	struct myHealth Health;
	struct myBeh Beh;
	struct myLPL NamPlt;
};
struct LPHDa {
	struct myMod Mod;
	struct myHealth Health;
	struct myBeh Beh;
	struct myLPL NamPlt;
	struct myDPL PhyNam;
	struct myINS PhyHealth;
	struct mySPS Proxy;
	struct {
		struct E1Q1SB1_C1_smv E1Q1SB1_C1_smv[2];
		void (*datasetDecodeDone)(CTYPE_INT16U smpCnt);
		CTYPE_INT16U smpCnt;
	} sv_inputs_Volt;
};
struct CSWIa {
	struct myMod Mod;
	struct myHealth Health;
	struct myBeh Beh;
	struct myPos Pos;
	struct mySPS GrpAl;
};
struct MMXUa {
	struct myMod Mod;
	struct myHealth Beh;
	struct myBeh Health;
	struct myMV Amps;
	struct myMV Volts;
};
struct exampleMMXU {
	struct myMod Mod;
	struct myHealth Beh;
	struct myBeh Health;
	struct simpleWYE A;
	struct {
		struct E1Q1SB1_C1_rmxu E1Q1SB1_C1_rmxu[16];
		void (*datasetDecodeDone)(CTYPE_INT16U smpCnt);
		CTYPE_INT16U smpCnt;
	} sv_inputs_rmxuCB;
	struct {
		struct E1Q1SB1_C1_Performance E1Q1SB1_C1_Performance;
		void (*datasetDecodeDone)(CTYPE_INT32U timeAllowedToLive, CTYPE_TIMESTAMP T, CTYPE_INT32U stNum, CTYPE_INT32U sqNum);
		CTYPE_INT32U timeAllowedToLive;
		CTYPE_TIMESTAMP T;
		CTYPE_INT32U stNum;
		CTYPE_INT32U sqNum;
	} gse_inputs_Performance;
	struct {
		struct E1Q1SB1_C1_Performance E1Q1SB1_C1_Performance;
		void (*datasetDecodeDone)(CTYPE_INT16U smpCnt);
		CTYPE_INT16U smpCnt;
	} sv_inputs_PerformanceSV;
};
struct exampleRMXU {
	struct myMod Mod;
	struct myHealth Beh;
	struct myBeh Health;
	struct simpleSAV AmpLocPhsA;
	struct simpleSAV AmpLocPhsB;
	struct simpleSAV AmpLocPhsC;
};
struct CILOa {
	struct myHealth Mod;
	struct myBeh Beh;
	struct myINS Health;
	struct mySPS EnaOpen;
	struct mySPS EnaClose;
};
struct TVTRa {
	struct myMod Mod;
	struct myHealth Health;
	struct myBeh Beh;
	struct mySAV Vol;
};
struct RSYNa {
	struct myMod Mod;
	struct myHealth Health;
	struct myBeh Beh;
	struct myLPL NamPlt;
	struct mySPS Rel;
	struct {
		struct E1Q1SB1_C1_smv E1Q1SB1_C1_smv[2];
		void (*datasetDecodeDone)(CTYPE_INT16U smpCnt);
		CTYPE_INT16U smpCnt;
	} sv_inputs_Volt;
	struct {
		struct E1Q1SB1_C1_Positions E1Q1SB1_C1_Positions;
		void (*datasetDecodeDone)(CTYPE_INT32U timeAllowedToLive, CTYPE_TIMESTAMP T, CTYPE_INT32U stNum, CTYPE_INT32U sqNum);
		CTYPE_INT32U timeAllowedToLive;
		CTYPE_TIMESTAMP T;
		CTYPE_INT32U stNum;
		CTYPE_INT32U sqNum;
	} gse_inputs_AnotherPositions;
	struct {
		struct E1Q1SB1_C1_Positions E1Q1SB1_C1_Positions;
		void (*datasetDecodeDone)(CTYPE_INT32U timeAllowedToLive, CTYPE_TIMESTAMP T, CTYPE_INT32U stNum, CTYPE_INT32U sqNum);
		CTYPE_INT32U timeAllowedToLive;
		CTYPE_TIMESTAMP T;
		CTYPE_INT32U stNum;
		CTYPE_INT32U sqNum;
	} gse_inputs_ItlPositions;
};

// this is the logical node LN type GGIO compliant to RTDS schema
struct GGIO {
    struct myMod Mod;
    struct myBeh Beh;
    struct myHealth Health;
    struct myLPL NamPlt;
    struct myInd Ind;
    struct myAnIn AnIn;
    struct myIntIn IntIn;
    struct myDPC DPCSO;
};


void init_datatypes();




#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
