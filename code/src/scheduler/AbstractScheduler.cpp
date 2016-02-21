#define NDEBUG

#include "AbstractScheduler.h"
#include "../ScientificCode.h"
//#include "../../lib/easylogging++.h"
#include <assert.h>

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
    //LOG(DEBUG) << "Destructor AbstractScheduler";
}

void AbstractScheduler::preprocessing(int argc, char* argv[], Task* buffer, int *initial_tasks_number) {
    assert(argc > 0);
    assert(argv != NULL);
    assert(buffer != NULL);
    assert(initial_tasks_number != NULL);

    code_preprocessing_master(argc, argv, buffer, initial_tasks_number);
}

void AbstractScheduler::postprocessing() {
    code_postprocessing_master();
}

void AbstractScheduler::place_task(Task task)
{
    long runtime = 1;//scheduling_strategy->DEFAULT_RUNTIME;
    if (scheduling_strategy->is_statistic_based()) {
        //TODO: Uncomment line
        //runtime = data_miner->predict(task.parameters);
    }
    scheduling_strategy->push_new_task(task, runtime);
}

int AbstractScheduler::get_rank()
{
    return this->rank;
}