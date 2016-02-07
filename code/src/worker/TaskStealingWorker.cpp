//
// Created by fabio on 29.01.16.
//

#include "TaskStealingWorker.h"
#include "../ScientificCode.h"
#include "../util/TimeUtility.h"

TaskStealingWorker::TaskStealingWorker(TaskStealingScheduler *scheduler)
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
    code_run_task(task, &place_task_forwarder, this);
    time_end = get_time_in_mirco();

    TaskData task_data;
    task_data.time_intercommunication_end = -1;
    task_data.time_intercommunication_start = -1;
    task_data.rank = scheduler->get_rank();
    task_data.time_appeared = task.time_appeared;
    task_data.time_started = time_begin;
    task_data.time_ended = time_end;
    task_data.parent  = task.parent;
    task_data.event = 1; //TODO: Right event
    task_data.mode = 1; //TODO: Right mode
    task_data.parameter_size = task.parameter_size;
    memcpy(task_data.parameters, task.parameters, sizeof(double) * task.parameter_size);
}
