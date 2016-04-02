#include "SJF.h"

bool ComparisonClassSJF::operator ()(TaskTimeType task_time_1, TaskTimeType task_time_2) {
    return task_time_1.second > task_time_2.second;
}

SJF::SJF() :
queue(new std::priority_queue<TaskTimeType, std::vector<TaskTimeType>, ComparisonClassSJF>())
{
}

SJF::~SJF()
{
    delete queue;
}

Task SJF::get_next_task()
{
    TaskTimeType result = queue->top();
    return result.first;
}

int SJF::get_task_count()
{
    return queue->size();
}

Task SJF::pop_next_task()
{
    TaskTimeType result;
    result = queue->top();
    queue->pop();
    return result.first;
}

void SJF::push_new_task(Task task, long runtime)
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

bool SJF::is_statistic_based()
{
    return true;
}
