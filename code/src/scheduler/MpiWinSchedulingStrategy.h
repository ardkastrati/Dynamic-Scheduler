/**
 * The MpiWinSchedulingStrategy interface is a specialization of the SchedulingStrategy interface. The MpiWinSchedulingStrategy interface
 * adds function for remote scheduling queue access. Implementations must provide the steal_next_task() and the get_task_count function
 * on remote scheduling queues by given rank.
 * The tasks must be kept in a MPI window to support remote memory access.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#ifndef _MPIWINSCHEDULINGSTRATEGY_H
#define _MPIWINSCHEDULINGSTRATEGY_H


#include "SchedulingStrategy.h"

class MpiWinSchedulingStrategy : public SchedulingStrategy {

    public:
        /**
         * Steals the next task from the given rank if the queue of the given rank is not empty
         *
         * @param rank the rank of the remote queue
         *
         * @return the next task from the given rank or NULL if the queue is empty
         */
        virtual Task steal_next_task(int rank, int number_of_tries) = 0;

        /**
         * Returns the task count of the remote queue of the given rank
         *
         * @param rank the rank of the remote queue
         *
         * @return the task count of the remote queue
         */
        virtual int get_task_count(int rank) = 0;

};


#endif //_MPIWINSCHEDULINGSTRATEGY_H
