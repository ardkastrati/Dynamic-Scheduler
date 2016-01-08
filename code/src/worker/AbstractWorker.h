/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _ABSTRACTWORKER_H
#define _ABSTRACTWORKER_H

#include "../Executer.h"
#include "../scheduler/Types.h"


class AbstractWorker: public Executer {
public: 

    virtual void run_task(TaskType task) = 0;
    /**
     * @param listener
     */
    //void register_bookkeeping_listener(void listener);
    
    /**
     * @param listener
     */
    //void remove_bookkeeping_listener(void listener);

};

#endif //_ABSTRACTWORKER_H
