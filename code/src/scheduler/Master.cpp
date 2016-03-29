#define NDEBUG

#include <mpi.h>
#include "Master.h"
#include "../Const.h"
#include "../util/IdUtility.h"


Master::Master(MasterSchedulingStrategy* scheduling_strategy, int rank, int number_of_processors)
: AbstractScheduler(scheduling_strategy, rank, number_of_processors),
free_worker(new std::queue<int>())
{
}

Master::~Master(){
    delete free_worker;
}



void Master::run()
{
    Task task;
    MPI_Status status;

    while(true)
    {
        if(is_finish())
        {
            int size = free_worker->size();
            for(int i = 0; i < size; i++) {
                int worker = free_worker->front();
                MPI_Send(&task, 1, MY_MPI_TASK_TYPE, worker, STOP, MPI_COMM_WORLD);
                free_worker->pop();
            }
            TaskData taskData;
            MPI_Send(&taskData, 1, MY_MPI_TASK_DATA_TYPE, DATABASE, STOP, MPI_COMM_WORLD);
            return;
        }

        MPI_Recv(&task, 1, MY_MPI_TASK_TYPE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == FINISH)
        {
            int worker = status.MPI_SOURCE;
            free_worker->push(worker);

        }else if (status.MPI_TAG == REQUEST) {
            place_task(task);
        }
        if (free_worker->size() > 0 && scheduling_strategy->get_task_count() > 0) {
            int worker = free_worker->front();
            free_worker->pop();
            task = scheduling_strategy->pop_next_task();
            MPI_Send(&task, 1, MY_MPI_TASK_TYPE, worker, START, MPI_COMM_WORLD);
        }

    }
}

bool Master::is_finish()
{
    return scheduling_strategy->get_task_count() == 0 && free_worker->size() == number_of_processors - 2;
}

void Master::execute(int argc, char* argv[]){
    Task init_tasks[MAX_INIT_TASK_COUNT];
    int init_tasks_number;
    preprocessing(argc, argv, init_tasks, &init_tasks_number);

    for (int i = 0; i < init_tasks_number; i++) {
        //place_task(init_tasks[i]);
        scheduling_strategy->push_new_task(init_tasks[i], scheduling_strategy->DEFAULT_RUNTIME);
    }

    run();

    postprocessing();
}
