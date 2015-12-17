#include "worker.hpp"
#include "logger.hpp"

Worker::Worker()
{

}

void Worker::execute() {
    Logger::log(TAG, "execute()", Logger::LEVEL_LOW);
}

