//
// Created by fabio on 29.01.16.
//

#ifndef _TASKSTEALINGWORKER_H
#define _TASKSTEALINGWORKER_H

#include "Worker.h"
#include "../scheduler/AbstractScheduler.h"


class TaskStealingWorker : public Worker {

private:
    AbstractScheduler* scheduler;

public:

    TaskStealingWorker(AbstractScheduler* scheduler);

    void run_task(Task task);

    void preprocessing(int argc, char* argv[]);

    void postprocessing();

    void place_task(Task task);

};


#endif //_TASKSTEALINGWORKER_H
