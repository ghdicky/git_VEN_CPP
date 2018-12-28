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

#include "gseDecodeBasic.h"
#include "gse.h"
#include "ied.h"
#include "gseDecode.h"

// for fprint and stdout 
#include <stdio.h> 

// for mysql wrapper
#include "../mysqlwrapper/mysqlwrapper.h"




int ber_decode_myAnalogValue(unsigned char *buf, struct myAnalogValue *myAnalogValue) {
	int offset = 0;

	if (buf[offset++] == 0x87) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &myAnalogValue->f);
	}

	return offset;
}
int ber_decode_ScaledValueConfig(unsigned char *buf, struct ScaledValueConfig *ScaledValueConfig) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &ScaledValueConfig->scaleFactor);
		offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &ScaledValueConfig->offset);
	}

	return offset;
}
int ber_decode_myVector(unsigned char *buf, struct myVector *myVector) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_myAnalogValue(&buf[offset], &myVector->mag);
		offset += ber_decode_myAnalogValue(&buf[offset], &myVector->ang);
	}

	return offset;
}
int ber_decode_simpleVector(unsigned char *buf, struct simpleVector *simpleVector) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_myAnalogValue(&buf[offset], &simpleVector->mag);
		offset += ber_decode_myAnalogValue(&buf[offset], &simpleVector->ang);
	}

	return offset;
}
int ber_decode_myMod(unsigned char *buf, struct myMod *myMod) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_ENUM(&buf[offset], (CTYPE_ENUM *) &myMod->ctlVal);
		offset += BER_DECODE_CTYPE_ENUM(&buf[offset], (CTYPE_ENUM *) &myMod->stVal);
		offset += BER_DECODE_CTYPE_QUALITY(&buf[offset], &myMod->q);
		offset += BER_DECODE_CTYPE_TIMESTAMP(&buf[offset], &myMod->t);
	}

	return offset;
}
int ber_decode_myHealth(unsigned char *buf, struct myHealth *myHealth) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_ENUM(&buf[offset], (CTYPE_ENUM *) &myHealth->stVal);
	}

	return offset;
}
int ber_decode_myBeh(unsigned char *buf, struct myBeh *myBeh) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_ENUM(&buf[offset], (CTYPE_ENUM *) &myBeh->stVal);
	}

	return offset;
}
int ber_decode_myINS(unsigned char *buf, struct myINS *myINS) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_INT32(&buf[offset], &myINS->stVal);
	}

	return offset;
}
int ber_decode_myLPL(unsigned char *buf, struct myLPL *myLPL) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_VISSTRING255(&buf[offset], &myLPL->ldNs);
		offset += BER_DECODE_CTYPE_VISSTRING255(&buf[offset], &myLPL->configRev);
	}

	return offset;
}
int ber_decode_myDPL(unsigned char *buf, struct myDPL *myDPL) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_VISSTRING255(&buf[offset], &myDPL->vendor);
		offset += BER_DECODE_CTYPE_VISSTRING255(&buf[offset], &myDPL->hwRev);
	}

	return offset;
}
int ber_decode_myPos(unsigned char *buf, struct myPos *myPos) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_DBPOS(&buf[offset], &myPos->stVal);
		offset += BER_DECODE_CTYPE_QUALITY(&buf[offset], &myPos->q);
		offset += BER_DECODE_CTYPE_TIMESTAMP(&buf[offset], &myPos->t);
		offset += BER_DECODE_CTYPE_BOOLEAN(&buf[offset], &myPos->ctlVal);
	}

	return offset;
}
int ber_decode_mySPS(unsigned char *buf, struct mySPS *mySPS) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_INT32(&buf[offset], &mySPS->stVal);
		offset += BER_DECODE_CTYPE_QUALITY(&buf[offset], &mySPS->q);
		offset += BER_DECODE_CTYPE_TIMESTAMP(&buf[offset], &mySPS->t);
	}

	return offset;
}
int ber_decode_myMV(unsigned char *buf, struct myMV *myMV) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_myAnalogValue(&buf[offset], &myMV->mag);
		offset += BER_DECODE_CTYPE_QUALITY(&buf[offset], &myMV->q);
		offset += BER_DECODE_CTYPE_TIMESTAMP(&buf[offset], &myMV->t);
		offset += ber_decode_ScaledValueConfig(&buf[offset], &myMV->sVC);
		offset += BER_DECODE_CTYPE_INT32(&buf[offset], &myMV->int1);
		offset += BER_DECODE_CTYPE_INT32(&buf[offset], &myMV->int2);
		offset += BER_DECODE_CTYPE_INT32(&buf[offset], &myMV->int3);
	}

	return offset;
}
int ber_decode_simpleMV(unsigned char *buf, struct simpleMV *simpleMV) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &simpleMV->mag);
		offset += BER_DECODE_CTYPE_QUALITY(&buf[offset], &simpleMV->q);
		offset += BER_DECODE_CTYPE_TIMESTAMP(&buf[offset], &simpleMV->t);
		offset += ber_decode_ScaledValueConfig(&buf[offset], &simpleMV->sVC);
	}

	return offset;
}
int ber_decode_simpleCMV(unsigned char *buf, struct simpleCMV *simpleCMV) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_simpleVector(&buf[offset], &simpleCMV->cVal);
		offset += BER_DECODE_CTYPE_QUALITY(&buf[offset], &simpleCMV->q);
		offset += BER_DECODE_CTYPE_TIMESTAMP(&buf[offset], &simpleCMV->t);
		offset += ber_decode_mySPS(&buf[offset], &simpleCMV->testSecondLayerSDO);
		offset += BER_DECODE_CTYPE_INT32(&buf[offset], &simpleCMV->testInteger);
		offset += BER_DECODE_CTYPE_BOOLEAN(&buf[offset], &simpleCMV->testBoolean);
	}

	return offset;
}
int ber_decode_simpleWYE(unsigned char *buf, struct simpleWYE *simpleWYE) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_simpleCMV(&buf[offset], &simpleWYE->phsA);
		offset += ber_decode_simpleCMV(&buf[offset], &simpleWYE->phsB);
		offset += ber_decode_simpleCMV(&buf[offset], &simpleWYE->phsC);
	}

	return offset;
}
int ber_decode_myCMV(unsigned char *buf, struct myCMV *myCMV) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_myVector(&buf[offset], &myCMV->cVal);
		offset += BER_DECODE_CTYPE_QUALITY(&buf[offset], &myCMV->q);
		offset += BER_DECODE_CTYPE_TIMESTAMP(&buf[offset], &myCMV->t);
	}

	return offset;
}
int ber_decode_mySEQ(unsigned char *buf, struct mySEQ *mySEQ) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_myCMV(&buf[offset], &mySEQ->c1);
		offset += ber_decode_myCMV(&buf[offset], &mySEQ->c2);
		offset += ber_decode_myCMV(&buf[offset], &mySEQ->c3);
		offset += BER_DECODE_CTYPE_ENUM(&buf[offset], (CTYPE_ENUM *) &mySEQ->seqT);
	}

	return offset;
}
int ber_decode_mySAV(unsigned char *buf, struct mySAV *mySAV) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_myAnalogValue(&buf[offset], &mySAV->instMag);
		offset += BER_DECODE_CTYPE_QUALITY(&buf[offset], &mySAV->q);
	}

	return offset;
}
int ber_decode_simpleSAV(unsigned char *buf, struct simpleSAV *simpleSAV) {
	int offset = 0;

	if (buf[offset++] == 0xA2) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_myAnalogValue(&buf[offset], &simpleSAV->instMag);
		offset += BER_DECODE_CTYPE_QUALITY(&buf[offset], &simpleSAV->q);
	}

	return offset;
}
int ber_decode_E1Q1SB1_C1_Performance(unsigned char *buf, struct E1Q1SB1_C1_Performance *E1Q1SB1_C1_Performance) {
	int offset = 0;

	offset += ber_decode_myMV(&buf[offset], &E1Q1SB1_C1_Performance->C1_MMXU_1_Amps);
	offset += ber_decode_myMV(&buf[offset], &E1Q1SB1_C1_Performance->C1_MMXU_1_Volts);

	return offset;
}
int ber_decode_E1Q1SB1_C1_Positions(unsigned char *buf, struct E1Q1SB1_C1_Positions *E1Q1SB1_C1_Positions) {
	int offset = 0;

	offset += ber_decode_myAnalogValue(&buf[offset], &E1Q1SB1_C1_Positions->C1_TVTR_1_Vol_instMag);
	offset += ber_decode_myPos(&buf[offset], &E1Q1SB1_C1_Positions->C1_CSWI_1_Pos);
	offset += ber_decode_myPos(&buf[offset], &E1Q1SB1_C1_Positions->C1_CSWI_2_Pos);
	offset += BER_DECODE_CTYPE_ENUM(&buf[offset], (CTYPE_ENUM *) &E1Q1SB1_C1_Positions->C1_MMXU_1_Mod_stVal);

	return offset;
}
int ber_decode_E1Q1SB1_C1_Measurands(unsigned char *buf, struct E1Q1SB1_C1_Measurands *E1Q1SB1_C1_Measurands) {
	int offset = 0;

	offset += ber_decode_myAnalogValue(&buf[offset], &E1Q1SB1_C1_Measurands->C1_TVTR_1_Vol_instMag);

	return offset;
}
int ber_decode_E1Q1SB1_C1_smv(unsigned char *buf, struct E1Q1SB1_C1_smv *E1Q1SB1_C1_smv) {
	int offset = 0;

	offset += ber_decode_myAnalogValue(&buf[offset], &E1Q1SB1_C1_smv->C1_TVTR_1_Vol_instMag);
	offset += ber_decode_myMod(&buf[offset], &E1Q1SB1_C1_smv->C1_CSWI_1_Mod);
	offset += BER_DECODE_CTYPE_ENUM(&buf[offset], (CTYPE_ENUM *) &E1Q1SB1_C1_smv->C1_MMXU_1_Mod_stVal);

	return offset;
}
int ber_decode_E1Q1SB1_C1_rmxu(unsigned char *buf, struct E1Q1SB1_C1_rmxu *E1Q1SB1_C1_rmxu) {
	int offset = 0;

	offset += ber_decode_simpleSAV(&buf[offset], &E1Q1SB1_C1_rmxu->C1_RMXU_1_AmpLocPhsA);
	offset += ber_decode_simpleSAV(&buf[offset], &E1Q1SB1_C1_rmxu->C1_RMXU_1_AmpLocPhsB);
	offset += ber_decode_simpleSAV(&buf[offset], &E1Q1SB1_C1_rmxu->C1_RMXU_1_AmpLocPhsC);

	return offset;
}
int ber_decode_D1Q1SB4_C1_SyckResult(unsigned char *buf, struct D1Q1SB4_C1_SyckResult *D1Q1SB4_C1_SyckResult) {
	int offset = 0;

	offset += ber_decode_mySPS(&buf[offset], &D1Q1SB4_C1_SyckResult->C1_RSYN_1_Rel);

	return offset;
}
int ber_decode_D1Q1SB4_C1_MMXUResult(unsigned char *buf, struct D1Q1SB4_C1_MMXUResult *D1Q1SB4_C1_MMXUResult) {
	int offset = 0;

	offset += ber_decode_simpleWYE(&buf[offset], &D1Q1SB4_C1_MMXUResult->C1_MMXU_1_A);

	return offset;
}


