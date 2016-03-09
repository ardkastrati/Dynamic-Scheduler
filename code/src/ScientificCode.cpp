/**
 * This is a dummy implementation of the Scientific code interface.
 * This implementation is used for testing.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#define NDEBUG

#include "ScientificCode.h"
//#include "../lib/easylogging++.h"
#include <cmath>
#include "worker/Worker.h"
#include <iostream>

using namespace std;

void code_postprocessing_master()
{
    //LOG(DEBUG) << "code postprocessing master";
}

void code_postprocessing_slave()
{
    //LOG(DEBUG) << "code postprocessing slave";
}

void code_preprocessing_master(int argc, char* argv[], Task* buffer, int* initial_tasks_number)
{
    //LOG(DEBUG) << "code preprocessing master";
    *initial_tasks_number = 100;
    for (int i = 0; i < 100; i++)
    {
        Task task;
        task.parameters[0] = i;
        task.parameter_size = 1;
        task.runtime = i;
        buffer[i] = task;
    }
}

void code_preprocessing_slave(int argc, char* argv[])
{
    //LOG(DEBUG) << "code preprocessing slave";
}

void code_run_task(Task task, void (*place_task_forwarder) (void*, Task), void* context) {
    if (task.parameters[0] < 50) {
      for (int i = 0; i < 1; i++) {
        Task newTask;
        newTask.parameter_size = 1;
        newTask.parameters[0] = task.parameters[0] + 100;// + 100* i;
        newTask.runtime = (long) newTask.parameters[0];
        newTask.parent = task.id;
        place_task_forwarder(context, newTask);
      }

    }
    for (int i = 0; i < task.parameters[0] * 100000; i++) {
        log(i);

    }
    //LOG(DEBUG) << "task done:" << task.parameters[0];
}
