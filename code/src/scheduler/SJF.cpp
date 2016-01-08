/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "SJF.h"

/**
 * SJF implementation
 * 
 * Implements the SchedulingStrategy interface and realises the Shortest Job First (SJF) scheduling strategy. Shortest Job First scheduling uses the estimated runtime of  tasks  to order the task queue.
 * SJF is a statistically based scheduling strategy
 */

SJF::SJF()
{
    //TODO:Set right comparer
    queue = new std::priority_queue<TaskTimeType>();
}

SJF::~SJF()
{
    delete queue;
}

TaskType SJF::get_next_task()
{
    TaskTimeType result = queue->top();
    return result.first;
}

int SJF::get_task_count()
{
    return queue->size();
}

void SJF::pop_next_task()
{
    queue->pop();
}

void SJF::push_new_task(TaskType task, long runtime)
{
    TaskTimeType taskTime;
    taskTime.first = task;
    taskTime.second = runtime;
    queue->push(taskTime);
}

SchedulingStrategy* SJF::change_strategy(SchedulingStrategy *new_strategy)
{
    int size = queue->size();
    for (int i = 0; i < size; i++)
    {
        TaskTimeType taskTime = queue->top();
        queue->pop();
        new_strategy->push_new_task(taskTime.first, taskTime.second);
    }
    return new_strategy;
}
