#include "LJF.h"

bool ComparisonClassLJF::operator ()(TaskTimeType task_time_1, TaskTimeType task_time_2) {
    return task_time_1.second < task_time_2.second;
}

LJF::LJF() :
queue(new std::priority_queue<TaskTimeType, std::vector<TaskTimeType>, ComparisonClassLJF>())
{
}

LJF::~LJF()
{
    delete queue;
}

Task LJF::get_next_task()
{
    TaskTimeType result = queue->top();
    return result.first;
}

int LJF::get_task_count()
{
    return queue->size();
}

Task LJF::pop_next_task()
{
    TaskTimeType result;
    result = queue->top();
    queue->pop();
    return result.first;
}

void LJF::push_new_task(Task task, long runtime)
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

bool LJF::is_statistic_based()
{
    return true;
}
