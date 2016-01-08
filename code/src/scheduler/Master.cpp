/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "Master.h"
#include "../easylogging++.h"
#include "../ScientificCode.h"

/**
 * Master implementation
 */

Master::Master(SchedulingStrategy* schedulingStrategy) : AbstractScheduler(schedulingStrategy){}

void Master::preprocessing(int argc, char* arcv[], TaskType* buffer, int* initail_tasks_number)
{
    code_preprocessing_master(argc, arcv, buffer, initail_tasks_number);
}

void Master::postprocessing()
{
    code_postprocessing_master();
}

void Master::loop()
{

}

void Master::execute(int argc, char* argv[]){
    LOG(INFO) << "I'am a master";
    TaskType init_tasks[100];
    int init_tasks_number;
    preprocessing(argc, argv, init_tasks, &init_tasks_number);

    for (int i = 0; i < init_tasks_number; i++) {
        schedulingStrategy->push_new_task(init_tasks[i], 1);
    }

    while (schedulingStrategy->get_task_count() != 0) {
        loop();
    }

    postprocessing();
}
