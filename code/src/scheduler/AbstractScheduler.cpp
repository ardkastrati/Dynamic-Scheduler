/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "AbstractScheduler.h"
#include "../easylogging++.h"

/**
 * AbstractScheduler implementation
 */


AbstractScheduler::AbstractScheduler(SchedulingStrategy* schedulingStrategy, int rank, int number_of_processors) : Executer(rank, number_of_processors)
{
    this->schedulingStrategy = schedulingStrategy;
}

AbstractScheduler::~AbstractScheduler()
{
    delete schedulingStrategy;
}

