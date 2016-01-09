/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _MASTER_H
#define _MASTER_H

#include "AbstractScheduler.h"
#include <queue>


class Master: public AbstractScheduler {
public:
    Master(SchedulingStrategy* schedulingStrategy, int rank, int number_of_processors);
    ~Master();
    void execute(int argc, char* argv[]);

private:
    std::queue<int>* free_worker;
    void preprocessing(int argc, char* arcv[], TaskType* buffer, int* initail_tasks_number);
    void postprocessing();
    void loop();
    bool is_finish();
};

#endif //_MASTER_H
