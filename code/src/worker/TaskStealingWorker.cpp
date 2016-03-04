#define NDEBUG

#include "TaskStealingWorker.h"
#include "../ScientificCode.h"
#include "../util/TimeUtility.h"
#include "../Const.h"
#include <iostream>

using namespace std;



TaskStealingWorker::TaskStealingWorker(AbstractScheduler *scheduler)
{
    if (scheduler == NULL) {
        throw "Illegal argument: scheduler must not be NULL";
    }
    this->scheduler = scheduler;
}

void TaskStealingWorker::place_task(Task task)
{
    task.time_appeared = get_time_in_mirco();
    scheduler->place_task(task);


    TaskData task_data;
    task_data.rank = scheduler->get_rank();
    task_data.time_appeared = task.time_appeared;
    task_data.parent  = task.parent;
    task_data.event = 0;
    task_data.mode = 1;
    task_data.parameter_size = task.parameter_size;
    memcpy(task_data.parameters, task.parameters, sizeof(double) * task.parameter_size);

    MPI_Request request;
    MPI_Isend(&task_data, 1, MY_MPI_TASK_DATA_TYPE, DATABASE, DATAENTRY, MPI_COMM_WORLD, &request);
}

void TaskStealingWorker::preprocessing(int argc, char* argv[])
{
    code_preprocessing_slave(argc, argv);
}

void TaskStealingWorker::postprocessing()
{
    code_postprocessing_slave();
}

void TaskStealingWorker::run_task(Task task)
{
    long time_begin;
    long time_end;

    time_begin = get_time_in_mirco();

    TaskData task_data;
    task_data.time_intercommunication_end = -1;
    task_data.time_intercommunication_start = -1;
    task_data.rank = scheduler->get_rank();
    task_data.time_appeared = task.time_appeared;
    task_data.time_started = time_begin;

    task_data.parent  = task.parent;
    task_data.event = 1;
    task_data.mode = 1;
    task_data.parameter_size = task.parameter_size;
    memcpy(task_data.parameters, task.parameters, sizeof(double) * task.parameter_size);


    MPI_Request request;
    MPI_Isend(&task_data, 1, MY_MPI_TASK_DATA_TYPE, DATABASE, DATAENTRY, MPI_COMM_WORLD, &request);


    code_run_task(task, &place_task_forwarder_taskstealing, this);

    time_end = get_time_in_mirco();

    task_data.time_ended = time_end;
    task_data.event = 2;

    MPI_Isend(&task_data, 1, MY_MPI_TASK_DATA_TYPE, DATABASE, DATAENTRY, MPI_COMM_WORLD, &request);
    cout << "rank: " << scheduler->get_rank() << ", task: " << task.parameters[0] << " took " << time_end - time_begin << " mircoseconds" << endl;
}
