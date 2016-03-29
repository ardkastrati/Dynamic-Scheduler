/**
 * This header defines the interface between the scheduler and the scientific code.
 * These function must be provided by the scientific code
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#ifndef SCIENTIFIC_CODE
#define SCIENTIFIC_CODE

#include <string>
#include "TypesExtern.h"

    
void code_postprocessing_master();
    
void code_postprocessing_slave();
    
    /**
     * @param argc
     * @param argv
     */
void code_preprocessing_master(int argc, char* argv[], Task* buffer, int* initial_tasks_number);
    
    /**
     * @param argc
     * @param argv
     */
void code_preprocessing_slave(int argc, char* argv[]);
    
    /**
     * @param task
     */
void code_run_task(Task task, void (*place_tast_forwarder) (void*, Task), void* context);
#endif
