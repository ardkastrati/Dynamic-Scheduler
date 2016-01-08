/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "AbstractScheduler.h"
#include "../easylogging++.h"

/**
 * AbstractScheduler implementation
 */


AbstractScheduler::AbstractScheduler(SchedulingStrategy* schedulingStrategy)
{
    this->schedulingStrategy = schedulingStrategy;
}

AbstractScheduler::~AbstractScheduler()
{
    delete schedulingStrategy;
}

