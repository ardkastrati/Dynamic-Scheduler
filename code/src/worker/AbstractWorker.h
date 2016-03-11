/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _ABSTRACTWORKER_H
#define _ABSTRACTWORKER_H

#include "../Executer.h"
#include "../Types.h"


class AbstractWorker: public Executer {
public: 
    AbstractWorker(int rank, int number_of_processors);
    void preporcessing(int argc, char* argv[]);

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
