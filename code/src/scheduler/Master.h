/**
 * The Master class inherits from the AbstractScheduler class and implements the master-worker scheduling design.
 * The Master class collects scientific tasks and orders them depending on the chosen scheduling strategy, currently FIFO, LIFO, SJF and LJF.
 * The class adds worker executor in a queue and sends them scientific tasks using the MPI_Send() function and waits for response.
 * FINISH or REQUEST tags using the MPI_Recv() function. If the master receives a FINISH tag, the master will add the worker to the free_worker queue.
 * If the master receives a REQUEST tag with a scientific task, the master will add the scientific task to the scheduling queue.
 *
 * If the is_finish() function returns true, the master will send a message using MPI_Send() with the tag STOP to all worker executors and
 * database servers to terminate them.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */


#ifndef _MASTER_H
#define _MASTER_H

#include "AbstractScheduler.h"
#include "../datamining/DataMining.h"
#include "MasterSchedulingStrategy.h"
#include <queue>

class Master: public AbstractScheduler {
    private:
        /**
         * The queue of free workers. The queue stores the rank of the workers currently  idling.
         */
        std::queue<int>* free_worker;

        /**
         * The main loop of the master - worker algorithm.
         * the function returns when all scientific tasks are completed
         */
        void run();

        /**
         * Checks whether all scientific tasks are completed.
         *All tasks completed <=> free_worker == worker_count && tasksqueue is empty
         *
         * @return TRUE if all scientific tasks are completed
         */
        bool is_finish();

    public:
        /**
         * Creates a new master for master - worker scheduling.
         * The constructor only initializes the queue free_worker and then calls the super constructor.
         *
         * @param scheduling_strategy the scheduling strategy to be set
         * @param rank the MPI rank of the processors, that execute the scheduler
         * @param number_of_processors the total number of processors of the MPI world
         */
        Master(MasterSchedulingStrategy* scheduling_strategy, int rank, int number_of_processors);

        /**
         * Deletes the queue free_worker object
         */
        ~Master();

        /**
         * Overrides the execute function from executor. This function is called to start the master.
         *
         * @param argc command line argument count
         * @param argv command line arguments
         */
        void execute(int argc, char* argv[]);
};

#endif //_MASTER_H
