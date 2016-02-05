/**
 * This class realize the last in-first out (LIFO) scheduling strategy.
 * The LIFO class uses the std::stack as fifo queue.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#ifndef _LIFO_H
#define _LIFO_H

#include "SchedulingStrategy.h"
#include <stack>


class LIFO: public SchedulingStrategy {
private:
    /**
     * Last In - First Out (LIFO) stack of TaskTypes. The stack keeps the scientific tasks
     */
    std::stack<Task>* stack;

public:
    /**
     * Constructs a new LIFO scheduling queue
     */
    LIFO();

    /**
     * Destructs a new LIFO scheduling queue
     */
    ~LIFO();

    /**
     * Returns the last-in task, or NULL if the queue is empty
     *
     * @return the last-in task
     */
    Task get_next_task();

    /**
     * Return the count of  tasks in the scheduling queue
     *
     * @retrun the count of tasks
     */
    int get_task_count();

    /**
     * Removes the next task in the queue, effectively reducing its size by one.
     */
    Task pop_next_task();

    /**
     * Insert a new task in the scheduling queue depending on the scheduling strategy and the estimated runtime
     * @param task
     * @param runtime
     */
    void push_new_task(Task task, long runtime);

    /**
     * Changes the scheduling strategy. Returns the new schdeuling strategy with all tasks, or NULL if there was an error.
     *
     * Estimated runtime of tasks will get lost by changing from statistically based strategies (LSF, SJF) to non-statistically based strategies. The order of the old queue will be kept.
     *
     * All tasks will get a default rumtime value (defined in DEFAULT_RUNTIME) by changing from non-statistically based strategies (FIFO, LIFO) to statistically based strategies. The order of the old queue perhaps won't be kept
     * @param new_strategy
     */
    SchedulingStrategy* change_strategy(SchedulingStrategy* new_strategy);

    bool is_statistic_based();
};

#endif //_LIFO_H
