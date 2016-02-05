//
// Created by fabio on 29.01.16.
//

#ifndef _TASKSTEALINGWORKER_H
#define _TASKSTEALINGWORKER_H

#include "Worker.h"


class TaskStealingWorker : public Worker {
public:

    void run_task(Task task);

    void preprocessing(int argc, char* argv[]);

    void postprocessing();

    void place_task(Task task);

};


#endif //_TASKSTEALINGWORKER_H
