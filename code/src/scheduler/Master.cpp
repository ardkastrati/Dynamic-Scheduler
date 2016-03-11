/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include <mpi.h>
#include "Master.h"
#include "../easylogging++.h"
#include "../ScientificCode.h"
#include "../Const.h"
#include "LJF.h"

/**
 * Master implementation
 */

Master::Master(SchedulingStrategy* schedulingStrategy, int rank, int number_of_processors) : AbstractScheduler(schedulingStrategy, rank, number_of_processors)
{
    free_worker = new std::queue<int>();
}

Master::~Master(){
    delete free_worker;
}

void Master::preprocessing(int argc, char* arcv[], TaskType* buffer, int* initail_tasks_number)
{
    code_preprocessing_master(argc, arcv, buffer, initail_tasks_number);
}

void Master::postprocessing()
{
    code_postprocessing_master();
}

void Master::run()
{
    TaskType task;
    MPI_Status status;

    while(true)
    {
        if(is_finish())
        {
            int size = free_worker->size();
            for(int i = 0; i < size; i++) {
                int worker = free_worker->front();
                MPI_Send(&task, 1, MPI_INT, worker, STOP, MPI_COMM_WORLD);
                free_worker->pop();
            }
            return;
        }

        MPI_Recv(&task, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == FINISH)
        {
            int worker = status.MPI_SOURCE;
            free_worker->push(worker);
        }else if (status.MPI_TAG == REQUEST) {
            schedulingStrategy->push_new_task(task, task);
            LOG(INFO) << "added task: " << task;
        }
        if (free_worker->size() > 0 && schedulingStrategy->get_task_count() > 0) {
            int worker = free_worker->front();
            free_worker->pop();
            task = schedulingStrategy->get_next_task();
            schedulingStrategy->pop_next_task();
            MPI_Send(&task, 1, MPI_INT, worker, START, MPI_COMM_WORLD);
        }

    }
}

bool Master::is_finish()
{
    return schedulingStrategy->get_task_count() == 0 && free_worker->size() == number_of_processors - 1;
}

void Master::execute(int argc, char* argv[]){
    LOG(INFO) << "I'am a master";

    TaskType init_tasks[100];
    int init_tasks_number;
    preprocessing(argc, argv, init_tasks, &init_tasks_number);

    for (int i = 0; i < init_tasks_number; i++) {
        schedulingStrategy->push_new_task(init_tasks[i], init_tasks[i]);
    }

    run();

    postprocessing();
}
