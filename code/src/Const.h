/**
 * This file defines some constants that are used for MPI communication.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */


/**
 * Tag to indicate that a task should be started.
 */
#define START 1000
/**
 * Tag to indicate that a new task should be placed int the scheduling queue.
 */
#define REQUEST 1001
/**
 * Tag to indicate that a worker finished a scientific task
 */
#define FINISH 1002
/**
 * Tag to indicate that all scientific task are completed and the program should finalize.
 */
#define STOP 1003
/**
 * Tag to indicate that the database server should add the new data entry
 */
#define DATAENTRY 1293
/**
 * Rank of the master
 */
#define MASTER 0
/**
 * Rank of the database server
 */
#define DATABASE 1
/**
 * Tag to indicate a data mining request
 */
#define DATAMINING 192

/**
 * The init task parameter count
 */
 #define MAX_INIT_TASK_COUNT 1000

 /**
  * The max queue size for taskstealing
  */
 #define MAX_MPI_WIN_TASK_COUNT 200000
