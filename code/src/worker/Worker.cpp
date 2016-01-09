/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "Worker.h"
#include "../ScientificCode.h"
#include "../Const.h"
#include "../easylogging++.h"
/**
 * Worker implementation
 */

Worker::Worker(int rank, int number_of_processors) : AbstractWorker(rank, number_of_processors)
{

}

void Worker::preporcessing()
{
    code_preprocessing_slave(0, NULL);
    TaskType task;
    MPI_Send(&task, 1, MPI_INT, MASTER, FINISH, MPI_COMM_WORLD);
}

void Worker::postprocessing()
{
    code_postprocessing_slave();
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    LOG(INFO) << "worker " << rank << " sagt ade";
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
    preporcessing();
    wait_for_task();
    postprocessing();
}
