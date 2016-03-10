/**
 * This is a dummy implementation of the Scientific code interface.
 * This implementation is used for testing.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#define NDEBUG

#include "ScientificCode.h"
#include <cmath>
#include "worker/Worker.h"
#include <iostream>
#include "Const.h"

using namespace std;

void code_postprocessing_master()
{
}

void code_postprocessing_slave()
{
}

void code_preprocessing_master(int argc, char* argv[], Task* buffer, int* initial_tasks_number)
{
    *initial_tasks_number = MAX_INIT_TASK_COUNT;
    for (int i = 0; i < MAX_INIT_TASK_COUNT; i++)
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
}

void code_run_task(Task task, void (*place_task_forwarder) (void*, Task), void* context) {
    if (task.parameters[0] < 50) {
      for (int i = 0; i < 10; i++) {
        Task newTask;
        newTask.parameter_size = 1;
        newTask.parameters[0] = task.parameters[0] + 100;// + 100* i;
        newTask.runtime = (long) newTask.parameters[0];
        newTask.parent = task.id;
        place_task_forwarder(context, newTask);
      }

    }
    for (int i = 0; i < task.parameters[0] * 10000; i++) {
        log(i);

    }
}
