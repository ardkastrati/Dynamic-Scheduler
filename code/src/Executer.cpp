/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "Executer.h"
#include "scheduler/Master.h"
#include "worker/Worker.h"
#include "scheduler/FIFO.h"

/**
 * Executer implementation
 */




/**
 * Returns a executer instance depending on the 
 * @param rank
 * @param number_of_processors
 */
Executer* Executer::get_new_executer_by_rank(int rank, int number_of_processors, std::string design, std::string strategy)
{
    if (rank == 0) {
        return new Master(new FIFO());
    } else {
        return new Worker();
    }

}
