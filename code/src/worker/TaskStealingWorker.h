#ifndef _TASKSTEALINGWORKER_H
#define _TASKSTEALINGWORKER_H

#include "Worker.h"
#include "../scheduler/AbstractScheduler.h"

/**
 * This class is a worker vor task-stealing. The worker sends non-blocking information to the Database Server.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */
class TaskStealingWorker : public Worker {

private:
    /**
     * The scheduler instance that holds this worker
     */
    AbstractScheduler* scheduler;

public:

    /**
     * Creates a new task-stealing worker
     *
     * @param scheduler the scheduler instance that holds this worker
     */
    TaskStealingWorker(AbstractScheduler* scheduler);

    /**
     * Calls the scientific code run task function and starts the calculation of the given task.
     * Sends an non-blocking massage to the database server: task started and task finished.
     *
     * @param task scientific task to be calculated
     */
    void run_task(Task task);

    /**
     * Calls the code_preprocessing_slave() function of the scientific code and pass the command lines arguments.
     *
     * @param argc command line argument count
     * @param argv command line arguments
    */
    void preprocessing(int argc, char* argv[]);

    /**
     * Calls the code_postprocessing_slave() function of the scientific code.
     */
    void postprocessing();


    /**
     * This function is called from the scientific code to add a new task to the scheduling queue.
     * This function sends a non-blocking message to the database server: task appeared
     *
     * @param task task to be added
     */
    void place_task(Task task);

};


#endif //_TASKSTEALINGWORKER_H
