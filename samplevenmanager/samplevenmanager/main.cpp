
#include <oadr/manager/VENManager.h>

#include "VENImpl.h"

#include "easylogging++.h"

#include <ostream>
#include <csignal>

/* Using thread to make the thread waiting for input and thread running venManager->run() */
/* concurrently */
#include <thread>


/* Use global variable global_optType which is defined in global_variable.h */
#include "../samplevenmanager/global_variable.h"


/* Include HTTPServer.cpp */
/*#include "HTTPServer.cpp"*/


/* Include the pistache library for running a HTTP server; */
/* the server will listen to the HTTP requests */
#include <pistache/endpoint.h>
/*#include <pistache/serializer/rapidjson.h> */
//#include <pistache/net.h>
#include "../../rapidjson/document.h"
#include "../../rapidjson/error/en.h" // this is to translate the parsing error into english






/* include the HttpHanlder header file
   in fact the type HttpHandler is linked to main.cpp by linking shared library Http */ 
//#include "../../Http/HttpHandler.h"

/* include the "HTTPServer.h" */ 
/* so that the Class/Type HTTPServer is declared and can be used as pointer type */
/* #include "HTTPServer.h" */


/* include the mongoose.h CPP library for running HTTP server */
/*#include "../../mongoose/Server.h"*/
/*#include "../../mongoose/WebController.h"*/


shared_ptr<IVENManager> venManager;

string vtnURL;
string venName;

//shared_ptr<HttpHandler> handler;


VENManagerConfig config;

bool logToStdout = true;


/* Initialise the global variable global_optType */
/* Default value is optOut */
oadr2b::ei::OptTypeType::value global_optType = oadr2b::ei::OptTypeType::optOut;
/* string global_optType = "Opt_Out"; */




/* auto opt for runHttpServer() method */
/*auto opts = Pistache::Http::Endpoint::options().threads(1);*/


/*Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(800));*/

/*Pistache::Http::Endpoint server(addr);*/


/*static const char *s_http_port = "800";
static struct mg_serve_http_opts s_http_server_opts;

struct mg_mgr mgr;
struct mg_connection *nc; */

        
using namespace samplevenmanager;
using namespace std;
using namespace Pistache;
/*using namespace Mongoose;*/

INITIALIZE_EASYLOGGINGPP

/********************************************************************************/

void signalHandler (int signum)
{
	venManager->stop();
}

/********************************************************************************/
void printUsage()
{
	cout << "Usage: " << endl;
	cout << "  ./samplevenmgr <vtn url> <ven name> true" << endl;
}

/********************************************************************************/

bool parseParams(int argc, char **argv)
{
	if (argc < 3)
		return false;

	config.vtnURL = argv[1];
	config.venName = argv[2];

	if (argc == 4 && strcmp(argv[3], "false") == 0)
		logToStdout = false;

	return true;
}

/********************************************************************************/

/*void runHttpServer()
{
    //initialize the server address as 0.0.0.0:800
    addr(Pistache::Ipv4::any();
    addr->port = Pistache::Port(800);
    
    // use 1 thread
    opts = Http::Endpoint::options().threads(1);
    
    
    server.init(opts);
    
    //The HTTP request handler is HTTPServer
    httpserver = Pistache::Http::make_handler<HTTPServer>();
    
    server.setHandler(httpserver);
    
    server.setHandler(httpserver);
    
    server.serve();


}*/



/********************************************************************************/

void displayLog()
{

/* This method will display the log file in the terminal window. */
    
/* Open a new terminal and run the specific command to display the log file*/
    system("gnome-terminal -e 'sh -c \"tail -f /home/hao/Downloads/VEN_CPP_source/logs/Hao_Ubuntu_VEN.log\"'");

/*  system("tail -f /home/hao/Downloads/VEN_CPP_source/logs/Hao_Ubuntu_VEN.log"); */
    

/* Open a new terminal and run the specific command to display the event list log*/
    system("gnome-terminal -e 'sh -c \"tail -f /home/hao/Downloads/VEN_CPP_source/logs/Hao_Ubuntu_VEN----Event-List.log\"'");
    
}

/********************************************************************************/
/* define the method ev_handler() */
/*static void ev_handler(struct mg_connection *nc, int ev, void *p){

    if (ev == MG_EV_HTTP_REQUEST){
    
        mg_serve_http(nc, (struct http_message *) p, s_http_server_opts); 
             
    }
}*/

/********************************************************************************/
/* define the method runServer() */
/*static void runServer(){

    mg_mgr_init(&mgr, NULL);

    printf("Starting web server on port %s\n", s_http_port);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    
    if (nc == NULL){
    
        printf("Failed to create listener\n");
        
        return 1;
        
    }
    
    //set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = "."; //server current directory
    s_http_server_opts.enable_directory_listing = "yes";
    
    
    for (;;){
    
        mg_mgr_poll(&mgr, 1000);
    
    }
    mg_mgr_free(&mgr);

    return 0;
} */



/********************************************************************************/

/* declare and define the Class HttpHandler */
class HttpHandler : public Http::Handler {
public:
    
    HTTP_PROTOTYPE(HttpHandler)
    
