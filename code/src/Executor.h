/**
 * The Executor class is the base class for all objects that are mpi processes and have a one mpi rank.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */


#ifndef _EXECUTER_H
#define _EXECUTER_H

#include <string>

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
         * @param rank
         * @param number_of_processors
         *
         * @return a executor object
         */
        static Executor *get_new_executor_by_rank(int rank, int number_of_processors, std::string design,
                                                  std::string strategy);
};

#endif //_EXECUTER_H
