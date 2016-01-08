/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "Worker.h"
#include "../ScientificCode.h"
/**
 * Worker implementation
 */

void Worker::preporcessing()
{
    code_preprocessing_slave(0, NULL);
}

void Worker::postprocessing()
{
    code_postprocessing_slave();
}

void Worker::run_task(TaskType task)
{
    code_run_task(task);
}

void Worker::wait_for_task() {

}

void Worker::execute(int argc, char* argv[])
{
    preporcessing();
    postprocessing();
}
