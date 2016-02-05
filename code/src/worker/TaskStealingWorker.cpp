//
// Created by fabio on 29.01.16.
//

#include "TaskStealingWorker.h"
#include "../ScientificCode.h"

void TaskStealingWorker::place_task(Task task)
{

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
