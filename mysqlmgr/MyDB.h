/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyDB.h
 * Author: hao
 *
 * Created on 15 July 2018, 22:20
 */

#ifndef MYDB_H
#define MYDB_H

/*include the file needed for MyDB */
#include <iostream>
#include <string>



/* mysql.h is from package libmysqlclient-dev, path is /usr/include/mysql/mysql.h*/
/* install the package by >sudo apt-get install libmysqlclient-dev */
#include <mysql/mysql.h>

using namespace std;


class MyDB {
    
public:
        
        MyDB(); //declare constructor for Class MyDB
        ~MyDB(); //declare the desctructor for Class MyDB
        bool connectDB(string host, string user, string pwd, string db_name); //declare the connectDB() function to connect to mySQL database
        bool closeDB(); // decleare the closeDB() function to quit the mySQL database 
        
        bool fetchSQL(string sql); // declare the fetchSQL() function to execute SQL SELECT query
        bool updateDefaultOptSQL(string sql); // declare the updateDefaultOptSQL() function to update the Default Opt mode of VEN
        string getDefaultOptSQL(); // declare the getDefaultOptSQL() function to retrieve the Default Opt mode of VEN
        
        bool updateVENInfoSQL(string sql); // declare the updateVENNameSQL() function to update the VEN Info
        string getVENNameSQL(); // declare the getDefaultOptSQL() function to retrieve the Default Opt mode of VEN
        
        bool updateVENMessageSQL(string sql); // declare the updateVENNameSQL() function to update the VEN Logs
        
        bool updateVENEventSQL(string sql); // declare the updateVENEventSQL() function to update the VEN Events 
        
        bool updateVENGooseGTNET1SQL(string sql); // declare the updateVENGooseGTNET1SQL() function to update the VEN GOOSE 
        bool updateVENGooseGTNET2SQL(string sql); // declare the updateVENGooseGTNET2SQL() function to update the VEN GOOSE 
        bool updateVENGooseGTNET3SQL(string sql); // declare the updateVENGooseGTNET3SQL() function to update the VEN GOOSE 
        
        bool updateVENEventSignalSQL(string sql); // declare the updateVENEventSignalSQL() function to update the VEN Event signals 
        bool deleteVENEventSignalSQL(string sql); // declare the deleteVENEventSignalSQL() function to delete the VEN Event signals 
        
        bool eventRecordExistSQL(string sql); // check if a specific event exists in MySQL
        
        bool eventSignalExistSQL(string sql); // check if a specific event signal exists in MySQL
        
        string getIndividualOptSQL(string eventID); // declare the getIndividualOptSQL() function to retrieve the Individual Opt mode of specific eventID        
      
        string getRequestIDSQL(string eventID); // declare the getRequestIDSQL() function to retrieve the request ID of specific eventID 

private:
        MYSQL *connection;
        MYSQL_RES *result;
        MYSQL_ROW row;
    
};


extern MyDB db;
extern MyDB db_GOOSE;
extern MyDB db_VENImpl;



#endif /* MYDB_H */

