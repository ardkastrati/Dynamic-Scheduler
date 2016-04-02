#ifndef _WORKER_H
#define _WORKER_H

#include "../TypesExtern.h"
#include "WorkerForwarder.h"

/**
 * This interface defines all functions a worker must provide.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */
class Worker {
public:
    /**
     * Calls the code_run_task() function of the scientific and starts the scientific calculation with the given task.
     *
     * @param task scientific task to be computed
     */
    virtual void run_task(Task task) = 0;

    /**
     * Calls the code_preprocessing_slave() function of the scientific code and pass the command lines arguments.
     *
     * @param argc command line argument count
     * @param argv command line arguments
     */
    virtual void preprocessing(int argc, char* argv[]) = 0;

    /**
     * Calls the code_postprocessing_slave() function of the scientific code.
     */
    virtual void postprocessing() = 0;

    /**
     * This function is called from the scientific code to place a new task in the scheduling queue.
     *
     * @param task task to be placed in the scheduling queue
     */
    virtual void place_task(Task task) = 0;
};

#endif //_WORKER_H
