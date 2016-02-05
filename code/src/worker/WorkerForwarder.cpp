//
// Created by fabio on 29.01.16.
//


#include "WorkerForwarder.h"

void place_task_forwarder(void* context, Task task)
{
    static_cast<Worker*>(context)->place_task(task);
}