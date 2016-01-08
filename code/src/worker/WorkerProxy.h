/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _WORKERPROXY_H
#define _WORKERPROXY_H

#include "AbstractWorker.h"
#include <queue>


class WorkerProxy: public AbstractWorker {
public:
    WorkerProxy(int number_of_processors);
    void execute(int argc, char* argv[]);
    void run_task(TaskType task);
private:
    std::queue<int>* free_worker;
    void preporcessing();
    void postprocessing();
};

#endif //_WORKERPROXY_H
