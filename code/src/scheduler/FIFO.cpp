/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "FIFO.h"

/**
 * FIFO implementation
 * 
 * Implements the SchedulingStrategy interface and realises the First In - First Out (FIFO) scheduling strategy.
 * FIFO is a non-statistically based scheduling strategy
 */

FIFO::FIFO()
{
    queue = new std::queue<TaskType>();
}

FIFO::~FIFO()
{
    delete queue;
}

TaskType FIFO::get_next_task()
{
    return queue->front();
}

int FIFO::get_task_count()
{
    return queue->size();
}

void FIFO::pop_next_task()
{
    return queue->pop();
}

void FIFO::push_new_task(TaskType task, long runtime)
{
    queue->push(task);
}

SchedulingStrategy* FIFO::change_strategy(SchedulingStrategy *new_strategy)
{
    int size = queue->size();
    for (int i = 0; i < size; i++)
    {
        new_strategy->push_new_task(queue->front(), DEFAULT_RUNTIME);
        queue->pop();
    }
    return new_strategy;
}
