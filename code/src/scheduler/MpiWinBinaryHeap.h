/**
 * This class is a binary heap, using a MPI shared memory area (MPI Window) to store data.
 * The algorithm details can be found here http://crypto.iti.kit.edu/fileadmin/User/Lectures/Algorithmen_SS15/folien_20150520.pdf
 * and here: http://crypto.iti.kit.edu/fileadmin/User/Lectures/Algorithmen_SS15/folien_20150518.pdf.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#ifndef CODE_MPIWINBINARYHEAP_H
#define CODE_MPIWINBINARYHEAP_H

#include "MpiWinSchedulingStrategy.h"

class MpiWinBinaryHeap : public MpiWinSchedulingStrategy {

private:
    bool is_min_heap;
    /**
     * The MPI window for the queue.
     */
    MPI_Win win_queue;
    /**
     * The MPI window for the current last element.
     */
    MPI_Win win_n;
    /**
     * The current last element.
     */
    int *n;
    /**
     * The task queue.
     */
    Task *queue;

    /**
     * The rank of this process. Relative to the task stealing communicator.
     */
    int rank;
    /**
     * The number of processes in the task stealing communicator.
     */
    int number_of_processors;
    /**
     * A constant, representing a lock for the win_n window.
     */
    const int lock = -100;

    /**
     * Creates the n, queue and the MPI windows.
     */
    void init(int max_size);

    /**
     *  Maximum size of the heap
     */
     int max_size;

    /**
     * Used to reestablish the heap invariant, after a new task was inserted.
     *
     * @param i the current level in the heap
     */
    void sift_up(int i);
    /**
     * Used to reestablish the heap invariant, after the first task was poped.
     *
     * @param i the current level in the heap
     * @param target_rank rank of the target. Relative to the task stealing communicator
     * @param current_n current last element in the heap
     */
    void sift_down(int i, int target_rank, int current_n);
    /**
     * Compare the given runtimes depending on the is_min_heap flog
     * If is_min_heap == TRUE the comparator will return (runtime1 < rumtime2).
     * If is_min_heap == FALSE the comparator will return (runtime1 > runtime2).
     * @param runtime1 first runtime to be compared
     * @param runtime2 second runtime to be compared
     * @return (runtime1 < runtime2), if is_min_heap == TRUE, else (runtime1 > runtime2)
     */
    bool comparator(long runtime1, long runtime2);
public:
    /**
 * Creates a new binary heap scheduling queue.
 *
 * @param size of the queue
 * @param rank from the process inside the MY_MPI_COMM_TASKSTEALING communicator
 * @param number_of_processors inside the MY_MPI_COMM_TASKSTEALING communicator
 */
    MpiWinBinaryHeap(int size, int rank, int number_of_processors, bool isMinHeap);

    /**
     * Destructs the binary heap scheduling queue.
     */
    ~MpiWinBinaryHeap();

    /**
     * Returns the first task, or NULL if the queue is empty
     *
     * @return the last-in task
     */
    Task get_next_task();

    /**
     * Returns the number of  tasks in the scheduling queue
     *
     * @return the count of tasks
     */
    int get_task_count();

    /**
     * Removes the next task in the queue, effectively reducing its size by one.
     */
    Task pop_next_task();

    /**
     * Inserts a new task in the scheduling queue depending on the scheduling strategy and the estimated runtime
     * @param task
     * @param runtime
     */
    void push_new_task(Task task, long runtime);

    /**
     * Changes the scheduling strategy. Returns the new scheduling strategy with all tasks, or NULL if there was an error.
     *
     * Estimated runtime of tasks will get lost by changing from statistically based strategies (LSF, SJF) to non-statistically based strategies. The order of the old queue will not change.
     *
     * All tasks will get a default runtime value (defined in DEFAULT_RUNTIME) by changing from non-statistically based strategies (FIFO, LIFO) to statistically based strategies. The order of the old queue might change.
     * @param new_strategy
     */
    SchedulingStrategy* change_strategy(SchedulingStrategy* new_strategy);

    /**
     * Steals the next task from the given rank in case the queue of the given rank is not empty.
     * Will return task.parameter_size == -1 if the win_offset window could not be locked.
     * Will return task.parameter_size == -2 if the queue is empty.
     *
     * @param rank the rank of the remote queue
     *
     * @return the next task from the given rank or NULL in case the queue is empty
     */
    Task steal_next_task(int target_rank, int number_of_tries);

    /**
     * Returns the task count of the remote queue of the given rank
     *
     * @param rank the rank of the remote queue
     *
     * @return the task count of the remote queue
     */
    int get_task_count(int target_rank);

    bool is_statistic_based();


};


#endif //CODE_MPIWINBINARYHEAP_H
