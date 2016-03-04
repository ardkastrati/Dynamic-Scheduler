#ifndef CODE_MPIWINFIFO_H
#define CODE_MPIWINFIFO_H

#include "MpiWinSchedulingStrategy.h"

/**
 * This class implements the MpiWinSchedulingStrategy and realize a FIFO queue.
 * The FIFO queue is represented as cyclic array. (See https://crypto.iti.kit.edu/fileadmin/User/Lectures/Algorithmen_SS15/folien_20150427.pdf page 125)
 * The queue itself and the offset are inside several MPI window to give other processes access to the data.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */
class MpiWinFIFO : public MpiWinSchedulingStrategy {

private:
    static const int HEAD = 0;
    static const int TAIL = 1;

    MPI_Win win_queue;
    MPI_Win win_offset;
    int* offset;

    /**
     * size[0] is head
     * size[1] is tail
     */
    int size;
    Task* queue;

    const int lock[2] = {-1, -1};

    int rank;
    int number_of_processors;
    void init(int max_size);
public:
    /**
     * Constructs a new LIFO scheduling queue
     *
     * @param size of the queue
     * @param rank from the process inside the MY_MPI_COMM_TASKSTEALING communicator
     * @param number_of_processors inside the MY_MPI_COMM_TASKSTEALING communicator
     */
    MpiWinFIFO(int size, int rank, int number_of_processors);

    /**
     * Destructs a new LIFO scheduling queue
     */
    ~MpiWinFIFO();

    /**
     * Returns the last-in task, or NULL if the queue is empty
     *
     * @return the last-in task
     */
    Task get_next_task();

    /**
     * Return the count of  tasks in the scheduling queue
     *
     * @return the count of tasks
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
     * Changes the scheduling strategy. Returns the new scheduling strategy with all tasks, or NULL if there was an error.
     *
     * Estimated runtime of tasks will get lost by changing from statistically based strategies (LSF, SJF) to non-statistically based strategies. The order of the old queue will be kept.
     *
     * All tasks will get a default runtime value (defined in DEFAULT_RUNTIME) by changing from non-statistically based strategies (FIFO, LIFO) to statistically based strategies. The order of the old queue perhaps won't be kept
     * @param new_strategy
     */
    SchedulingStrategy* change_strategy(SchedulingStrategy* new_strategy);

    /**
     * Steals the next task from the given rank if the queue of the given rank is not empty
     *
     * @param rank the rank of the remote queue
     *
     * @return the next task from the given rank or NULL if the queue is empty
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


#endif //CODE_MPIWINFIFO_H
