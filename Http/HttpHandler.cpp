/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* Include the pistach library for running a HTTP sever; */
/*#include <pistache/endpoint.h> */
#include "HttpHandler.h"

#include <oadr/manager/VENManager.h>


HttpHandler::HttpHandler()
{
}

HttpHandler::~HttpHandler()
{
}


void onRequest(const Http::Request& request, Http::ResponseWriter response, shared_ptr<IVENManager> venManager){

 string requestBody = request.body();
        
        if ( (requestBody.compare("OptIn") == 0) || (requestBody.compare("OptOut") == 0) ){
            venManager->configDefaultOpt(requestBody);
        }
        
        // cout << request.resource() << endl;
                
 
        response.send(Http::Code::Ok, "Hello World");
        
        cout << "An HTTP Request has been received! " << endl;
    
}


