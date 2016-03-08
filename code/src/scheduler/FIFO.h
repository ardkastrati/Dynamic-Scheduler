/**
 * This class realize the first in-first out (FIFO) scheduling strategy.
 * The FIFO class uses the std::queue as fifo queue.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */


#ifndef _FIFO_H
#define _FIFO_H

#include "SchedulingStrategy.h"
#include <queue>

class FIFO: public SchedulingStrategy {
private:
    /**
     * First In - First Out (FIFO) queue of TaskTypes. The queue stores  the scientific tasks.
     */
    std::queue<Task>* queue;

public:
    /**
     * Creates a new FIFO scheduling queue.
     */
    FIFO();

    /**
     * Destructs the FIFO scheduling queue.
     */
    ~FIFO();

    /**
     * Returns the first task to be executed, or NULL if the queue is empty.
     *
     * @return the first-in task
     */
    Task get_next_task();

    /**
     * Returns the number of  tasks in the scheduling queue.
     *
     * @return the number of tasks
     */
    int get_task_count();

    /**
     * Removes the next task in the queue, effectively reducing its size by one.
     */
    Task pop_next_task();

    /**
     * Inserts a new task in the scheduling queue depending on the scheduling strategy and the estimated runtime.
     * @param task
     * @param runtime
     */
    void push_new_task(Task task, long runtime);

    /**
     * Changes the scheduling strategy. Returns the new schdeuling strategy with all tasks, or NULL if there was an error.
     *
     * Estimated runtime of tasks will get lost by changing from statistically based strategies (LSF, SJF) to non-statistically based strategies. The order of the old queue will be kept.
     *
     * All tasks will get a default rumtime value (defined in DEFAULT_RUNTIME) when changing from non-statistically based strategies (FIFO, LIFO) to statistically based strategies. The order of the old queue might get changed.
     * @param new_strategy
     */
    SchedulingStrategy* change_strategy(SchedulingStrategy* new_strategy);

    bool is_statistic_based();
};

#endif //_FIFO_H
