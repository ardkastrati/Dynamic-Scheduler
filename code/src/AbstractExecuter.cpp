#include "AbstractExecuter.hpp"
#include "Scheduler.hpp"

void AbstractExecuter::get_new_executer_by_id(int rank, int number_of_processors) {
    if (rank == 0) {
        return new Scheduler();
    }
}
