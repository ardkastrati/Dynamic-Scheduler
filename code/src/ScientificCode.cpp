#include "ScientificCode.h"
#include "../lib/easylogging++.h"
#include <cmath>
#include "worker/Worker.h"

void code_postprocessing_master()
{
    LOG(INFO) << "code postprocessing master";
}

void code_postprocessing_slave()
{
    LOG(INFO) << "code postprocessing slave";
}

void code_preprocessing_master(int argc, char* argv[], Task* buffer, int* initial_tasks_number)
{
    LOG(INFO) << "code preprocessing master";
    *initial_tasks_number = 100;
    for (int i = 0; i < 100; i++)
    {
        Task task;
        task.parameters[0] = i;
        task.parameter_size = 1;
        buffer[i] = task;
    }
}

void code_preprocessing_slave(int argc, char* argv[])
{
    LOG(INFO) << "code preprocessing slave";
}

void code_run_task(Task task, void (*place_task_forwarder) (void*, Task), void* context) {
    if (task.parameters[0] < 50) {
        Task newTask;
        newTask.parameter_size = 1;
        newTask.parameters[0] = task.parameters[0] + 100;
        place_task_forwarder(context, newTask);

    }
    for (int i = 0; i < task.parameters[0] * 100000; i++) {
        log(i);

    }
    LOG(INFO) << "task done:" << task.parameters[0];
}
