/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#include "AbstractWorker.h"
#include "../easylogging++.h"

/**
 * AbstractWorker implementation
 */

AbstractWorker::AbstractWorker(int rank, int number_of_processors) : Executer(rank, number_of_processors)
{

}


/**
 * @param listener
 */
/*void AbstractWorker::register_bookkeeping_listener(void listener) {

}*/

/**
 * @param listener
 */
/*void AbstractWorker::remove_bookkeeping_listener(void listener) {

}*/
