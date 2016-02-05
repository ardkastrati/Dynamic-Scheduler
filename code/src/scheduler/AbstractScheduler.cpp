#include "AbstractScheduler.h"
#include "../ScientificCode.h"

AbstractScheduler::AbstractScheduler(SchedulingStrategy* scheduling_strategy,
    DataMining* data_miner, int rank, int number_of_processors) :
    Executor(rank, number_of_processors),
    scheduling_strategy(scheduling_strategy),
    data_miner(data_miner)
{
}

AbstractScheduler::~AbstractScheduler()
{
    delete scheduling_strategy;
    delete data_miner;
}

void AbstractScheduler::preprocessing(int argc, char* argv[], Task* buffer, int *initial_tasks_number) {

    code_preprocessing_master(argc, argv, buffer, initial_tasks_number);
}

void AbstractScheduler::postprocessing() {
    code_postprocessing_master();
}
