/**
 * The Executor class is the base class for all objects that are mpi processes and have a one mpi rank.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */


#ifndef _EXECUTER_H
#define _EXECUTER_H

#include "scheduler/StrategyEnum.h"
#include "scheduler/DesignEnum.h"

class Executor {
protected:
        /**
         * The MPI rank of the processor, that runs the executor code
         */
        const int rank;
        /**
         * The total number of processors of the MPI world
         */
        const int number_of_processors;
public:
        /**
         * Constructs a new executor object and initialize the parameters rank and number_of_processors
         *
         * @param rank the MPI rank of the processor, that runs the executor code
         * @param number_of_processors the total number of processors of the MPI world
         */
        Executor(int rank, int number_of_processors);

        virtual ~Executor();

        /**
         * This procedure is called on all executor subtypes to start them
         *
         * @param argc command line argument count
         * @param argv command line arguments
         */
        virtual void execute(int argc, char* argv[]) = 0;

        /**
         * Returns a executor instance depending on the rank and design
         *
         * @param rank of the process
         * @param number_of_processors of the MPI_COMM_WORLD communicator
         * @param design to be used
         * @param strategy to be used
         *
         * @return a executor object
         */
        static Executor *get_new_executor_by_rank(int rank, int number_of_processors, DesignEnum design,
                                                  StrategyEnum strategy);
private:
        /**
         * Returns a executor instance for master-worker design depending on rank and strategy
         *
         * @param rank of the process
         * @param number_of_processors of the MPI_COMM_WORLD communicator
         * @param strategy to be used
         *
         * @return a executor object
         */
        static Executor *get_new_executor_for_master_worker(int rank, int number_of_processors, StrategyEnum strategy);

        /**
         * Returns a executer instance for task-stealing design depending on rank and strategy.
         * This function splits the MPI world in to parts:
         *      - Color 0: Database server
         *      - Color 1: Task-stealing scheduler
         *
         * @param rank of the process
         * @param number_of_processors of the MPI_COMM_WORLD communicator
         * @param strategy to be used
         *
         * @return a executor object
         */
        static Executor *get_new_executor_for_taskstealing(int rank, int number_of_processors, StrategyEnum strategy);
};

#endif //_EXECUTER_H
