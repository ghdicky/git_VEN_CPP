/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <stdlib.h>
#include "mysqlwrapper.h"
#include "../mysqlmgr/MyDB.h"
#include "src/ied.h"
#include <string>
#include <iostream>

using namespace std;

struct wrapper {
    void *obj;
};

wrapper_t *wrapper_create()
{
    wrapper_t *m;
    //MyDB *obj;
    m = (__typeof__(m))malloc(sizeof(*m));
    
    //obj = db;
    m->obj = &db_GOOSE;

    
           
    return m;
}

void wrapper_db_getVENNameSQL(wrapper_t *m)
{
    MyDB *obj;
    
    if (m == NULL)
        return;
    
    obj = static_cast<MyDB *>(m->obj);
    obj->getVENNameSQL();
    
}

void wrapper_db_updateVENGooseGTNET1SQL(wrapper_t *m)
{
    
    MyDB *obj;
    
    long long dtstamp_second;
    
    if (m == NULL)
        return;
    
    obj = static_cast<MyDB *>(m->obj);
    
    
    //time_t dtstamp is the timestamp obtained from GOOSE of GTNET1 and will be stored in the database
    dtstamp_second = ReceiveGTNET1.received_gtnet_c1_outputs1.T;
    
    // as timestamp of GOOSE is using opposite endian, need to swap
    // can diretly use function int64_t __builtin_bswap64(int64_t x)
    dtstamp_second = __builtin_bswap64(dtstamp_second); 
    
    // shift the first 4 byte integer part to the lower 4 byte position so that dtstamp_second holds the part of integer second of the GOOSE timestamp   
    dtstamp_second >>= 32;
    
    db_GOOSE.connectDB("localhost", "hao", "111111", "test");
    
    // update record for substation
    obj->updateVENGooseGTNET1SQL("INSERT INTO substation (dtstamp, P, Q) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                               "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_2_SubP.mag.f) + 
                                                                                               "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_3_SubQ.mag.f) + 
                                                                                                        "')");   
    
    // update record for house21
    obj->updateVENGooseGTNET1SQL("INSERT INTO house21 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_4_21P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_5_21Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_6_21T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_7_21Opt.mag.f) + "')");
    
    // update record for house22
    obj->updateVENGooseGTNET1SQL("INSERT INTO house22 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_8_22P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_9_22Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_10_22T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_11_22Opt.mag.f) + "')");
    
    // update record for house23
    obj->updateVENGooseGTNET1SQL("INSERT INTO house23 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_12_23P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_13_23Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_14_23T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_15_23Opt.mag.f) + "')");
    
    // update record for house24
    obj->updateVENGooseGTNET1SQL("INSERT INTO house24 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_16_24P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_17_24Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_18_24T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_19_24Opt.mag.f) + "')");
    
    // update record for house25
    obj->updateVENGooseGTNET1SQL("INSERT INTO house25 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_20_25P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_21_25Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_22_25T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_23_25Opt.mag.f) + "')");
    
    // update record for house26
    obj->updateVENGooseGTNET1SQL("INSERT INTO house26 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_24_26P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_25_26Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_26_26T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_27_26Opt.mag.f) + "')");
    
    // update record for house27
    obj->updateVENGooseGTNET1SQL("INSERT INTO house27 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_28_27P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_29_27Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_30_27T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_31_27Opt.mag.f) + "')");
    
    // update record for house28
    obj->updateVENGooseGTNET1SQL("INSERT INTO house28 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_32_28P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_33_28Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_34_28T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_35_28Opt.mag.f) + "')");
    
    // update record for house29
    obj->updateVENGooseGTNET1SQL("INSERT INTO house29 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_36_29P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_37_29Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_38_29T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_39_29Opt.mag.f) + "')");
    
    // update record for house30
    obj->updateVENGooseGTNET1SQL("INSERT INTO house30 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_40_30P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_41_30Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_42_30T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_43_30Opt.mag.f) + "')");
    
    // update record for house31
    obj->updateVENGooseGTNET1SQL("INSERT INTO house31 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_44_31P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_45_31Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_46_31T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_47_31Opt.mag.f) + "')");
    
    // update record for house48
    obj->updateVENGooseGTNET1SQL("INSERT INTO house48 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_48_48P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_49_48Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_50_48T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_51_48Opt.mag.f) + "')");
    
    // update record for house49
    obj->updateVENGooseGTNET1SQL("INSERT INTO house49 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_52_49P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_53_49Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_54_49T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_55_49Opt.mag.f) + "')");
    
    // update record for house50
    obj->updateVENGooseGTNET1SQL("INSERT INTO house50 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_56_50P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_57_50Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_58_50T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_59_50Opt.mag.f) + "')");
    
    // update record for house51
    obj->updateVENGooseGTNET1SQL("INSERT INTO house51 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_60_51P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_61_51Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_62_51T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET1.received_gtnet_c1_outputs1.C1_GGIO_63_51Opt.mag.f) + "')");   

    db_GOOSE.closeDB();
}

void wrapper_db_updateVENGooseGTNET2SQL(wrapper_t *m)
{
    
    MyDB *obj;
    
    long long dtstamp_second;
    
    if (m == NULL)
        return;
    
    obj = static_cast<MyDB *>(m->obj);
    
    
    //time_t dtstamp is the timestamp obtained from GOOSE of GTNET2 and will be stored in the database
    dtstamp_second = ReceiveGTNET2.received_gtnet_c1_outputs2.T;
    
    // as timestamp of GOOSE is using opposite endian, need to swap
    // can diretly use function int64_t __builtin_bswap64(int64_t x)
    dtstamp_second = __builtin_bswap64(dtstamp_second); 
    
    // shift the first 4 byte integer part to the lower 4 byte position so that dtstamp_second holds the part of integer second of the GOOSE timestamp   
    dtstamp_second >>= 32;
    
    db_GOOSE.connectDB("localhost", "hao", "111111", "test");
    
    // update record for house52
    obj->updateVENGooseGTNET2SQL("INSERT INTO house52 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_66_52P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_67_52Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_68_52T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_69_52Opt.mag.f) + "')");
    
    // update record for house53
    obj->updateVENGooseGTNET2SQL("INSERT INTO house53 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_70_53P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_71_53Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_72_53T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_73_53Opt.mag.f) + "')");
    
    // update record for house54
    obj->updateVENGooseGTNET2SQL("INSERT INTO house54 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_74_54P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_75_54Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_76_54T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_77_54Opt.mag.f) + "')");
    
    // update record for house55
    obj->updateVENGooseGTNET2SQL("INSERT INTO house55 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_78_55P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_79_55Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_80_55T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_81_55Opt.mag.f) + "')");
    
    // update record for house56
    obj->updateVENGooseGTNET2SQL("INSERT INTO house56 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_82_56P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_83_56Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_84_56T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_85_56Opt.mag.f) + "')");
    
    // update record for house57
    obj->updateVENGooseGTNET2SQL("INSERT INTO house57 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_86_57P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_87_57Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_88_57T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_89_57Opt.mag.f) + "')");
    
    // update record for house59
    obj->updateVENGooseGTNET2SQL("INSERT INTO house59 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_90_59P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_91_59Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_92_59T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_93_59Opt.mag.f) + "')");
    
    // update record for house60
    obj->updateVENGooseGTNET2SQL("INSERT INTO house60 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_94_60P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_95_60Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_96_60T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_97_60Opt.mag.f) + "')");
    
    // update record for house61
    obj->updateVENGooseGTNET2SQL("INSERT INTO house61 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_98_61P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_99_61Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_100_61T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_101_61Opt.mag.f) + "')");
    
    // update record for house62
    obj->updateVENGooseGTNET2SQL("INSERT INTO house62 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_102_62P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_103_62Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_104_62T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_105_62Opt.mag.f) + "')");
    
    // update record for house63
    obj->updateVENGooseGTNET2SQL("INSERT INTO house63 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_106_63P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_107_63Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_108_63T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_109_63Opt.mag.f) + "')");
    
    // update record for house64
    obj->updateVENGooseGTNET2SQL("INSERT INTO house64 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_110_64P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_111_64Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_112_64T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_113_64Opt.mag.f) + "')");
    
    // update record for house65
    obj->updateVENGooseGTNET2SQL("INSERT INTO house65 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_114_65P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_115_65Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_116_65T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_117_65Opt.mag.f) + "')");
    
    // update record for house66
    obj->updateVENGooseGTNET2SQL("INSERT INTO house66 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_118_66P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_119_66Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_120_66T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_121_66Opt.mag.f) + "')");
    
    // update record for house67
    obj->updateVENGooseGTNET2SQL("INSERT INTO house67 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_122_67P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_123_67Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_124_67T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET2.received_gtnet_c1_outputs2.C1_GGIO_125_67Opt.mag.f) + "')");   

    db_GOOSE.closeDB();
}

void wrapper_db_updateVENGooseGTNET3SQL(wrapper_t *m)
{
    
    MyDB *obj;
    
    long long dtstamp_second;
    
    if (m == NULL)
        return;
    
    obj = static_cast<MyDB *>(m->obj);
    
    
    //time_t dtstamp is the timestamp obtained from GOOSE of GTNET3 and will be stored in the database
    dtstamp_second = ReceiveGTNET3.received_gtnet_c1_outputs3.T;
    
    // as timestamp of GOOSE is using opposite endian, need to swap
    // can diretly use function int64_t __builtin_bswap64(int64_t x)
    dtstamp_second = __builtin_bswap64(dtstamp_second); 
    
    // shift the first 4 byte integer part to the lower 4 byte position so that dtstamp_second holds the part of integer second of the GOOSE timestamp   
    dtstamp_second >>= 32;
    
    db_GOOSE.connectDB("localhost", "hao", "111111", "test");
    
    // update record for house68
    obj->updateVENGooseGTNET3SQL("INSERT INTO house68 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_130_68P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_131_68Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_132_68T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_133_68Opt.mag.f) + "')");
    
    // update record for house69
    obj->updateVENGooseGTNET3SQL("INSERT INTO house69 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_134_69P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_135_69Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_136_69T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_137_69Opt.mag.f) + "')");
    
    // update record for house70
    obj->updateVENGooseGTNET3SQL("INSERT INTO house70 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_138_70P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_139_70Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_140_70T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_141_70Opt.mag.f) + "')");
    
    // update record for section42
    obj->updateVENGooseGTNET3SQL("INSERT INTO section42 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_142_42P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_143_42Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_144_42T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_145_42Opt.mag.f) + "')");
    
    // update record for section43
    obj->updateVENGooseGTNET3SQL("INSERT INTO section43 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_146_43P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_147_43Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_148_43T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_149_43Opt.mag.f) + "')");
    
    // update record for section44
    obj->updateVENGooseGTNET3SQL("INSERT INTO section44 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_150_44P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_151_44Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_152_44T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_153_44Opt.mag.f) + "')");
    
    // update record for section45
    obj->updateVENGooseGTNET3SQL("INSERT INTO section45 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_154_45P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_155_45Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_156_45T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_157_45Opt.mag.f) + "')");
   
    // update record for section46
    obj->updateVENGooseGTNET3SQL("INSERT INTO section46 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_158_46P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_159_46Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_160_46T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_161_46Opt.mag.f) + "')");
    
    // update record for section47
    obj->updateVENGooseGTNET3SQL("INSERT INTO section47 (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_162_47P.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_163_47Q.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_164_47T.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_165_47Opt.mag.f) + "')");
    
    // update record for section47B
    obj->updateVENGooseGTNET3SQL("INSERT INTO section47B (dtstamp, P, Q, temperature, opt) VALUES (FROM_UNIXTIME(" + std::to_string(dtstamp_second) + 
                                                                                                              "), '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_166_47BP.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_167_47BQ.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_168_47BT.mag.f) + 
                                                                                                              "', '" + std::to_string(ReceiveGTNET3.received_gtnet_c1_outputs3.C1_GGIO_169_47BOpt.mag.f) + "')");                                                                 

    db_GOOSE.closeDB();
}
