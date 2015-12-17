#include "fifo.hpp"

FIFO::FIFO()
{
    task_queue = new queue<TaskType>();
}

TaskType FIFO::get_next_task()
{
    return task_queue->front();
}

int FIFO::get_task_count()
{
    return task_queue->size();
}

TaskType FIFO::pop_next_task()
{
    TaskType result = task_queue->front();
    task_queue->pop();
    return result;
}

void FIFO::push_new_task(TaskType task, long runtime)
{
    task_queue->push(task);
}

void FIFO::change_strategy(SchedulingStrategy *new_strategy)
{
    return;
}

FIFO::~FIFO()
{
    delete task_queue;
}

