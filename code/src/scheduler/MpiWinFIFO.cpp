#define NDEBUG

#include "MpiWinFIFO.h"
#include "../../lib/easylogging++.h"

MpiWinFIFO::MpiWinFIFO(int size, int rank, int number_of_processors) :
    rank(rank),
    number_of_processors(number_of_processors),
    size(size)
{
    init(size);
}

MpiWinFIFO::~MpiWinFIFO()
{
    MPI_Win_free(&win_offset);
    MPI_Win_free(&win_queue);

    MPI_Free_mem(queue);
    MPI_Free_mem(offset);
}

void MpiWinFIFO::init(int max_size)
{
    int queue_size = sizeof(Task) * max_size;

    MPI_Alloc_mem(queue_size, MPI_INFO_NULL, &queue);
    MPI_Alloc_mem(sizeof(int) * 2, MPI_INFO_NULL, &offset);

    offset[HEAD] = 0;
    offset[TAIL] = 0;

    int disp_unit = sizeof(Task);

    MPI_Win_create(queue, queue_size, disp_unit, MPI_INFO_NULL, MY_MPI_COMM_TASKSTEALING, &win_queue);
    MPI_Win_create(offset, sizeof(int) * 2, sizeof(int), MPI_INFO_NULL, MY_MPI_COMM_TASKSTEALING, &win_offset);
}

Task MpiWinFIFO::get_next_task()
{
    throw "Not implemented yet";
}

Task MpiWinFIFO::pop_next_task() {
    Task task;
    bool task_found = false;
    //TODO: hard coded DATABASE
    for (int i = 0; i < number_of_processors && !task_found; i++) {
        int target_rank = (rank + i) % number_of_processors;
        task = steal_next_task(target_rank, 0);
        if (task.parameter_size > 0) {
            task_found = true;
        }
    }
    return task;
}

void MpiWinFIFO::push_new_task(Task task, long runtime)
{

    LOG(INFO) << "push: " << task.parameters[0];

    int current_offset[2];

    bool already_locked = true;
    while(already_locked) {
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_offset);
        current_offset[HEAD] = offset[HEAD];
        current_offset[TAIL] = offset[TAIL];
        offset[HEAD] = lock;
        MPI_Win_unlock(rank, win_offset);
        if (current_offset[HEAD] != lock) {
            already_locked = false;
        }
    }

    //now the offset is locked by me

    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_queue);

    queue[current_offset[TAIL]] = task;

    MPI_Win_unlock(rank, win_queue);

    current_offset[TAIL] = (current_offset[TAIL] + 1) % size;

    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_offset);
    offset[HEAD] = current_offset[HEAD];
    offset[TAIL] = current_offset[TAIL];
    MPI_Win_unlock(rank, win_offset);


}

SchedulingStrategy* MpiWinFIFO::change_strategy(SchedulingStrategy* new_strategy)
{
    throw "Not supported operation";
}
int MpiWinFIFO::get_task_count()
{
    return get_task_count(rank);
}

int MpiWinFIFO::get_task_count(int target_rank) {

    int offset[2];

    MPI_Win_lock(MPI_LOCK_SHARED, target_rank, 0, win_offset);
    MPI_Get(&offset, 2, MPI_INT, target_rank, 0, 2, MPI_INT, win_offset);
    MPI_Win_unlock(target_rank, win_offset);

    return (offset[TAIL] - offset[HEAD] + size) % size;
}

bool MpiWinFIFO::is_statistic_based()
{
    return false;
}

Task MpiWinFIFO::steal_next_task(int target_rank, int number_of_tries) {
    //LOG(INFO) << "try to steal task from: " <<target_rank;
    int current_offset[2];
    bool already_locked = true;
    int tries = 0;
    //TODO:Documentation for number_of_tries parameter
    while (already_locked && (number_of_tries == 0 || tries < number_of_tries))
    {
        tries++;
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, target_rank, 0, win_offset);
        MPI_Get(&current_offset, 2, MPI_INT, target_rank, 0, 2, MPI_INT, win_offset);
        MPI_Put(&lock, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_offset);
        MPI_Win_unlock(target_rank, win_offset);
        if (current_offset[HEAD] != lock) {
            already_locked = false;
        }
    }
    Task task;
    //TODO: Documentation of return values
    if (already_locked) {
        task.parameter_size = -1;
        return task;
    }
    //now the offset is locked by me

    //TODO: Documentation of return values
    if (current_offset <= 0)
    {
        task.parameter_size = -2;
    }
    else
    {

        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, target_rank, 0, win_queue);
        MPI_Get(&task, 1, MY_MPI_TASK_TYPE, target_rank, current_offset[0], 1, MY_MPI_TASK_TYPE, win_queue);
        MPI_Win_unlock(target_rank, win_queue);
        current_offset[HEAD] = (current_offset[HEAD] + 1) % size;
    }
    //LOG(INFO) << current_offset;

    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, target_rank, 0, win_offset);
    MPI_Put(&current_offset, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_offset);
    MPI_Win_unlock(target_rank, win_offset);

    return task;
}