/**
 * This class represents a independent task-stealing scheduler. The scheduler uses MPIWinSchedulingStrategy as queue
 * to make ist accessible from other task-stealing scheduling.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */


#ifndef _TASKSTEALINGSCHEDULER_H
#define _TASKSTEALINGSCHEDULER_H

#include "AbstractScheduler.h"
#include "MpiWinSchedulingStrategy.h"
#include "../worker/Worker.h"


class TaskStealingScheduler: public AbstractScheduler {
private:
    /**
     * This MPI_Win represent the status of the scheduler. The scheduler can be idle and working.
     */
    MPI_Win win_status;
    /**
     * The status of the scheduler.
     */
    int* status;
    /**
     *  The TaskStealingWorker
     */
    Worker* worker;
public:

    /**
     * Constructs a new TaskStealingScheduler.
     *
     * @param scheduling_strategy the scheduling strategy instance
     * @param data_miner the data miner instance
     * @param rank the rank of the TaskStealingScheduler relative to the task stealing communicator
     * @param number_of_processors the number of processors in the task stealing communicator
     */
    TaskStealingScheduler(MpiWinSchedulingStrategy* scheduling_strategy, DataMining* data_miner, int rank, int number_of_processors);
    /**
     * Destructs the TaskStealingScheduler and frees the MPI window and the status.
     */
    ~TaskStealingScheduler();

    void execute(int argc, char* argv[]);

    /**
     * The main loop of the master - worker algorithm.
     * The function returns when all scientific tasks are completed.
     */
    void run();

    /**
     * Returns, if the scientific calculation finished.
     *
     * @return TRUE if the scientific calculation finished
     */
    bool is_finish();
};

#endif //_TASKSTEALINGSCHEDULER_H
