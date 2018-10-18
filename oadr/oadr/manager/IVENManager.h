/*
 * IVENManager.h
 *
 *  Created on: Jul 9, 2015
 *      Author: dupes
 */

#ifndef OADR_OADR_MANAGER_IVENMANAGER_H_
#define OADR_OADR_MANAGER_IVENMANAGER_H_

#include <exception>

#include "../helper/thread/IRun.h"
#include "../scheduler/Scheduler.h"

class IVENManager : public IRun
{
public:
	IVENManager();
	virtual ~IVENManager();

	virtual Scheduler *getScheduler() = 0;
        
        /* Declare method selectOptFunction() which is actually defined in VENManager.cpp */
        virtual void selectOptFunction() = 0;
        
        
        /* Declare method configDefaultOpt() which is actually defined in VENManager.cpp */
        virtual string configDefaultOpt(string http_opt) = 0;
        
         
        /* Declare method configVENInfo() which is actually defined in VENManager.cpp */
        virtual void configVENInfo() = 0;
        
        
        /* Declare method getVENInfoDB() which is actually defined in VENManager.cpp */
        virtual string getVENInfoDB() = 0;
        
        
        /* Declare method configIndividualOpt() in IVENManager.h and this method is actually defined in VENManager.cpp */
        virtual string configIndividualOpt(string eventID, string individualOptValue) = 0;
        
        
};

#endif /* OADR_OADR_MANAGER_IVENMANAGER_H_ */
