#include "Executor.h"
#include "scheduler/TaskStealingScheduler.h"
#include "scheduler/MpiWinLIFO.h"
#include "scheduler/MpiWinFIFO.h"
#include "scheduler/MpiWinBinaryHeap.h"
#include "scheduler/Master.h"
#include "scheduler/SJF.h"
#include "scheduler/FIFO.h"
#include "scheduler/LIFO.h"
#include "scheduler/LJF.h"
#include "scheduler/SchedulingStrategy.h"
#include "worker/WorkerExecutor.h"
#include "database/DatabaseServer.h"
#include <mpi.h>
#include "TypesExtern.h"
#include "Const.h"


Executor::Executor(int rank, int number_of_processors) :
    rank(rank),
    number_of_processors(number_of_processors)
{
}

Executor::~Executor() { }

Executor *Executor::get_new_executor_by_rank(int rank, int number_of_processors, DesignEnum design,
                                             StrategyEnum strategy) {
    Executor* executor;
    switch (design)
    {
        case DesignEnum::MASTER_WORKER:
            executor = get_new_executor_for_master_worker(rank, number_of_processors, strategy);
            break;
        case DesignEnum::TASK_STEALING:
            executor = get_new_executor_for_taskstealing(rank, number_of_processors, strategy);
            break;
        default:
            throw "Unreachable";
    }
    return executor;
}

Executor* Executor::get_new_executor_for_master_worker(int rank, int number_of_processors, StrategyEnum strategy) {
    Executor* executor;
    if (rank == 0)
    {
        SchedulingStrategy* scheduling_strategy;
        switch (strategy)
        {
            case ENUM_FIFO:
                scheduling_strategy = new FIFO();
                break;
            case ENUM_LIFO:
                scheduling_strategy = new LIFO();
                break;
            case ENUM_SJF:
                scheduling_strategy = new SJF();
                break;
            case ENUM_LJF:
                scheduling_strategy = new LJF();
                break;
            default:
                throw "Unreachable";
        }
        executor = new Master(scheduling_strategy, NULL, rank, number_of_processors);
    }
    else if (rank == 1)
    {
        executor = new DatabaseServer(rank, number_of_processors);
    }
    else
    {
        executor = new WorkerExecutor(rank, number_of_processors);
    }
    return executor;
}

Executor* Executor::get_new_executor_for_taskstealing(int rank, int number_of_processors, StrategyEnum strategy)
{
    Executor* executor;

    if (rank == 1) {
        MPI_Comm_split(MPI_COMM_WORLD, 0, rank, &MY_MPI_COMM_TASKSTEALING);
        executor = new DatabaseServer(rank, number_of_processors);
    } else {
        MPI_Comm_split(MPI_COMM_WORLD, 1, rank, &MY_MPI_COMM_TASKSTEALING);
        int taskstealing_world_rank;
        int taskstealing_world_number_of_processors;

        MPI_Comm_rank(MY_MPI_COMM_TASKSTEALING, &taskstealing_world_rank);
        MPI_Comm_size(MY_MPI_COMM_TASKSTEALING, &taskstealing_world_number_of_processors);
        MpiWinSchedulingStrategy* scheduling_strategy;
        switch(strategy) {
          case ENUM_LIFO:
            scheduling_strategy = new MpiWinLIFO(MAX_MPI_WIN_TASK_COUNT, taskstealing_world_rank, taskstealing_world_number_of_processors);
            break;
          case ENUM_SJF:
            scheduling_strategy = new MpiWinBinaryHeap(MAX_MPI_WIN_TASK_COUNT, taskstealing_world_rank, taskstealing_world_number_of_processors, true);
            break;
          case ENUM_LJF:
            scheduling_strategy = new MpiWinBinaryHeap(MAX_MPI_WIN_TASK_COUNT, taskstealing_world_rank, taskstealing_world_number_of_processors, false);
            break;
          case ENUM_FIFO:
            scheduling_strategy = new MpiWinFIFO(MAX_MPI_WIN_TASK_COUNT, taskstealing_world_rank, taskstealing_world_number_of_processors);
            break;
          default:
            throw "Unreachable";
        }
        executor = new TaskStealingScheduler(scheduling_strategy, NULL, taskstealing_world_rank,
                                             taskstealing_world_number_of_processors);
    }

    return executor;
}
