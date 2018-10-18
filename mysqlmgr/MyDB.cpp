/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*include all necessary libraries for MyDB.cpp */
#include <iostream>
#include <cstdlib>
#include "MyDB.h"

MyDB db;

using namespace std;


// MyDB constructor
MyDB::MyDB() {
    
    connection = mysql_init(NULL); //initialise the variables for MySQL connection
    if(connection == NULL) 
    {
    
        cout << "Error:" << mysql_error(connection);
        exit(1); 
    
    }
}


// deconstructor of MyDB
MyDB::~MyDB() {

    if(connection != NULL)
    {
    
        mysql_close(connection);
    
    }

}

//initDB() will establish a connection to a specific schema/database in MySQL database  
bool MyDB::initDB(string host, string user, string pwd, string db_name) {
    
    connection = mysql_real_connect(connection, host.c_str(), user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
    
    // if connection fails, then return NULL to the connection object
    // if connection is successful, return the SQL connection the connection object
    if(connection == NULL)
    {
        
        cout << "Error:" << mysql_error(connection);
        exit(1); 
                
    }
    return true;
    
   
}


bool MyDB::fetchSQL(string sql) {

    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, sql.c_str()))
    {
    
        cout << "Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
        
        result = mysql_use_result(connection); // obtain query result
        
        // mysql_field_count() return the number of rows of the query result
        for (int i=0; i<mysql_field_count(connection); ++i)
        {
            //get the next row
            row = mysql_fetch_row(result);
            
            if(row <= 0)
            {
            
                break;
            
            }
            
            // mysql_num_fields() return the string of the fields of the current row[i] in the result           
            for (int j=0; j<mysql_num_fields(result); ++j)
            {
            
                cout << row[j] << " ";
            
            }
            cout << endl;
                
        }
        
        //free the memory storing the result
        mysql_free_result(result);
        
    }
    return true;


}


bool MyDB::updateDefaultOptSQL(string sql) {

    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, sql.c_str()))
    {
    
        cout << "Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
    
        //fetchSQL("SELECT * FROM vendefaultopt");
        
        cout << "Default Opt Mode has been updated!" << endl;
    
    }
    return true;
    
}

string MyDB::getDefaultOptSQL(){
    
    string command = "SELECT defaultopt FROM vendefaultopt";
    string defaultopt;
        
    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, command.c_str()))
    {
    
        cout << "Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
        
         result = mysql_use_result(connection); // obtain query result
     
         //get the 1st row of the result
         row = mysql_fetch_row(result);
         
         // row[0] stores the defautopt values because the whole table only has 1 row, 
         // and the query "SELECT defaultopt FROM vendefaultopt" only return 1 value 
         defaultopt = row[0];
         
         //free the memory storing the result
        mysql_free_result(result);
            
    }
    
    return defaultopt;
       
        
    
}


bool MyDB::updateVENInfoSQL(string sql) {

    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, sql.c_str()))
    {
    
        cout << "Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
    
        //fetchSQL("SELECT * FROM vendefaultopt");
        
        cout << "VEN info has been updated!" << endl;
    
    }
    return true;
    
}


string MyDB::getVENNameSQL(){
    
    string command = "SELECT venName FROM veninfo";
    string venname;
        
    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, command.c_str()))
    {
    
        cout << "Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
        
         result = mysql_use_result(connection); // obtain query result
     
         //get the 1st row of the result
         row = mysql_fetch_row(result);
         
         // row[0] stores the defautopt values because the whole table only has 1 row, 
         // and the query "SELECT defaultopt FROM vendefaultopt" only return 1 value 
         venname = row[0];
         
         //free the memory storing the result
        mysql_free_result(result);
            
    }
    
    return venname;
       
        
    
}


bool MyDB::updateVENMessageSQL(string sql) {

    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, sql.c_str()))
    {
        
        cout << "In updateVENMessageSQL, Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
    
        //fetchSQL("SELECT * FROM vendefaultopt");
        
        cout << "VEN log has been updated!" << endl;
    
    }
    return true;
    
}


