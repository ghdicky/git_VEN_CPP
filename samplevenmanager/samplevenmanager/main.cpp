
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
/* #include "pistache/endpoint.h"*/

/* include the "HTTPServer.h" */ 
/* so that the Class/Type HTTPServer is declared and can be used as pointer type */
/* #include "HTTPServer.h" */


/* include the mongoose.h library for running HTTP server */
/*#include "mongoose.h"*/


shared_ptr<IVENManager> venManager;

string vtnURL;
string venName;

/*shared_ptr<HTTPServer> httpserver;*/


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
/*using namespace Pistache;*/

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

/*void runHttpServer()*/
/*{*/
    /* initialize the server address as 0.0.0.0:800 */
    /*addr(Pistache::Ipv4::any();*/
    /*addr->port = Pistache::Port(800);*/
    
    /* use 1 thread */
    /*opts = Http::Endpoint::options().threads(1);*/
    
    
    /*server.init(opts);*/
    
    /*The HTTP request handler is HTTPServer */
    /*httpserver = Pistache::Http::make_handler<HTTPServer>();*/
    
    /*server.setHandler(httpserver);*/
    
    /*server.setHandler(httpserver);*/
    
    /*server.serve();*/


/*} */



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

	signal(SIGINT, signalHandler);
        
        /* display log file in terminal */
        displayLog();
        
        
        
        std::thread first (&IVENManager::run, venManager); /* This is the 1st thread running venManager->run() */  
        std::thread second (&IVENManager::selectOptFunction, venManager); /* This is the 2nd thread running venManager->selectOptType() */
        
        
        /* run the HTTP server */
        /*runHttpServer();*/
       
       	/*venManager->run();*/
        first.join();
        second.join();
        
        
                       

	return 0;
}
