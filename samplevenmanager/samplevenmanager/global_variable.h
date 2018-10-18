/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   global_variable.h
 * Author: hao
 *
 * Created on 09 June 2018, 02:48
 */

#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H


#include "../../oadr/oadr/request/Oadr2bHelper.h"

/*include header files necessary for MySQL database operation*/
//#include <iostream>
//#include "../../mysqlmgr/MyDB.h"

/* include <string> for string type */
/* #include <string> */

/* Declaration of reference variable must be initialised; */
/* Null reference will not work */
/*extern oadr2b::ei::OptTypeType::value global_optType = oadr2b::ei::OptTypeType::optOut;*/
extern oadr2b::ei::OptTypeType::value global_optType;

/*extern std::string global_optType;*/

/* Declaration of global database db reference variable must be initialised; */
//extern MyDB db;


#endif /* GLOBAL_VARIABLE_H */

