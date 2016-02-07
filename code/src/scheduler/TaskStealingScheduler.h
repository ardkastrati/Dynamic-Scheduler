/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _TASKSTEALINGSCHEDULER_H
#define _TASKSTEALINGSCHEDULER_H

#include "AbstractScheduler.h"
#include "MpiWinSchedulingStrategy.h"
#include "../worker/Worker.h"


class TaskStealingScheduler: public AbstractScheduler {
    private:
        MPI_Win win_status;
        int* status;
        Worker* worker;
    public:
        TaskStealingScheduler(MpiWinSchedulingStrategy* scheduling_strategy, DataMining* data_miner, int rank, int number_of_processors);
        ~TaskStealingScheduler();
        void execute(int argc, char* argv[]);


        /**
         * The main loop of the master - worker algorithm.
         * the function returns when all scientific tasks are completed
         */
        void run();

    bool is_finish();
};

#endif //_TASKSTEALINGSCHEDULER_H
