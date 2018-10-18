/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   httpmanager.h
 * Author: hao
 *
 * Created on 15 July 2018, 18:38
 */

#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

/* include the pistache library for running a Http server; */
#include <pistache/endpoint.h>

using namespace std;
using namespace Pistache;

class HttpHandler : public Http::Handler {   

public:   
    
    HttpHandler();
    virtual ~HttpHandler();
    
    HTTP_PROTOTYPE(HttpHandler)
               
    void onRequest(const Http::Request& request, Http::ResponseWriter response); 

};


#endif /* HTTPMANAGER_H */

