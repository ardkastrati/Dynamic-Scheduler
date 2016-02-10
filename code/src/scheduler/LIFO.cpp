#define NDEBUG

#include "LIFO.h"
#include "../../lib/easylogging++.h"

LIFO::LIFO() :
stack(new std::stack<Task>())
{
}

LIFO::~LIFO()
{
    delete stack;
    LOG(DEBUG) << "LIFO destructor";
}

Task LIFO::get_next_task()
{
    return stack->top();
}

int LIFO::get_task_count()
{
    return stack->size();
}

Task LIFO::pop_next_task()
{
    Task result;
    result = stack->top();
    stack->pop();
    return result;
}

void LIFO::push_new_task(Task task, long runtime)
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
bool LIFO::is_statistic_based()
{
    return false;
}