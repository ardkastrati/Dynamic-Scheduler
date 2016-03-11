/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _WORKER_H
#define _WORKER_H

#include "AbstractWorker.h"


class Worker: public AbstractWorker {
public:
    Worker(int rank, int number_of_processors);
    void execute(int argc, char* argv[]);
    void run_task(TaskType task);
    static void place_task(TaskType task);
private:
    void preporcessing(int argc, char* argv[]);
    void postprocessing();
    void wait_for_task();

};

#endif //_WORKER_H
