#ifndef _LJF_H
#define _LJF_H

#include "SchedulingStrategy.h"
#include <queue>
#include <vector>
/**
 * This class is a custom comparison class for the std::priority_queue. This class is used to order the priority queue.
 * This class is used from the LJF class.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */
class ComparisonClassLJF {
public:
    /**
     * Returns true, if the runtime of the task_time_1 is shorter than the runtime of the task_time_2.
     * This comparison function is used from the std::priority_queue to order the tasks.
     *
     * @param task_time_1 pair of task and runtime to be compared
     * @param task_time_2 pair of task and runtime to be compared
     *
     * @return true, if the runtime of the task1 is shorter than the runtime of the task2
     */
    bool operator()(TaskTimeType task_time_1, TaskTimeType task_time_2);
};

/**
 * This class implements the SchedulingStrategy interface and realises the Longest Job First (LJF) scheduling strategy.
 * Longest Job First scheduling uses the estimated runtime of tasks to order the task queue.
 * LJF is a statistically based scheduling strategy.
 * The LJF class uses the std::priority_queue priority queue to keep the tasks.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */
class LJF: public SchedulingStrategy {
private:
    /**
     * priority  queue  of TaskTypes. The priority queue   keeps the scientific tasks and orders them using the estimated runtime with Longest Job First  (LJF) strategy
     */
    std::priority_queue<TaskTimeType, std::vector<TaskTimeType>, ComparisonClassLJF>* queue;

public:
    /**
     * Constructs a new SJF scheduling strategy
     */
    LJF();

    /**
     * Deletes the priority_queue
     */
    ~LJF();

    /**
     * Returns the longest task depending on the scheduling strategy, or NULL if the queue is empty
     *
     * @return the longest task
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

#endif //_LJF_H
