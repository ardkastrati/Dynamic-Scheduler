#ifndef FIFO_H
#define FIFO_H

#include "schedulingstrategy.hpp"
#include <queue>
#include "types.h"

using namespace std;

class FIFO : public SchedulingStrategy
{
private:
    queue<TaskType>* task_queue;
public:
    FIFO();
    ~FIFO();
    virtual TaskType get_next_task();
    virtual int get_task_count();
    virtual TaskType pop_next_task();
    virtual void push_new_task(TaskType task, long runtime);
    virtual void change_strategy(SchedulingStrategy* new_strategy);

};

#endif // FIFO_H
