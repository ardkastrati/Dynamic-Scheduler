#ifndef _WORKEREXECUTOR_H
#define _WORKEREXECUTOR_H

#include "../Executor.h"
#include "Worker.h"

/**
 * This class represents a worker running in its own process with its own MPI rank.
 *
 * The executor() function is called from the the main function.
 *
 * First the executor() function calls preprocessing().
 * After that the executor() functions calls the wait_for_worker() function.
 * This function blocks until a new MPI message receive, and starts the computation.
 * This is repeated until the worker receives a MPI massage with the tag STOP.
 * At the end the executor() function calls the postprocessing() function.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */
class WorkerExecutor : public Executor, public Worker {
public:

    /**
     * Constructs a new WorkerExecutor object.
     * This constructor calls the super constructor from Executor.
     *
     * @param rank the MPI rank of the processor, that runs the executor code
     * @param number_of_processors the total number of processors of the MPI world
     */
    WorkerExecutor(int rank, int number_of_processors);

    void run_task(Task task);

    /**
     * Calls the code_preprocessing_slave() function of the scientific code and pass the command lines arguments.
     * When the code_preprocessing_slave() function returns, a MPI message with the TAG FINISH will be send to the Master
     * (rank 0).
     *
     * @param argc command line argument count
     * @param argv command line arguments
 */
    void preprocessing(int argc, char* argv[]);

    void postprocessing();

    /**
     * Calls the code_run_task() function of the scientific and starts the scientific calculation with the given task.
     * If the computation finish, a MPI message with the TAG finish will be send to the Master (rank 0).
     *
     * @param task scientific task to be computed
     */
    void place_task(Task task);

    void execute(int argc, char* argv[]);

private:

    /**
     * Waits until the worker receive a new MPI message from the Master (rank 0).
     * There are 2 different types of messages with following TAGs:
     * - START: the worker received a new task and starts the computation.
     * - STOP: the hole scientific calculation was finished and the worker can terminate.
     */
    void wait_for_task();
};

#endif //_WORKEREXECUTER_H
