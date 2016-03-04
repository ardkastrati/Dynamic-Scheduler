//
// Created by fabio on 04.03.16.
//
#include <iostream>
#include "MpiWinBinaryHeap.h"

using namespace std;

MpiWinBinaryHeap::MpiWinBinaryHeap(int max_size, int rank, int number_of_processors) :
    rank(rank),
    number_of_processors(number_of_processors)
{
    init(max_size);
}

MpiWinBinaryHeap::~MpiWinBinaryHeap()
{
    MPI_Win_free(&win_queue);
    MPI_Win_free(&win_n);

    MPI_Free_mem(queue);
    MPI_Free_mem(n);
}

void MpiWinBinaryHeap::init(int max_size)
{
    cout << "Binary heap" << endl;
    int queue_size = sizeof(Task) * max_size;
    MPI_Alloc_mem(queue_size, MPI_INFO_NULL, &queue);
    MPI_Alloc_mem(sizeof(int), MPI_INFO_NULL, &n);

    *n = -1;

    int disp_unit = sizeof(Task);

    MPI_Win_create(queue, queue_size, disp_unit, MPI_INFO_NULL, MY_MPI_COMM_TASKSTEALING, &win_queue);
    MPI_Win_create(n, sizeof(int), sizeof(int), MPI_INFO_NULL, MY_MPI_COMM_TASKSTEALING, &win_n);
}

Task MpiWinBinaryHeap::get_next_task()
{
    throw "Unsupported operation";
}

void MpiWinBinaryHeap::push_new_task(Task task, long runtime)
{
    static int i = 0;
    //cout << "Push: " << task.parameters[0] << endl;
    task.runtime = runtime;
    i++;
    int current_n;
    bool already_locked = true;
    while(already_locked) {
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_n);
        current_n = *n;
        *n = lock;
        MPI_Win_unlock(rank, win_n);
        if (current_n != lock) {
            already_locked = false;
        }
    }

    //now the n window ist locked by me
    current_n++;

    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_queue);

    queue[current_n] = task;
    sift_up(current_n);
    MPI_Win_unlock(rank, win_queue);

    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_n);
    *n = current_n;
    MPI_Win_unlock(rank, win_n);
    //cout << "Pushed" << endl;
}

void MpiWinBinaryHeap::sift_up(int i)
{
    //cout << "sift up " << i << endl;
    if (i == 0 || queue[i/2].runtime < queue[i].runtime) {
        return;
    }
    Task temp = queue[i];
    queue[i] = queue[i/2];
    queue[i/2] = temp;
    sift_up(i/2);
}

SchedulingStrategy* MpiWinBinaryHeap::change_strategy(SchedulingStrategy* new_strategy)
{
    throw "Not supported operation";
}

Task MpiWinBinaryHeap::steal_next_task(int target_rank, int number_of_tries)
{
    int current_n;
    int already_locked = true;
    int tries = 0;

    while(already_locked && (number_of_tries == 0 || tries < number_of_tries))
    {
        tries++;
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, target_rank, 0, win_n);
        MPI_Get(&current_n, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_n);
        MPI_Put(&lock, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_n);
        MPI_Win_unlock(target_rank, win_n);
        if (current_n != lock) {
            already_locked = false;
        }
    }

    Task task;

    if (already_locked) {
        task.parameter_size = -1;
        return task;
    }
    // now win_n is locked by me
    if (current_n < 0) {
        task.parameter_size = -2;
    } else {

        Task lastTask;
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_queue);
        MPI_Get(&task, 1, MY_MPI_TASK_TYPE, target_rank, 0, 1, MY_MPI_TASK_TYPE, win_queue);
        MPI_Get(&lastTask, 1, MY_MPI_TASK_TYPE, target_rank, current_n, 1, MY_MPI_TASK_TYPE, win_queue);
        MPI_Win_unlock(rank, win_queue);

        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_queue);
        MPI_Put(&lastTask, 1, MY_MPI_TASK_TYPE, target_rank, 0, 1, MY_MPI_TASK_TYPE, win_queue);
        MPI_Win_unlock(rank, win_queue);
        current_n--;
        sift_down(0, target_rank, current_n);
    }
    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, target_rank, 0, win_n);
    MPI_Put(&current_n, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_n);
    MPI_Win_unlock(target_rank, win_n);

    return task;
}

void MpiWinBinaryHeap::sift_down(int i, int target_rank, int current_n)
{
    if (2 * i <= current_n) {
        Task iTask;
        Task leftTask;
        Task rightTask;
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_queue);
        MPI_Get(&iTask, 1, MY_MPI_TASK_TYPE, target_rank, i, 1, MY_MPI_TASK_TYPE, win_queue);
        MPI_Get(&leftTask, 1, MY_MPI_TASK_TYPE, target_rank, 2 * i, 1, MY_MPI_TASK_TYPE, win_queue);
        MPI_Get(&leftTask, 1, MY_MPI_TASK_TYPE, target_rank, 2 * i + 1, 1, MY_MPI_TASK_TYPE, win_queue);
        MPI_Win_unlock(rank, win_queue);

        int m;
        Task mTask;
        if (2 * i + 1 > current_n || leftTask.runtime < rightTask.runtime) {
            m = 2*i;
            mTask = leftTask;
        } else {
            m = 2 * i + 1;
            mTask = rightTask;
        }
        if (iTask.runtime > mTask.runtime) {
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_queue);
            MPI_Put(&iTask, 1, MY_MPI_TASK_TYPE, target_rank, m, 1, MY_MPI_TASK_TYPE, win_queue);
            MPI_Put(&mTask, 1, MY_MPI_TASK_TYPE, target_rank, i, 1, MY_MPI_TASK_TYPE, win_queue);
            MPI_Win_unlock(rank, win_queue);
            sift_down(m, target_rank, current_n);
        }

    }
}

int MpiWinBinaryHeap::get_task_count(int target_rank) {

    int n;

    MPI_Win_lock(MPI_LOCK_SHARED, target_rank, 0, win_n);
    MPI_Get(&n, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_n);
    MPI_Win_unlock(target_rank, win_n);

    return n + 1;
}

int MpiWinBinaryHeap::get_task_count() {
    return get_task_count(rank);
}

bool MpiWinBinaryHeap::is_statistic_based()
{
    return true;
}

Task MpiWinBinaryHeap::pop_next_task() {
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