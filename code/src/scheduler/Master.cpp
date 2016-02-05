#include <mpi.h>
#include "Master.h"
#include "../../lib/easylogging++.h"
#include "../Const.h"

Master::Master(SchedulingStrategy* scheduling_strategy, DataMining* data_miner, int rank, int number_of_processors)
: AbstractScheduler(scheduling_strategy, data_miner, rank, number_of_processors),
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
            return;
        }

        MPI_Recv(&task, 1, MY_MPI_TASK_TYPE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == FINISH)
        {
            int worker = status.MPI_SOURCE;
            free_worker->push(worker);

        }else if (status.MPI_TAG == REQUEST) {

            long runtime = 0;

            if (scheduling_strategy->is_statistic_based()) {
                //TODO: update code to new TaskType
                double param = 0;
                data_miner->predict(&param);
            }

            scheduling_strategy->push_new_task(task, runtime);
            LOG(INFO) << "added task: " << task.parameters[0];
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
    return scheduling_strategy->get_task_count() == 0 && free_worker->size() == number_of_processors - 1;
}

void Master::execute(int argc, char* argv[]){
    LOG(INFO) << "I'am a master";

    Task init_tasks[100];
    int init_tasks_number;
    preprocessing(argc, argv, init_tasks, &init_tasks_number);

    for (int i = 0; i < init_tasks_number; i++) {
        scheduling_strategy->push_new_task(init_tasks[i], scheduling_strategy->DEFAULT_RUNTIME);
    }

    run();

    postprocessing();
}
