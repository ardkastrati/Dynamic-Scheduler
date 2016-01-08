/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "WorkerProxy.h"

/**
 * WorkerProxy implementation
 */

WorkerProxy::WorkerProxy(int number_of_processors)
{
    /*free_worker = new std::queue<int>();
    //TODO: richtige arbeiter herausfinden? mehere masters, database
    for (int i = 1; i < number_of_processors; i++) {
        free_worker->push(i);
    }*/
}

void WorkerProxy::run_task(TaskType task)
{

}
