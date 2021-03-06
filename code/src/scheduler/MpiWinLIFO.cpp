#define NDEBUG

#include <stddef.h>
#include <iostream>
#include "MpiWinLIFO.h"
#include "../Const.h"

#define ASSERT 0

using namespace std;


MpiWinLIFO::MpiWinLIFO(int max_size, int rank, int number_of_processors) :
    rank(rank),
    number_of_processors(number_of_processors)
{
    init(max_size);
}

MpiWinLIFO::~MpiWinLIFO()
{
    MPI_Win_free(&win_queue);
    MPI_Win_free(&win_offset);
    //MPI_Win_free(&win_size);

    MPI_Free_mem(queue);
    //MPI_Free_mem(size);
    MPI_Free_mem(offset);
}

void MpiWinLIFO::init(int max_size)
{
    //cout << "init" << endl;
    int queue_size = sizeof(Task) * max_size;

    MPI_Alloc_mem(queue_size, MPI_INFO_NULL, &queue);
    MPI_Alloc_mem(sizeof(int), MPI_INFO_NULL, &offset);

    *offset = 0;

    int disp_unit = sizeof(Task);

    MPI_Win_create(queue, queue_size, disp_unit, MPI_INFO_NULL, MY_MPI_COMM_TASKSTEALING, &win_queue);
    MPI_Win_create(offset, sizeof(int), sizeof(int), MPI_INFO_NULL, MY_MPI_COMM_TASKSTEALING, &win_offset);

}
Task MpiWinLIFO::get_next_task() {
    throw "Unsupported operation";
}

int MpiWinLIFO::get_task_count() {
    return get_task_count(rank);
}


Task MpiWinLIFO::pop_next_task() {
    Task task;
    bool task_found = false;
    for (int i = 0; i < number_of_processors && !task_found; i++) {
        int target_rank = (rank + i) % number_of_processors;
        task = steal_next_task(target_rank, 0);
        if (task.parameter_size > 0) {
            task_found = true;
        }
    }

    return task;
}


void MpiWinLIFO::push_new_task(Task task, long runtime)
{
    //cout << "insert: " << task.parameters[0] << endl;
    int current_offset;
    bool already_locked = true;
    while(already_locked) {
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_offset);
        current_offset = offset[0];
        *offset = lock;
        MPI_Win_unlock(rank, win_offset);
        if (current_offset != lock) {
            already_locked = false;
        }
    }

    //now the offset is locked by me

    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_queue);

    queue[current_offset] = task;

    MPI_Win_unlock(rank, win_queue);

    current_offset++;
    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_offset);
    *offset = current_offset;
    MPI_Win_unlock(rank, win_offset);

}


Task MpiWinLIFO::steal_next_task(int target_rank, int number_of_tries) {
    //cout << "try to steal task from: " <<target_rank << endl;
    int current_offset;
    bool already_locked = true;
    int tries = 0;
    while (already_locked && (number_of_tries == 0 || tries < number_of_tries))
    {
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, target_rank, 0, win_offset);
        MPI_Get(&current_offset, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_offset);
        MPI_Put(&lock, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_offset);
        MPI_Win_unlock(target_rank, win_offset);
        tries++;
        if (current_offset != lock) {
            already_locked = false;
        }
    }
    Task task;
    if (already_locked) {
        task.parameter_size = -1;
        return task;
    }
    //now the offset is locked by me

    if (current_offset <= 0)
    {
        task.parameter_size = -2;
    }
    else
    {
        current_offset--;

        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, target_rank, 0, win_queue);
        MPI_Get(&task, 1, MY_MPI_TASK_TYPE, target_rank, current_offset, 1, MY_MPI_TASK_TYPE, win_queue);
        MPI_Win_unlock(target_rank, win_queue);
    }

    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, target_rank, 0, win_offset);
    MPI_Put(&current_offset, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_offset);
    MPI_Win_unlock(target_rank, win_offset);

    return task;
}

int MpiWinLIFO::get_task_count(int target_rank) {

    int offset;

    MPI_Win_lock(MPI_LOCK_SHARED, target_rank, 0, win_offset);
    MPI_Get(&offset, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_offset);
    MPI_Win_unlock(target_rank, win_offset);

    return offset;
}

bool MpiWinLIFO::is_statistic_based()
{
    return false;
}

SchedulingStrategy* MpiWinLIFO::change_strategy(SchedulingStrategy *new_strategy) {
    throw "Unsupported operation";
}
