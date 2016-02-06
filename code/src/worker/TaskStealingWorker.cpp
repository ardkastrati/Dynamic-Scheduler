//
// Created by fabio on 29.01.16.
//

#include "TaskStealingWorker.h"
#include "../ScientificCode.h"

TaskStealingWorker::TaskStealingWorker(TaskStealingScheduler *scheduler)
{
    if (scheduler == NULL) {
        throw "Illegal argument: scheduler must not be NULL";
    }
    this->scheduler = scheduler;
}

void TaskStealingWorker::place_task(Task task)
{
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
    code_run_task(task, &place_task_forwarder, this);
}
