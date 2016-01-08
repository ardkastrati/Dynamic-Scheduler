/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _WORKER_H
#define _WORKER_H

#include "AbstractWorker.h"


class Worker: public AbstractWorker {
public:
    void execute(int argc, char* argv[]);
    void run_task(TaskType task);
private:
    void preporcessing();
    void postprocessing();
    void wait_for_task();
};

#endif //_WORKER_H
