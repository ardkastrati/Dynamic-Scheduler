#include "executer.hpp"
#include "scheduler.hpp"
#include "worker.hpp"
#include "logger.hpp"

Executer::Executer()
{

}
Executer* Executer::get_executer_by_rank(int rank, int number_of_processors) {
    if (rank == 0) {
        return new Scheduler();
    } else {
        return new Worker();
    }
}
void Executer::execute() {
    Logger::log(TAG, "execute()", Logger::LEVEL_LOW);
}

