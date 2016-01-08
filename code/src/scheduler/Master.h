/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _MASTER_H
#define _MASTER_H

#include "AbstractScheduler.h"


class Master: public AbstractScheduler {
public:
    Master(SchedulingStrategy*);
    void execute(int argc, char* argv[]);

private:
    void preprocessing(int argc, char* arcv[], TaskType* buffer, int* initail_tasks_number);
    void postprocessing();
    void loop();
};

#endif //_MASTER_H