bool MyDB::updateVENEventSQL(string sql) {

    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, sql.c_str()))
    {
        
        cout << "In updateVENEventSQL, Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
    
        //fetchSQL("SELECT * FROM vendefaultopt");
        
        cout << "VEN event has been updated!" << endl;
    
    }
    return true;
    
}


bool MyDB::updateVENEventSignalSQL(string sql) {

    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, sql.c_str()))
    {
        
        cout << "In updateVENSignalSQL, Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
    
        //fetchSQL("SELECT * FROM vendefaultopt");
        
        cout << "VEN event signal has been updated!" << endl;
    
    }
    return true;
    
}


bool MyDB::deleteVENEventSignalSQL(string sql) {

    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, sql.c_str()))
    {
        
        cout << "In deleteVENSignalSQL, Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
    
        //fetchSQL("SELECT * FROM vendefaultopt");
        
        cout << "VEN event signals have been deleted!" << endl;
    
    }
    return true;
    
}


bool MyDB::eventRecordExistSQL(string sql) {

    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, sql.c_str()))
    {
        
        cout << "In eventRecordExistSQL, Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
        
        result = mysql_use_result(connection); // obtain query result        
                
        //get the 1st row of the result
        row = mysql_fetch_row(result);
        
        // if row <=0, there is no matched row;
        // otherwise, there is matched row
        if (row <= 0){
            
            //free the memory storing the result
            mysql_free_result(result);
            
            cout << "There is no matched event record in MySQL." << endl;
            return false;
                
        } else {
            
            //free the memory storing the result
            mysql_free_result(result);
        
            cout << "There is matched event record in MySQL." << endl;
            return true;
            
        }
          
    }      
                            
}


bool MyDB::eventSignalExistSQL(string sql) {

    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, sql.c_str()))
    {
        
        cout << "In eventSignalExistSQL, Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
        
        result = mysql_use_result(connection); // obtain query result        
                
        //get the 1st row of the result
        row = mysql_fetch_row(result);
        
        // if row <=0, there is no matched row;
        // otherwise, there is matched row
        if (row <= 0){
            
            //free the memory storing the result
            mysql_free_result(result);
            
            cout << "There is no matched event signal record in MySQL." << endl;
            return false;
                
        } else {
            
            //free the memory storing the result
            mysql_free_result(result);
        
            cout << "There is matched event signal record in MySQL." << endl;
            return true;
            
        }
          
    }      
                            
}


string MyDB::getIndividualOptSQL(string eventID){

    string command = "SELECT optState FROM eventinfo WHERE eventID='" + eventID + "'";
    string individualOptState;
        
    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, command.c_str()))
    {
    
        cout << "Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
        
         result = mysql_use_result(connection); // obtain query result
     
         //get the 1st row of the result
         row = mysql_fetch_row(result);
         
         // row[0] stores the individualOptState value because the whole table only has 1 row, 
         // and the query "SELECT optState FROM eventinfo WHERE eventID='multiple event multiple signal'" only return 1 value 
         individualOptState = row[0];
         
         //free the memory storing the result
        mysql_free_result(result);
            
    }
    
    return individualOptState;



}



string MyDB::getRequestIDSQL(string eventID){

    string command = "SELECT requestID FROM eventinfo WHERE eventID='" + eventID + "'";
    string requestID;
    
    //return 0 when mysql_query is successful,
    //return non 0 value when mysql_query is not successful
    if(mysql_query(connection, command.c_str()))
    {
    
        cout << "Query Error:" << mysql_error(connection); 
        exit(1);
        
    } else {
        
         result = mysql_use_result(connection); // obtain query result
     
         //get the 1st row of the result
         row = mysql_fetch_row(result);
         
         // row[0] stores the requestID value because the whole table only has 1 row, 
         // and the query "SELECT requestID FROM eventinfo WHERE eventID='multiple event multiple signal'" only return 1 value 
         requestID = row[0];
         
         //free the memory storing the result
        mysql_free_result(result);
            
    }
    
    return requestID;
       

}




