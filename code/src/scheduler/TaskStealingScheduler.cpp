#include "../../lib/easylogging++.h"
#include "TaskStealingScheduler.h"
#include "MpiWinLIFO.h"
#include "../ScientificCode.h"
#include "../worker/TaskStealingWorker.h"
#include "../Const.h"

#define WORKING 1
#define IDLE 0

TaskStealingScheduler::TaskStealingScheduler(MpiWinSchedulingStrategy* scheduling_strategy, DataMining* data_miner, int rank, int number_of_processors) :
    AbstractScheduler(scheduling_strategy , data_miner, rank, number_of_processors)
{

    MPI_Alloc_mem(sizeof(int), MPI_INFO_NULL, &status);
    *status = WORKING;
    MPI_Win_create(status, sizeof(int), sizeof(int), MPI_INFO_NULL, MY_MPI_COMM_TASKSTEALING, &win_status);
    worker = new TaskStealingWorker(this);

}

TaskStealingScheduler::~TaskStealingScheduler()
{
    LOG(INFO) << "Destructor TaskStealingScheduler";
    MPI_Win_free(&win_status);
    MPI_Free_mem(status);
    delete worker;
}
void TaskStealingScheduler::execute(int argc, char* argv[])
{
    LOG(INFO) << "Ich bin ein TaskStealingScheduler";
    if (rank == 0)
    {
        //TODO: Change 100 to dynamic one
        Task tasks[100];
        int number_of_tasks;

        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
        *status = WORKING;
        MPI_Win_unlock(rank, win_status);

        code_preprocessing_master(argc, argv, tasks, &number_of_tasks);
        for (int i = 0; i < number_of_tasks; i++) {
            scheduling_strategy->push_new_task(tasks[i], 0);
        }

        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
        *status = IDLE;
        MPI_Win_unlock(rank, win_status);
    }
    else
    {
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
        *status = WORKING;
        MPI_Win_unlock(rank, win_status);

        worker->preprocessing(argc, argv);

        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
        *status = IDLE;
        MPI_Win_unlock(rank, win_status);

    }
    run();
    if (rank == 0) {
        postprocessing();
        short temp;
        MPI_Send(&temp, DATABASE, MPI_SHORT, DATABASE, STOP, MPI_COMM_WORLD);
    } else {
        worker->postprocessing();
    }

}

void TaskStealingScheduler::run() {

    bool is_running = true;
    while (is_running) {

        Task task = scheduling_strategy->pop_next_task();

        if (task.parameter_size > 0) {

            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
            *status = WORKING;
            MPI_Win_unlock(rank, win_status);

            worker->run_task(task);

            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
            *status = IDLE;
            MPI_Win_unlock(rank, win_status);
        } else
        {
            is_running = !is_finish();
        }

    }
}

bool TaskStealingScheduler::is_finish() {
    bool is_finish = true;
    //TODO: change vor datacore
    for (int target_rank = 0; target_rank < number_of_processors && is_finish; target_rank++) {

        int status;
        MPI_Win_lock(MPI_LOCK_SHARED, target_rank, 0, win_status);
        MPI_Get(&status, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_status);
        MPI_Win_unlock(target_rank, win_status);
        if (status == WORKING) {
            is_finish = false;
        }
    }
    return is_finish;
}
