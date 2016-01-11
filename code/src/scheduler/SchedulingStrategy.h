/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _SCHEDULINGSTRATEGY_H
#define _SCHEDULINGSTRATEGY_H

#include "../Types.h"
#include <utility>


typedef std::pair<TaskType, long> TaskTimeType;

class SchedulingStrategy {
public: 
    
    /**
     * Returns the next task depending on the scheduling strategy, or NULL if the queue is empty
     */
    virtual TaskType get_next_task();
    
    /**
     * Return the count of  tasks in the scheduling queue
     */
    virtual int get_task_count();
    
    /**
     * Removes the next task in the queue, effectively reducing its size by one.
     */
    virtual void pop_next_task();
    
    /**
     * Insert a new task in the scheduling queue depending on the scheduling strategy and the estimated runtime
     * @param task
     * @param runtime
     */
    virtual void push_new_task(TaskType task, long runtime);
    
    /**
     * Changes the scheduling strategy. Returns the new schdeuling strategy with all tasks, or NULL if there was an error.
     * 
     * Estimated runtime of tasks will get lost by changing from statistically based strategies (LSF, SJF) to non-statistically based strategies. The order of the old queue will be kept.
     * 
     * All tasks will get a default rumtime value (defined in DEFAULT_RUNTIME) by changing from non-statistically based strategies (FIFO, LIFO) to statistically based strategies. The order of the old queue perhaps won't be kept
     * @param new_strategy
     */
    virtual SchedulingStrategy* change_strategy(SchedulingStrategy* new_strategy);

    /**
     * Default runtime of tasks
     */
    static const long DEFAULT_RUNTIME = 1;
};

#endif //_SCHEDULINGSTRATEGY_H
