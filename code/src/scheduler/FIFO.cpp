#define NDEBUG

#include "FIFO.h"
//#include "../../lib/easylogging++.h"

FIFO::FIFO() :
queue(new std::queue<Task>())
{
}

FIFO::~FIFO()
{
    delete queue;
    //LOG(DEBUG) << "FIFIO Destructor";
}

Task FIFO::get_next_task()
{
    return queue->front();
}

int FIFO::get_task_count()
{
    return queue->size();
}
Task FIFO::pop_next_task()
{
    Task result;
    result = queue->front();
    queue->pop();
    return result;
}

void FIFO::push_new_task(Task task, long runtime)
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
bool FIFO::is_statistic_based()
{
    return false;
}