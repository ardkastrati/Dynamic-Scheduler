#define NDEBUG

//#include "../../lib/easylogging++.h"
#include "TaskStealingScheduler.h"
#include "MpiWinLIFO.h"
#include "../ScientificCode.h"
#include "../worker/TaskStealingWorker.h"
#include "../Const.h"
#include <iostream>

using namespace std;

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
    //LOG(DEBUG) << "Destructor TaskStealingScheduler";
    MPI_Win_free(&win_status);
    MPI_Free_mem(status);
    delete worker;
}
void TaskStealingScheduler::execute(int argc, char* argv[])
{
    if (rank == 0)
    {
        Task tasks[MAX_INIT_TASK_COUNT];
        int number_of_tasks;

        /*MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
        *status = WORKING;
        MPI_Win_unlock(rank, win_status);
        */
        code_preprocessing_master(argc, argv, tasks, &number_of_tasks);
        for (int i = 0; i < number_of_tasks; i++) {
            scheduling_strategy->push_new_task(tasks[i], (long) tasks[i].parameters[0]);
            //place_task(tasks[i]);
        }
        /*MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
        *status = IDLE;
        MPI_Win_unlock(rank, win_status);*/
    }
    else
    {

        /*MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
        *status = WORKING;
        MPI_Win_unlock(rank, win_status);*/

        worker->preprocessing(argc, argv);

        /*MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
        *status = IDLE;
        MPI_Win_unlock(rank, win_status);*/

    }
    run();
    cout << "+++++++++++++++++++Finished" << endl;
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
    int number_of_tries = 10;
    while (is_running) {
        //std::cout << "Run loop" << std::endl;
        /*MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
        *status = WORKING;
        MPI_Win_unlock(rank, win_status);*/

        Task task = scheduling_strategy->pop_next_task();

        if (task.parameter_size > 0) {

            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
            *status = WORKING;
            MPI_Win_unlock(rank, win_status);
            number_of_tries = 10;
            //cout << task.parameters[0] << endl;
            worker->run_task(task);

            /*MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
            *status = IDLE;
            MPI_Win_unlock(rank, win_status);*/


        } else
        {
            number_of_tries--;
            if (number_of_tries > 0) {
              continue;
            }
            if (rank == 0 ){
              if (is_finish()) {
                MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
                *status = IDLE;
                MPI_Win_unlock(rank, win_status);
                is_running = false;
              }
            } else {
                int temp_status;
                MPI_Win_lock(MPI_LOCK_EXCLUSIVE, MASTER, 0, win_status);
                MPI_Get(&temp_status, 1, MPI_INT, MASTER, 0, 1, MPI_INT, win_status);
                MPI_Win_unlock(MASTER, win_status);
                if (temp_status == IDLE) {
                  is_running = false;
                }
                MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win_status);
                *status = IDLE;
                MPI_Win_unlock(rank, win_status);

            }
            //is_running = !is_finish();
        }


    }
}

bool TaskStealingScheduler::is_finish() {
    bool is_finish = true;
    for (int target_rank = 1; target_rank < number_of_processors && is_finish; target_rank++) {

        int status;
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, target_rank, 0, win_status);
        MPI_Get(&status, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_status);
        MPI_Win_unlock(target_rank, win_status);
        //cout << "status: " << status << endl;
        if (status == WORKING) {
            is_finish = false;
        }
    }
    return is_finish;
}
