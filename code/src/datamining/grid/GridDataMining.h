/**
 * Project Dynamic Scheduler for Scientific Simulations
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
	 * the nr of dimensions of the virtal mulitdimenisonal array
	 */
	int nr_of_dimensions;
	/**
	 * number of tasks that are in the Grid
	 */
	int nr_of_tasks;
	/**
	 * is true when the Grid is recreated
	 */
	bool make_new_grid_running;
	/**
	 * the maximun of the parameters of the task that are insertet yet
	 */
	double* max_parameter;
	/**
	 * the minimun of the parameters of the task that are insertet yet
	 */
	double* min_parameter;
	/**
	 * the average differenz between the prediction and the real time the task had taken
	 */
	double average_differential;
	/**
	 * the maximun average differenz
	 */
	double max_differential_time;
	/**
	 * the ArrayHandler that manage the communikation between the GridDataMininer and the data
	 */
	ArrayHandler* memory;
	/**
	 * the MpiProxy manage the communikation between MPI and the Grid
	 */
	MpiProxy* proxy;
	/**
	 * inserts a task into the Grid but different from the normal insert every Gridpoint is checked instead of the surrounding
	 * @param parameter the parameter of the task
	 *				 musst be nr_of_dimensions long
	 *				 musst not be NULL
	 * @param time the new time of the task
	 *				 musst not be negativ
	 */
	void hard_insert(double* parameters, long runtime);
	/**
	 * creates a new Grid and inserts every task that erver ran
	 */
	void make_new_grid();
	/**
 	 * update the min and max parameter vektors and the average_differential
 	 * @param parameter the parameter of the task
 	 *				musst be nr_of_dimensions long
 	 *				musst not be NULL
 	 * @param time the new time of the task
 	 *				musst not be negativ
 	 */
	void grid_bookkeping(double* parameters, long runtime);
	/**
	 * check if the Grid musst be recreated
	 * @return true if the grid musst be recreated false if the grid is good or the grid is recreated right know
	 */
	bool check_for_update();
public:
	/**
	 * Grid Konstruktor create a ArrayHandler and a MpiProxy
	 * @param rank in the MPI World
	 * @param target_rank the MPI rank of the GridDataMininer that holds the MPI SharedMemory
	 * @param database holds all task that ever ran
	 * @param nr_of_dimensions the nr of dimensions of the virtal mulitdimenisonal array
	 * @param initial_tasks_parameter a array with the parameter of the initial task
	 * 				musst be initial_task_count * nr_of_dimensions long
	 * @param initial_task_runtime a array with the runtime of the initial task
	 *				musst be initial_task_count long
	 * @param initial_task_count the number of initial task
	 *				musst be bigger than zero
	 */
	GridDataMining(int rank, int target_rank, DatabaseHandler* database, int parameter_count, double* initial_tasks_parameter, long* initial_task_runtime, int initial_task_count);
	/**
	 * Deconstructor
	 */
	~GridDataMining();
	/**
	 * predict a given task
	 * @param parameter the parameter of the task
 	 *				musst be nr_of_dimensions long
 	 *				musst not be NULL
	 */
	long predict(double* parameters);
	/**
	 * insert a ran task into the grid
	 * @param parameter the parameter of the task
 	 *				musst be nr_of_dimensions long
 	 *				musst not be NULL
 	 * @param time the new time of the task
 	 *				musst not be negativ
 	 */
	void insert(double* parameters, long runtime);
};

#endif //_GRIDDATAMINING_H
