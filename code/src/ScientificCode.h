/**
 * Project Dynamic Scheduler for Scientific Simulations
 */

#ifndef SCIENTIFIC_CODE
#define SCIENTIFIC_CODE

#include <string>
#include "Types.h"

    
void code_postprocessing_master();
    
void code_postprocessing_slave();
    
    /**
     * @param argc
     * @param argv
     */
void code_preprocessing_master(int argc, char* argv[], TaskType* buffer, int* initial_tasks_number);
    
    /**
     * @param argc
     * @param argv
     */
void code_preprocessing_slave(int argc, char* argv[]);
    
    /**
     * @param task
     */
void code_run_task(TaskType task);
#endif