    void onRequest(const Http::Request& request, Http::ResponseWriter response){
        string requestBody = request.body();
                
        string defaultopt;
        
        string venname;
        string vtnurl; 
        
       
        //rapidjson::Document is from #include "../../rapidjson/document.h"
        //the received HTTP Post Request is of type text/plain but the text format is the same as Json such as {"defaultOptMode":"OptIn"} {"eventID":""}
        rapidjson::Document jsonBody;
        jsonBody.Parse(requestBody.c_str()); //need to convert requestBody into const char* (character string) and then parse to Json object
        
        //this is to check the parsing error 
        //cout << GetParseError_En(jsonBody.GetParseError()) << endl;
        
        //cout << jsonBody["defaultOptMode"].GetString() << endl;
        
        //the HTTP response cannot be decoded correctly by the browser if the HTTP server is running in localhost
        //This is due to security reason for cross-domain request
        //To solve this problem, the HTTP respone header must contain Access-Control-Allow-Origin, 
        //which tells the browser to process the HTTP response as if it is from a remote apache or nginx HTTP server
        response.headers().add<Http::Header::AccessControlAllowOrigin>("*");
        
        
        
        //response.headers().add<Http::Header::ContentType>(MIME(Text, Plain));
        cout <<  "The POST text is: " << requestBody << endl;
        
        //cout << "The serialized text is:" << serializeResponse << endl;
        
        // the request body in the in the format of "eventID OptIn" and need to split the strings 
        //std::istringstream iss(requestBody);
        //string subString1;
        
        //iss >> subString1;
        
       // while (iss >> subString1){
                   
       //     cout << "Substring: " << subString1 << endl;
        
       // }
       //if (requestBody.find("defaultOptMode") != std::string::npos ) {
        if (jsonBody.HasMember("defaultOptMode")) {
            
            // the key "defaultOptMode" is found in jsonBody and this HTTP Post Request is for defaultOptMode configuration
            
            //string subStringBeforeDefaultOptValue = "defaultOptMode=";
            //int defaultOptValueLength = 5;
            //string defaultOptValue = requestBody.substr(subStringBeforeDefaultOptValue.length(), defaultOptValueLength);
            
            string defaultOptValue = jsonBody["defaultOptMode"].GetString();
            
            //if ( (requestBody.compare("OptIn") == 0) || (requestBody.compare("OptOut") == 0) ){
            defaultopt = venManager->configDefaultOpt(defaultOptValue);
            
            response.send(Http::Code::Ok, defaultopt, MIME(Text, Plain));
            //} 
        
        //} else if ( (requestBody.find("eventID") != std::string::npos) && (requestBody.find("individualOptMode") != std::string::npos) ) {
        } else if ( jsonBody.HasMember("eventID") && jsonBody.HasMember("individualOptMode") ) {
            
            // the key "eventID" and "individualOptMode" are found in jsonBody and this HTTP Post Request is for Opt change of event
            //cout << "eventID is: " << jsonBody["eventID"].GetString() << " and opt is: " << jsonBody["individualOptMode"].GetString() << endl;
        
            string eventID = jsonBody["eventID"].GetString();
            string individualOptValue = jsonBody["individualOptMode"].GetString();
            
            string responseJsonBody = venManager->configIndividualOpt(eventID, individualOptValue);
            
            response.send(Http::Code::Ok, responseJsonBody, MIME(Text, Plain));
        }
        
        
        //response.send(Http::Code::Ok, defaultopt, MIME(Application, Json));
        
        // cout << request.resource() << endl;
                
        
        //response.send(Http::Code::Ok, "Hello World", MIME(Text, Plain));
        
        cout << "An HTTP Request has been received! " << endl;
    
        }
};


/********************************************************************************/

/*class MyController : public WebController
{

    public:
        void hello(Request &request, StreamResponse &response)
        {
            response << "Hello" << htmlEntities(request.get("name", "... what's your name ?")) << endl;      
        
        }
        
        void setup()
        {
            addRoute("GET", "/hello", MyController, hello);
            
        }



};*/


/********************************************************************************/

int main(int argc, char **argv)
{
	if (!parseParams(argc, argv))
	{
		printUsage();
		return 0;
	}

	shared_ptr<VENImpl> venImpl(new VENImpl(config.venName, logToStdout));

	config.services.eventService = venImpl.get();
	config.services.oadrMessage = venImpl.get();
	config.services.reportService = venImpl.get();
	config.services.exceptionService = venImpl.get();

	venManager = shared_ptr<IVENManager>(VENManager::init(config));
        
        //initialize the global database connection db
        //MyDB db;

        
        
        //MyController myController;
        //Server server(2000);
        //server.registerController(&myController);
        
        //server.start();
        
        /* define parameters for the Http server */
        //Pistache::Address addr(Pistache::Ipv4::, Pistache::Port(9080));
        //auto opts = Pistache::Http::Endpoint::options().threads(1);
        //Http::Endpoint server(addr);
        //server.init(opts);
        
        /* put the HttpHanlder module/class into the server; in fact the methods defined after receiving the HTTP request */
        //server.setHandler(Http::make_handler<HttpHandler>());
       
        
        //MyDB db;
        //db.initDB("localhost", "hao", "haoguo0428@UoM", "test");
        //db.fetchSQL("SELECT * FROM eventinfo");

	signal(SIGINT, signalHandler);
        
        /* display log file in terminal */
        displayLog();
       
        /*Http::listenAndServe<HttpHandler>("*:9080");*/
        
               
        
        
        std::thread first (&IVENManager::run, venManager); /* This is the 1st thread running venManager->run() */  
        //std::thread second (&IVENManager::selectOptFunction, venManager); /* This is the 2nd thread running venManager->selectOptType() */
        
        
        /* run the HTTP server */
        /*runHttpServer();*/
       
       	/*venManager->run();*/
        //first.join();
        //second.join();
        
        
        //http server starts running
        //server.serve(); 
        Http::listenAndServe<HttpHandler>("127.0.0.1:9080");
        
        
                       

	return 0;
}