// this is to decode data attribute GGIO_1.Ind.stVal 
//int ber_decode_myCBooleanValue(unsigned char *buf, struct myBooleanValue *myBooleanValue) {
//	int offset = 0;

//	if (buf[offset++] == 0x83) {
//		offset += getLengthFieldSize(buf[offset]);

//                offset += BER_DECODE_CTYPE_BOOLEAN(&buf[offset], &myBooleanValue->b);
//	}

//	return offset;
//}


// this is to decode data object Ind of type myInd
//int ber_decode_myInd(unsigned char *buf, struct myInd *myInd) {
//	int offset = 0;

//	if (buf[offset++] == ASN1_TAG_BOOLEAN) {
//		offset += getLengthFieldSize(buf[offset]);
                
//                fprintf(stdout, "offset when decode_myBooleanValue is: %u \n", offset);
//                fprintf(stdout, "buf[offset] is: %d \n", buf[offset]);

                                
                
//		offset += BER_DECODE_CTYPE_BOOLEAN(&buf[offset], &myInd->flag.b);
//	}

//	return offset;
//}

// this is to decode data object AnIn of type myAnIn
int ber_decode_myAnIn(unsigned char *buf, struct myAnIn *myAnIn) {
	int offset = 0;

	if (buf[offset++] == 0x87) {
		offset += getLengthFieldSize(buf[offset]);

		offset += ber_decode_myAnalogValue(&buf[offset], &myAnIn->mag);
	}
        
	return offset;
}

