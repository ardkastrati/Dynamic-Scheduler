/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include <mpi.h>
#include "Worker.h"
#include "../ScientificCode.h"
#include "../Const.h"
/**
 * Worker implementation
 */

Worker::Worker(int rank, int number_of_processors) : AbstractWorker(rank, number_of_processors)
{

}

void Worker::preporcessing(int argc, char* argv[])
{
    code_preprocessing_slave(argc, argv);
    TaskType task;
    MPI_Send(&task, 1, MPI_INT, MASTER, FINISH, MPI_COMM_WORLD);
}

void Worker::postprocessing()
{
    code_postprocessing_slave();
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
}

void Worker::run_task(TaskType task)
{
    code_run_task(task);
}

void Worker::wait_for_task() {
    TaskType task;
    MPI_Status status;

    while(true){
        MPI_Recv(&task, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == STOP) {
            return;
        } else if (status.MPI_TAG == START) {
            run_task(task);
            MPI_Send(&task, 1, MPI_INT, MASTER, FINISH, MPI_COMM_WORLD);
        }
    }


}

void Worker::place_task(TaskType task)
{
    MPI_Send(&task, 1, MPI_INT, MASTER, REQUEST, MPI_COMM_WORLD);
}

void Worker::execute(int argc, char* argv[])
{
    preporcessing(argc, argv);
    wait_for_task();
    postprocessing();
}
