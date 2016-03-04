#include "WorkerForwarder.h"
#include "WorkerExecutor.h"
#include "TaskStealingWorker.h"

void place_task_forwarder_master(void* context, Task task)
{
    static_cast<WorkerExecutor*>(context)->place_task(task);
}

void place_task_forwarder_taskstealing(void* context, Task task)
{
    static_cast<TaskStealingWorker*>(context)->place_task(task);
}