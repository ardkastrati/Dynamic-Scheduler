/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _TASKSTEALINGSCHEDULER_H
#define _TASKSTEALINGSCHEDULER_H

#include "AbstractScheduler.h"
#include "MpiWinSchedulingStrategy.h"


class TaskStealingScheduler: public AbstractScheduler {
    private:
    public:
        TaskStealingScheduler(MpiWinSchedulingStrategy* scheduling_strategy, DataMining* data_miner, int rank, int number_of_processors);
        void execute(int argc, char* argv[]);

        /**
         * This function is called after all scientific tasks are completed.
         * This function runs the calls the scientific postprocessing_master() code
         */
        void postprocessing();

        /**
         * The main loop of the master - worker algorithm.
         * the function returns when all scientific tasks are completed
         */
        void run();


    bool is_finish();
};

#endif //_TASKSTEALINGSCHEDULER_H
