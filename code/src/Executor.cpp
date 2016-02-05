#include "Executor.h"
#include "scheduler/TaskStealingScheduler.h"
#include "scheduler/MpiWinLIFO.h"
#include "../lib/easylogging++.h"
#include "scheduler/Master.h"
#include "scheduler/SJF.h"
#include "worker/WorkerExecutor.h"
#include "database/DatabaseServer.h"


Executor::Executor(int rank, int number_of_processors) :
    rank(rank),
    number_of_processors(number_of_processors)
{
}

Executor *Executor::get_new_executor_by_rank(int rank, int number_of_processors, std::string design,
                                             std::string strategy)
{
    MpiWinSchedulingStrategy* scheduling_strategy = new MpiWinLIFO(200, rank, number_of_processors);
    return new TaskStealingScheduler(scheduling_strategy, NULL, rank, number_of_processors);
    if (rank == 0)
    {
        return new Master(new SJF(), NULL,rank, number_of_processors);
    }
    else if (rank == 20)
    {
        return new DatabaseServer(rank, number_of_processors);
    }
    else
    {
        return new WorkerExecutor(rank, number_of_processors);
    }

}
