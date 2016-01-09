/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "Executer.h"
#include "scheduler/Master.h"
#include "worker/Worker.h"
#include "scheduler/LJF.h"

/**
 * Executer implementation
 */


Executer::Executer(int rank, int number_of_processors){
    this->rank = rank;
    this->number_of_processors = number_of_processors;
}

/**
 * Returns a executer instance depending on the 
 * @param rank
 * @param number_of_processors
 */
Executer* Executer::get_new_executer_by_rank(int rank, int number_of_processors, std::string design, std::string strategy)
{
    if (rank == 0) {
        return new Master(new LJF(), rank, number_of_processors);
    } else {
        return new Worker(rank, number_of_processors);
    }

}
