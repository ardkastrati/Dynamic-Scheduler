/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _FIFO_H
#define _FIFO_H

#include "SchedulingStrategy.h"
#include <queue>

class FIFO: public SchedulingStrategy {
private: 
    /**
     * First In - First Out (FIFO) queue of TaskTypes. The queue keeps the scientific tasks
     */
    std::queue<TaskType>* queue;

public:
    /**
     * Constructs a new FIFO scheduling queue
     */
    FIFO();

    /**
     * Destructs a new FIFO scheduling queue
     */
    ~FIFO();

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

#endif //_FIFO_H
