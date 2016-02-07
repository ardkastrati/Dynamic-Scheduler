/**
 * The SchedulingStrategy interface defines the functions that all implementations of a scheduling strategy must provide.
 * @author Fabio Broghammer
 * @version 1.0
 */


#ifndef _SCHEDULINGSTRATEGY_H
#define _SCHEDULINGSTRATEGY_H

#include "../TypesExtern.h"
#include <utility>


typedef std::pair<Task, long> TaskTimeType;

class SchedulingStrategy {
public:

    /**
     * Returns the next task depending on the scheduling strategy.
     *
     * @return the next task of the queue, or NULL if the queue is empty
     */
    virtual Task get_next_task() = 0;

    /**
     * Return the count of  tasks in the scheduling queue
     *
     * @retrun the count of tasks
     */
    virtual int get_task_count() = 0;

    /**
     * Returns the next task of the queue depending on the scheduling strategy and removes the task.
     * Effectively reducing its size by one.
     *
     * @return the next task of the queue, or NULL, if the queue is empty
     */
    virtual Task pop_next_task() = 0;

    /**
     * Insert a new task in the scheduling queue depending on the scheduling strategy and the estimated runtime
     * @param task
     * @param runtime
     */
    virtual void push_new_task(Task task, long runtime) = 0;

    /**
     * Changes the scheduling strategy. Returns the new schdeuling strategy with all tasks, or NULL if there was an error.
     *
     * Estimated runtime of tasks will get lost by changing from statistically based strategies (LSF, SJF) to non-statistically based strategies. The order of the old queue will be kept.
     *
     * All tasks will get a default rumtime value (defined in DEFAULT_RUNTIME) by changing from non-statistically based strategies (FIFO, LIFO) to statistically based strategies. The order of the old queue perhaps won't be kept
     * @param new_strategy
     */
    virtual SchedulingStrategy* change_strategy(SchedulingStrategy* new_strategy) = 0;

    /**
     * Returns true, if the current scheduling strategy statistic based.
     *
     * @return true, if the current scheduling strategy statistic based
     */
    virtual bool is_statistic_based() = 0;

    virtual ~SchedulingStrategy();

    /**
     * Default runtime of tasks in milli seconds
     */
    static const long DEFAULT_RUNTIME = 1;
};
inline SchedulingStrategy::~SchedulingStrategy(){};
#endif //_SCHEDULINGSTRATEGY_H
