#include "WorkerExecutor.h"
#include <mpi.h>
#include "../ScientificCode.h"
#include "../Const.h"
#include "../../lib/easylogging++.h"

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
    code_run_task(task, &place_task_forwarder, this);
    MPI_Send(&task, 1, MY_MPI_TASK_TYPE, MASTER, FINISH, MPI_COMM_WORLD);
}

void WorkerExecutor::place_task(Task task)
{
    LOG(INFO) << "place_task: " << task.parameters[0];
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

