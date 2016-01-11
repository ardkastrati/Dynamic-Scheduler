/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "LJF.h"

/**
 * LJF implementation
 * 
 * Implements the SchedulingStrategy interface and realises the Longest Job First (LJF) scheduling strategy. Longest Job First scheduling uses the estimated runtime of tasks  to order the task queue.
 * LJF is a statistically based scheduling strategy
 */

bool ComparisonClassLJF::operator ()(TaskTimeType task1, TaskTimeType task2) {
    return task1.second < task2.second;
}

LJF::LJF()
{
    //TODO:Set right comparer
    queue = new std::priority_queue<TaskTimeType, std::vector<TaskTimeType>, ComparisonClassLJF>();
}

LJF::~LJF()
{
    delete queue;
}

TaskType LJF::get_next_task()
{
    TaskTimeType result = queue->top();
    return result.first;
}

int LJF::get_task_count()
{
    return queue->size();
}

void LJF::pop_next_task()
{
    queue->pop();
}

void LJF::push_new_task(TaskType task, long runtime)
{
    TaskTimeType taskTime;
    taskTime.first = task;
    taskTime.second = runtime;
    queue->push(taskTime);
}

SchedulingStrategy* LJF::change_strategy(SchedulingStrategy *new_strategy)
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
