//
// Created by fabio on 29.01.16.
//

#ifndef _TASKSTEALINGWORKER_H
#define _TASKSTEALINGWORKER_H

#include "Worker.h"
#include "../scheduler/TaskStealingScheduler.h"


class TaskStealingWorker : public Worker {

private:
    TaskStealingScheduler* scheduler;

public:

    TaskStealingWorker(TaskStealingScheduler* scheduler);

    void run_task(Task task);

    void preprocessing(int argc, char* argv[]);

    void postprocessing();

    void place_task(Task task);

};


#endif //_TASKSTEALINGWORKER_H
