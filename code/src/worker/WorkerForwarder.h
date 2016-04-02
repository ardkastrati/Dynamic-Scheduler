/**
 * This function are used to call c++ member function from the scientific c code.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#ifndef CODE_WORKERFORWARDER_H
#define CODE_WORKERFORWARDER_H

#include "../TypesExtern.h"

/**
 * This function is called from the scientific c code and calls the member function from context (WorkerExecutor) and pass the task.
 *
 * @param context pointer of the object with the function to be called
 * @param task to be passed
 */
void place_task_forwarder_master(void* context, Task task);

/**
 * This function is called from the scientific c code and calls the member function from context (TaskStealingWorker) and pass the task.
 *
 * @param context pointer of the object with the function to be called
 * @param task to be passed
 */
void place_task_forwarder_taskstealing(void* context, Task task);

#endif //CODE_WORKERFORWARDER_H