// this is to decode the receiving GTNET_C1_outputs dataset for GTNET1 Outputs1
int ber_decode_GTNET1_C1_outputs1(unsigned char *buf, struct GTNET1_C1_outputs1 *GTNET1_C1_outputs1) {
        int offset = 0;

        // locate buf[offset] that contains boolean and assign the boolean to Input_GTNET1.C1.outputs->C1_GGIO_1_GOOSETrigger.flag
	offset += BER_DECODE_CTYPE_BOOLEAN(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_1_GOOSETrigger.stVal); 
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_2_SubP.mag
	offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_2_SubP.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_3_SubQ.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_3_SubQ.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_4_21P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_4_21P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_5_21Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_6_21T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_7_21Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_8_22P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_8_22P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_9_22Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_10_22T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_11_22Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_12_23P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_12_23P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_13_23Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_14_23T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_15_23Opt.mag.f);

        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_16_24P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_16_24P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_17_24Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_18_24T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_19_24Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_20_25P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_20_25P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_21_25Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_22_25T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_23_25Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_24_26P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_24_26P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_25_26Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_26_26T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_27_26Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_28_27P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_28_27P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_29_27Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_30_27T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_31_27Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_32_28P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_32_28P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_33_28Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_34_28T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_35_28Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_36_29P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_36_29P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_37_29Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_38_29T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_39_29Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_40_30P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_40_30P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_41_30Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_42_30T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_43_30Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_44_31P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_44_31P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_45_31Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_46_31T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_47_31Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_48_48P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_48_48P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_49_48Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_50_48T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_51_48Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_52_49P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_52_49P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_53_49Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_54_49T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_55_49Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_56_50P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_56_50P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_57_50Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_58_50T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_59_50Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET1.C1.outputs->C1_GGIO_60_51P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_60_51P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_61_51Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_62_51T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET1_C1_outputs1->C1_GGIO_63_51Opt.mag.f);
        
        
	return offset;
}

