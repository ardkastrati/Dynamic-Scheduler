#include "scheduler.hpp"
#include "logger.hpp"

Scheduler::Scheduler()
{

}

void Scheduler::execute(){
    Logger::log(TAG, "execute()", Logger::LEVEL_LOW);
}

