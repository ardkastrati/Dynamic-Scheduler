/**
 * Implementation of 'DataMining' Superclass.
 * GridDataMining creates a multi-dimensional array (with each parameter as dimension) used to predict the runtime of future tasks.
 * The virtual 'grid points' are set according to the closest tasks previously executed.
 */


#ifndef _GRIDDATAMINING_H
#define _GRIDDATAMINING_H


#include "../DataMining.h"
#include "MpiProxy.h"
#include "ArrayHandler.h"

#include "../../database/DatabaseHandler.h"

class GridDataMining : public DataMining {
private:
	DatabaseHandler* database;
	/**
	 * The nr of dimensions of the virtual multi-dimensional array.
	 */
	int nr_of_dimensions;
	/**
	 * Number of tasks already inserted in the grid.
	 */
	int nr_of_tasks;
	/**
	 * True during the grid is recreated.
	 */
	bool make_new_grid_running;
	/**
	 * The maximum of the parameters of the tasks already inserted.
	 */
	double* max_parameter;
	/**
	 * The minimum of the parameters of the task already inserted.
	 */
	double* min_parameter;
	/**
	 * The average deviation between the predicted runtime and the actual runtime of all tasks already executed.
	 */
	double average_deviation;
	/**
	 * The maximum average deviation allowed before a new grid is created.
	 */
	double max_deviation_time;
	/**
	 * The ArrayHandler managing the data access.
	 */
	ArrayHandler* memory;
	/**
	 * The MpiProxy manages the communication between MPI and the grid.
	 */
	MpiProxy* proxy;
	/**
	 * Inserts a task into the grid.
	 * Unlike the normal insert every grid point might get adapted instead of only the surrounding.
	 * @param parameter the parameter of the task
	 *				 must be nr_of_dimensions long
	 *				 must not be NULL
	 * @param time the new time of the task
	 *				 must not be negative
	 */
	void hard_insert(double* parameters, long runtime);
	/**
	 * Creates a new grid and inserts every task ever executed.
	 */
	void make_new_grid();
	/**
 	 * Updates the min and max parameter vectors and the average_deviation.
 	 * @param parameter the parameter of the task
 	 *				must be nr_of_dimensions long
 	 *				must not be NULL
 	 * @param time the new time of the task
 	 *				must not be negative
 	 */
	void grid_bookkeping(double* parameters, long runtime);
	/**
	 * Checks whether the grid must get recreated.
	 * @return true if the grid must be recreated false if the grid is good or the grid is recreated right know
	 */
	bool check_for_update();
public:
	/**
	 * Grid constructor.
	 * Creates an ArrayHandler and a MpiProxy.
	 * @param rank in the MPI World
	 * @param target_rank the MPI rank of the GridDataMininer that holds the MPI SharedMemory
	 * @param database holds all task that ever ran
	 * @param nr_of_dimensions the nr of dimensions of the virtual multi-dimensional array
	 * @param initial_tasks_parameter a array with the parameter of the initial task
	 * 				must be initial_task_count * nr_of_dimensions long
	 * @param initial_task_runtime a array with the runtime of the initial task
	 *				must be initial_task_count long
	 * @param initial_task_count the number of initial task
	 *				must be greater than zero
	 */
	GridDataMining(int rank, int target_rank, DatabaseHandler* database, int parameter_count, double* initial_tasks_parameter, long* initial_task_runtime, int initial_task_count);
	/**
	 * Destructor
	 */
	~GridDataMining();
	/**
	 * Predicts a given task's runtime.
	 * @param parameter the parameter of the task
 	 *				must be nr_of_dimensions long
 	 *				must not be NULL
	 */
	long predict(double* parameters);
	/**
	 * Inserts an executed task into the grid.
	 * @param parameter the parameter of the task
 	 *				must be nr_of_dimensions long
 	 *				must not be NULL
 	 * @param time the new time of the task
 	 *				must not be negative
 	 */
	void insert(double* parameters, long runtime);
};

#endif //_GRIDDATAMINING_H