// this is to decode the receiving GTNET_C1_outputs dataset for GTNET2 Outputs2
int ber_decode_GTNET2_C1_outputs2(unsigned char *buf, struct GTNET2_C1_outputs2 *GTNET2_C1_outputs2) {
        int offset = 0;

        // locate buf[offset] that contains boolean and assign the boolean to Input_GTNET2.C1.outputs->C1_GGIO_65_GOOSETrigger.flag
	offset += BER_DECODE_CTYPE_BOOLEAN(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_65_GOOSETrigger.stVal); 
               
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_66_52P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_66_52P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_67_52Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_68_52T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_69_52Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_70_53P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_70_53P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_71_53Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_72_53T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_73_53Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_74_54P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_74_54P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_75_54Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_76_54T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_77_54Opt.mag.f);

        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_78_55P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_78_55P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_79_55Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_80_55T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_81_55Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_82_56P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_82_56P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_83_56Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_84_56T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_85_56Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_86_57P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_86_57P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_87_57Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_88_57T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_89_57Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_90_59P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_90_59P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_91_59Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_92_59T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_93_59Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_94_60P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_94_60P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_95_60Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_96_60T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_97_60Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_98_61P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_98_61P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_99_61Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_100_61T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_101_61Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_102_62P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_102_62P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_103_62Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_104_62T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_105_62Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_106_63P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_106_63P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_107_63Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_108_63T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_109_63Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_110_64P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_110_64P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_111_64Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_112_64T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_113_64Opt.mag.f);
       
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_114_65P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_114_65P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_115_65Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_116_65T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_117_65Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_118_66P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_118_66P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_119_66Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_120_66T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_121_66Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET2.C1.outputs->C1_GGIO_122_67P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_122_67P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_123_67Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_124_67T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET2_C1_outputs2->C1_GGIO_125_67Opt.mag.f);
        
        
	return offset;
}

