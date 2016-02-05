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
    Task task;
    for (int i = 0; i < 100; i++)
    {
        task.parameter_size = 100;
        for (int j = 0; j < task.parameter_size; j++) {
            task.parameters[j] = (double) i;
        }
        buffer[i] = task;
    }
}

void code_preprocessing_slave(int argc, char* argv[])
{
    LOG(INFO) << "code preprocessing slave";
}

void code_run_task(Task task, void (*place_task_forwarder) (void*, Task), void* context) {
    if (task.parameters[0] < 50) {
        for (int i = 0; i < 1; i++) {
            Task newTask;
            newTask.parameter_size = -1;
            place_task_forwarder(context, newTask);
        }

    }
    for (int i = 0; i < task.parameters[0] * 100000; i++) {
        log(i);

    }
    LOG(INFO) << "task done:" << task.parameters[0];
}
