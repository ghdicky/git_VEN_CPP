/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mysqlwrapper.h
 * Author: hao
 *
 * Created on 06 November 2018, 11:37
 */

#ifndef MYSQLWRAPPER_H
#define MYSQLWRAPPER_H




#ifdef __cplusplus
extern "C" {
#endif

    
    struct wrapper;
    
    typedef struct wrapper wrapper_t;
    
    wrapper_t *wrapper_create();
    
    void wrapper_db_getVENNameSQL(wrapper_t *m); // wrap getVENNameSQL in MyDB.cpp so that it can be used in gseDecode.c
    
    void wrapper_db_updateVENGooseGTNET1SQL(wrapper_t *m); // wrap updateVENGooseSQL in MyDB.cpp so that it can be used in gseDecode.c
    void wrapper_db_updateVENGooseGTNET2SQL(wrapper_t *m); // wrap updateVENGooseSQL in MyDB.cpp so that it can be used in gseDecode.c
    void wrapper_db_updateVENGooseGTNET3SQL(wrapper_t *m); // wrap updateVENGooseSQL in MyDB.cpp so that it can be used in gseDecode.c
    
#ifdef __cplusplus
}
#endif

#endif /* MYSQLWRAPPER_H */