// this is to decode the receiving GTNET_C1_outputs dataset for GTNET3 Outputs3
int ber_decode_GTNET3_C1_outputs3(unsigned char *buf, struct GTNET3_C1_outputs3 *GTNET3_C1_outputs3) {
        int offset = 0;

        // locate buf[offset] that contains boolean and assign the boolean to Input_GTNET3.C1.outputs->C1_GGIO_129_GOOSETrigger.flag
	offset += BER_DECODE_CTYPE_BOOLEAN(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_129_GOOSETrigger.stVal); 
               
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_130_68P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_130_68P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_131_68Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_132_68T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_133_68Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_134_69P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_134_69P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_135_69Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_136_69T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_137_69Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_138_70P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_138_70P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_139_70Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_140_70T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_141_70Opt.mag.f);

        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_142_42P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_142_42P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_143_42Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_144_42T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_145_42Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_146_43P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_146_43P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_147_43Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_148_43T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_149_43Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_150_44P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_150_44P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_151_44Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_152_44T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_153_44Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_154_45P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_154_45P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_155_45Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_156_45T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_157_45Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_158_46P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_158_46P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_159_46Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_160_46T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_161_46Opt.mag.f);
       
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_162_47P.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_162_47P.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_163_47Q.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_164_47T.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_165_47Opt.mag.f);
        
        // locate buf[offset] that contains float 32 and assign the float 32 to Input_GTNET3.C1.outputs->C1_GGIO_166_47BP.mag
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_166_47BP.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_167_47BQ.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_168_47BT.mag.f);
        offset += BER_DECODE_CTYPE_FLOAT32(&buf[offset], &GTNET3_C1_outputs3->C1_GGIO_169_47BOpt.mag.f);
        
        
	return offset;
}


