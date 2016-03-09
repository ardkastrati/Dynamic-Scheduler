#ifndef _ABSTRACTSCHEDULER_H
#define _ABSTRACTSCHEDULER_H

#include "SchedulingStrategy.h"
#include "../datamining/DataMining.h"
#include "../Executor.h"
#include "SchedulingStrategyEvaluator.h"

/**
 * The abstract AbstractScheduler class is the base class for all types of scheduler objects like master-worker scheduler
 * or task stealing scheduler and inherits from the Executor class. Subclasses have to override the run() and the is_finish() function.
 * The preprocessing and the postprocessing functions call the code_preprocessing_master() and the code_postprocessing_master()
 * functions on the code interface.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */
class AbstractScheduler: public Executor {
protected:
    /**
     * Will be incremented when a new task appears.
     */
    int task_number = 0;
    /**
     * The current scheduling strategy of the scheduler.
     */
    SchedulingStrategy* scheduling_strategy;

    /**
     * The current data_miner of the scheduler.
     */
    DataMining* data_miner;

    /**
     * The current scheduling strategy evaluator of the scheduler.
     */
    SchedulingStrategyEvaluator* schedulingStrategyEvaluator;


    /**
     * This function is called before the master starts the scheduling of the
     * scientific tasks. This function calls the scientific code_preprocessing_master() code.
     * @param argc command line argument count. Must not be negative
     * @param argv command line arguments. Must not be NULL
     * @param buffer buffer where the scientific code can store the initial tasks. Must not be NULL!
     * @param initial_tasks_number the count of initial tasks. Must not be NULL!
     */
    virtual void preprocessing(int argc, char* argv[], Task* buffer, int* initial_tasks_number);

    /**
     * This function is called after all scientific tasks are completed.
     * This function calls the scientific code_postprocessing_master() code.
     */
    virtual void postprocessing();

    /**
    * The main loop of the master - worker algorithm.
    * The function returns after all scientific tasks are completed.
    */
    virtual void run() = 0;

    /**
     * Checks whether all scientific tasks are completed.
     * All tasks completed <=> free_worker == worker_count && tasksqueue is empty.
     *
     * @return TRUE if all scientific tasks are completed
     */
    virtual bool is_finish() = 0;

public:
    /**
     * Initializes the fields of the abstract scheduler.
     * This constructor is called from the subclass constructors.
     *
     * @param scheduling_strategy the scheduling strategy to be set
     * @param data_mining the data miner to be set
     * @param rank the MPI rank of the processors, that execute the scheduler
     * @param number_of_processors the total number of processors of the MPI world
     */
    AbstractScheduler(SchedulingStrategy* scheduling_strategy,
        DataMining* data_miner, int rank, int number_of_processors);
    /**
     * Deletes the scheduling_strategy and data_miner object.
     */
    virtual ~AbstractScheduler();

    virtual void place_task(Task task);

    /**
     * Returns the rank of the scheduler.
     *
     * @return the rank of the scheduler
     */
    int get_rank();
};

#endif //_ABSTRACTSCHEDULER_H
