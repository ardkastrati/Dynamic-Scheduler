/**
 * Project Dynamic Scheduler for Scientific Simulations
 */

#include "ScientificCode.h"
#include "easylogging++.h"
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

void code_preprocessing_master(int argc, char* argv[], TaskType* buffer, int* initial_tasks_number)
{
    LOG(INFO) << "code preprocessing master";
    *initial_tasks_number = 100;
    for (int i = 0; i < 100; i++)
    {
        buffer[i] = i;
    }
}

void code_preprocessing_slave(int argc, char* argv[])
{
    LOG(INFO) << "code preprocessing slave";
}

void code_run_task(TaskType task) {
    if (task < 50) {
        for (int i = 0; i < 1; i++) {
            Worker::place_task(task + 100 + i);
        }

    }
    for (int i = 0; i < task * 100000; i++) {
        log(i);

    }
    LOG(INFO) << "task done:" << task;
}