void gseDecodeDataset(unsigned char *dataset, CTYPE_INT16U datasetLength, unsigned char *gocbRef, CTYPE_INT16U gocbRefLength, CTYPE_INT32U timeAllowedToLive, CTYPE_TIMESTAMP T, CTYPE_INT32U stNum, CTYPE_INT32U sqNum) {

	if (gocbRefLength == 29 && strncmp((const char *) gocbRef, "E1Q1SB1C1/LLN0$GO$Performance", gocbRefLength) == 0) {
		if (stNum != D1Q1SB4.S1.C1.exampleMMXU_1.gse_inputs_Performance.stNum) {
			ber_decode_E1Q1SB1_C1_Performance(dataset, &D1Q1SB4.S1.C1.exampleMMXU_1.gse_inputs_Performance.E1Q1SB1_C1_Performance);
		}
		D1Q1SB4.S1.C1.exampleMMXU_1.gse_inputs_Performance.timeAllowedToLive = timeAllowedToLive;
		D1Q1SB4.S1.C1.exampleMMXU_1.gse_inputs_Performance.T = T;
		D1Q1SB4.S1.C1.exampleMMXU_1.gse_inputs_Performance.stNum = stNum;
		D1Q1SB4.S1.C1.exampleMMXU_1.gse_inputs_Performance.sqNum = sqNum;
		if (D1Q1SB4.S1.C1.exampleMMXU_1.gse_inputs_Performance.datasetDecodeDone != NULL) {
			D1Q1SB4.S1.C1.exampleMMXU_1.gse_inputs_Performance.datasetDecodeDone(timeAllowedToLive, T, stNum, sqNum);
		}
	}
	if (gocbRefLength == 34 && strncmp((const char *) gocbRef, "E1Q1SB1C1/LLN0$GO$AnotherPositions", gocbRefLength) == 0) {
		if (stNum != D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_AnotherPositions.stNum) {
			ber_decode_E1Q1SB1_C1_Positions(dataset, &D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_AnotherPositions.E1Q1SB1_C1_Positions);
		}
		D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_AnotherPositions.timeAllowedToLive = timeAllowedToLive;
		D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_AnotherPositions.T = T;
		D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_AnotherPositions.stNum = stNum;
		D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_AnotherPositions.sqNum = sqNum;
		if (D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_AnotherPositions.datasetDecodeDone != NULL) {
			D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_AnotherPositions.datasetDecodeDone(timeAllowedToLive, T, stNum, sqNum);
		}
	}
	if (gocbRefLength == 30 && strncmp((const char *) gocbRef, "E1Q1SB1C1/LLN0$GO$ItlPositions", gocbRefLength) == 0) {
		if (stNum != D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.stNum) {
			ber_decode_E1Q1SB1_C1_Positions(dataset, &D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.E1Q1SB1_C1_Positions);
		}
		D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.timeAllowedToLive = timeAllowedToLive;
		D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.T = T;
		D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.stNum = stNum;
		D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.sqNum = sqNum;
		if (D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.datasetDecodeDone != NULL) {
			D1Q1SB4.S1.C1.RSYNa_1.gse_inputs_ItlPositions.datasetDecodeDone(timeAllowedToLive, T, stNum, sqNum);
		}
	}
        // if gocbRefLength is 22 and gocbRef is "GTNET1C1/LLN0$G0$Gcb01", the GOOSE of GTNET1 is received  
        if (gocbRefLength == 22 && strncmp((const char *) gocbRef, "GTNET1C1/LLN0$GO$Gcb01", gocbRefLength) == 0){
                //fprintf(stdout, "VEN receives a GOOSE whose gocbRef is GTNET1C1/LLN0$GO$Gcb01 !\n");
                
                if (stNum != ReceiveGTNET1.received_gtnet_c1_outputs1.stNum) {
			// assign P, Q, Temperature, Opt value of GOOSE to local IED ReceiveGTNET1
                        ber_decode_GTNET1_C1_outputs1(dataset, &ReceiveGTNET1.received_gtnet_c1_outputs1); 
		}
                ReceiveGTNET1.received_gtnet_c1_outputs1.T = T;
                ReceiveGTNET1.received_gtnet_c1_outputs1.stNum = stNum;
		ReceiveGTNET1.received_gtnet_c1_outputs1.sqNum = sqNum;
                
                //fprintf (stdout, "%c", dataset);
                
                //fprintf(stdout, "The GOOSE trigger flag is: %u \n", ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_1_GOOSETrigger.stVal);
                
                //fprintf(stdout, "The P of Substation is: %f \n", ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_2_SubP.mag.f);
                
                //fprintf(stdout, "The Q of Substation is: %f \n", ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_3_SubQ.mag.f);
                
                //fprintf(stdout, "The P of House 21 is: %f \n", ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_4_21P.mag.f);

                //fprintf(stdout, "The Q of House 21 is: %f \n", ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_5_21Q.mag.f);
                
                //fprintf(stdout, "The Temperature of House 21 is: %f \n", ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_6_21T.mag.f);
                
                //fprintf(stdout, "The Opt of House 21 is: %f \n", ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_7_21Opt.mag.f);         
                
                                
                wrapper_t *m = wrapper_create();
                wrapper_db_updateVENGooseGTNET1SQL(m); // update the GTNET1 record in the database 
        }
        // if gocbRefLength is 22 and gocbRef is "GTNET2C1/LLN0$G0$Gcb01", the GOOSE of GTNET2 is received  
        if (gocbRefLength == 22 && strncmp((const char *) gocbRef, "GTNET2C1/LLN0$GO$Gcb01", gocbRefLength) == 0){
                //fprintf(stdout, "VEN receives a GOOSE whose gocbRef is GTNET1C1/LLN0$GO$Gcb01 !\n");
                
                if (stNum != ReceiveGTNET2.received_gtnet_c1_outputs2.stNum) {
			// assign P, Q, Temperature, Opt value of GOOSE to local IED ReceiveGTNET1
                        ber_decode_GTNET2_C1_outputs2(dataset, &ReceiveGTNET2.received_gtnet_c1_outputs2); 
		}
                ReceiveGTNET2.received_gtnet_c1_outputs2.T = T;
                ReceiveGTNET2.received_gtnet_c1_outputs2.stNum = stNum;
		ReceiveGTNET2.received_gtnet_c1_outputs2.sqNum = sqNum;
                                                
                wrapper_t *m = wrapper_create();
                wrapper_db_updateVENGooseGTNET2SQL(m); // update the GTNET2 record in the database 
        }
        // if gocbRefLength is 22 and gocbRef is "GTNET3C1/LLN0$G0$Gcb01", the GOOSE of GTNET3 is received  
        if (gocbRefLength == 22 && strncmp((const char *) gocbRef, "GTNET3C1/LLN0$GO$Gcb01", gocbRefLength) == 0){
                //fprintf(stdout, "VEN receives a GOOSE whose gocbRef is GTNET1C1/LLN0$GO$Gcb01 !\n");
                
                if (stNum != ReceiveGTNET3.received_gtnet_c1_outputs3.stNum) {
			// assign P, Q, Temperature, Opt value of GOOSE to local IED ReceiveGTNET1
                        ber_decode_GTNET3_C1_outputs3(dataset, &ReceiveGTNET3.received_gtnet_c1_outputs3); 
		}
                ReceiveGTNET3.received_gtnet_c1_outputs3.T = T;
                ReceiveGTNET3.received_gtnet_c1_outputs3.stNum = stNum;
		ReceiveGTNET3.received_gtnet_c1_outputs3.sqNum = sqNum;
                                                
                wrapper_t *m = wrapper_create();
                wrapper_db_updateVENGooseGTNET3SQL(m); // update the GTNET1 record in the database 
        }
}


