/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _ABSTRACTSCHEDULER_H
#define _ABSTRACTSCHEDULER_H

#include "../Executer.h"
#include "SchedulingStrategy.h"


class AbstractScheduler: public Executer {
protected:
    SchedulingStrategy* schedulingStrategy;

public: 
    AbstractScheduler(SchedulingStrategy* schedulingStrategy, int rank, int number_of_processors);
    ~AbstractScheduler();
};

#endif //_ABSTRACTSCHEDULER_H
