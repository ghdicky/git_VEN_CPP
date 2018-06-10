
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



shared_ptr<IVENManager> venManager;

string vtnURL;
string venName;



VENManagerConfig config;

bool logToStdout = true;


/* Initialise the global variable global_optType */
/* Default value is optOut */
oadr2b::ei::OptTypeType::value global_optType = oadr2b::ei::OptTypeType::optOut;
/* string global_optType = "Opt_Out"; */


using namespace samplevenmanager;
using namespace std;

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
        
       
       	/*venManager->run();*/
        first.join();
        second.join();
      
                       

	return 0;
}
