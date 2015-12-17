#include "scheduler.hpp"
#include "logger.hpp"
#include "fifo.hpp"

Scheduler::Scheduler()
{
    scheduler_queue = new FIFO();
}

void Scheduler::execute(){
    Logger::log(TAG, "execute()", Logger::LEVEL_LOW);
    for (int i = 0; i < 100; i++) {
        scheduler_queue->push_new_task(i, 0);
    }
    while (scheduler_queue->get_task_count() != 0) {
        TaskType task = scheduler_queue->pop_next_task();
        Logger::log(TAG, "Removed Task " + to_string(task) + " from queue", Logger::LEVEL_LOW);
    }

}
Scheduler::~Scheduler()
{
    delete scheduler_queue;
}
