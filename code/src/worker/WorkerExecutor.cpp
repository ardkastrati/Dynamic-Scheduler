#include "WorkerExecutor.h"
#include <mpi.h>
#include <cstring>
#include "../ScientificCode.h"
#include "../Const.h"
#include "../../lib/easylogging++.h"
#include "../util/TimeUtility.h"


WorkerExecutor::WorkerExecutor(int rank, int number_of_processors) : Executor(rank, number_of_processors) {}

void WorkerExecutor::execute(int argc, char* argv[])
{
    preprocessing(argc, argv);
    wait_for_task();
    postprocessing();
}

void WorkerExecutor::preprocessing(int argc, char* argv[])
{
    code_preprocessing_slave(argc, argv);

    Task task;
    MPI_Send(&task, 1, MY_MPI_TASK_TYPE, MASTER, FINISH, MPI_COMM_WORLD);
}

void WorkerExecutor::postprocessing()
{
    code_postprocessing_slave();
}

void WorkerExecutor::run_task(Task task)
{
    long time_begin;
    long time_end;

    time_begin = get_time_in_mirco();
    code_run_task(task, &place_task_forwarder_master, this);
    time_end = get_time_in_mirco();

    LOG(INFO) << "task: " << task.parameters[0] << " took " << time_end - time_begin << " mircoseconds";

    TaskData task_data;
    task_data.time_intercommunication_end = -1;
    task_data.time_intercommunication_start = -1;
    task_data.rank = rank;
    task_data.time_appeared = task.time_appeared;
    task_data.time_started = time_begin;
    task_data.time_ended = time_end;
    task_data.parent  = task.parent;
    task_data.event = 1; //TODO: Right event
    task_data.mode = 1; //TODO: Right mode
    task_data.parameter_size = task.parameter_size;
    memcpy(task_data.parameters, task.parameters, sizeof(double) * task.parameter_size);


    //TODO: Send task data to database


    MPI_Send(&task, 1, MY_MPI_TASK_TYPE, MASTER, FINISH, MPI_COMM_WORLD);
}

void WorkerExecutor::place_task(Task task)
{
    LOG(INFO) << "place_task: " << task.parameters[0];
    task.time_appeared = get_time_in_mirco();
    MPI_Send(&task, 1, MY_MPI_TASK_TYPE, MASTER, REQUEST, MPI_COMM_WORLD);
}

void WorkerExecutor::wait_for_task()
{
    Task task;
    MPI_Status status;

    bool isRunning = true;

    while(isRunning){
        MPI_Recv(&task, 1, MY_MPI_TASK_TYPE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == STOP) {
            isRunning = false;
        } else if (status.MPI_TAG == START) {
            run_task(task);
        }
    }
}

