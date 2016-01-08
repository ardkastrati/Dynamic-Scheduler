/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "LIFO.h"

/**
 * LIFO implementation
 * 
 * Implements the SchedulingStrategy interface and realises the Last In - First Out (LIFO) scheduling strategy.
 * LIFO is a non-statistically based scheduling strategy
 */

LIFO::LIFO()
{
    stack = new std::stack<TaskType>();
}

LIFO::~LIFO()
{
    delete stack;
}

TaskType LIFO::get_next_task()
{
    return stack->top();
}

int LIFO::get_task_count()
{
    return stack->size();
}

void LIFO::pop_next_task()
{
    stack->pop();
}

void LIFO::push_new_task(TaskType task, long runtime)
{
    stack->push(task);
}

SchedulingStrategy* LIFO::change_strategy(SchedulingStrategy *new_strategy)
{
    int size = stack->size();
    for(int i = 0; i < size; i++)
    {
        new_strategy->push_new_task(stack->top(), DEFAULT_RUNTIME);
        stack->pop();
    }
    return new_strategy;
}
