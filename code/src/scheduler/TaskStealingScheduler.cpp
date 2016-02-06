#include "../../lib/easylogging++.h"
#include "TaskStealingScheduler.h"
#include "MpiWinLIFO.h"
#include "../ScientificCode.h"
#include "../worker/TaskStealingWorker.h"

#define WORKING 1
#define FREE 0

TaskStealingScheduler::TaskStealingScheduler(MpiWinSchedulingStrategy* scheduling_strategy, DataMining* data_miner, int rank, int number_of_processors) :
    AbstractScheduler(scheduling_strategy , data_miner, rank, number_of_processors)
{

}
void TaskStealingScheduler::execute(int argc, char* argv[])
{

    MpiWinSchedulingStrategy* scheduler = static_cast<MpiWinSchedulingStrategy*>(scheduling_strategy);



    TaskStealingWorker worker(this);

    if (rank == 0)
    {
        Task tasks[100];
        int number_of_tasks;

        code_preprocessing_master(argc, argv, tasks, &number_of_tasks);
        for (int i = 0; i < number_of_tasks; i++) {
            scheduling_strategy->push_new_task(tasks[i], 0);
        }
    }
    else
    {
        worker.preprocessing(argc, argv);
    }
    while (true) {

        if (is_finish()) {
            LOG(INFO) << "Goodbye: " << this->rank;
            break;
        }
        Task task = scheduling_strategy->pop_next_task();

        if (task.parameter_size > 0) {

            worker.run_task(task);
        } else {
            break;
        }

    }

    if (rank == 0) {
        code_postprocessing_master();
    } else {
        worker.postprocessing();
    }

    //scheduler->free();
}


void TaskStealingScheduler::postprocessing() {
    //AbstractScheduler::postprocessing();
}

void TaskStealingScheduler::run() {

}

bool TaskStealingScheduler::is_finish() {
    return false;
}
