/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _SJF_H
#define _SJF_H

#include "SchedulingStrategy.h"
#include <queue>

class SJF: public SchedulingStrategy {
private: 
    /**
     * priority  queue  of TaskTypes. The priority queue   keeps the scientific tasks and orders them using the estimated runtime with Shortest Job First  (SJF) strategy
     */
    std::priority_queue<TaskTimeType>* queue;

public:
    /**
     * Constructs a new SJF scheduling queue
     */
    SJF();

    /**
     * Destructs a new SJF scheduling queue
     */
    ~SJF();

    /**
     * Returns the next task depending on the scheduling strategy, or NULL if the queue is empty
     */
    TaskType get_next_task();

    /**
     * Return the count of  tasks in the scheduling queue
     */
    int get_task_count();

    /**
     * Removes the next task in the queue, effectively reducing its size by one.
     */
    void pop_next_task();

    /**
     * Insert a new task in the scheduling queue depending on the scheduling strategy and the estimated runtime
     * @param task
     * @param runtime
     */
    void push_new_task(TaskType task, long runtime);

    /**
     * Changes the scheduling strategy. Returns the new schdeuling strategy with all tasks, or NULL if there was an error.
     *
     * Estimated runtime of tasks will get lost by changing from statistically based strategies (LSF, SJF) to non-statistically based strategies. The order of the old queue will be kept.
     *
     * All tasks will get a default rumtime value (defined in DEFAULT_RUNTIME) by changing from non-statistically based strategies (FIFO, LIFO) to statistically based strategies. The order of the old queue perhaps won't be kept
     * @param new_strategy
     */
    SchedulingStrategy* change_strategy(SchedulingStrategy* new_strategy);
};

#endif //_SJF_H
