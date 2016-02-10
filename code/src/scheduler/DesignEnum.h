/**
 * This enum contains all designs that the scheduler provides.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#ifndef CODE_DESIGNENUM_H
#define CODE_DESIGNENUM_H


enum DesignEnum {
    /**
     * The task stealing design uses a peer to peer communication.
     * One process is used as database server. The other processes are independent scheduler with own queues.
     * The scheduler tries to pop the next task from their own queue. If the queue is empty the scheduler steals a task
     * from an other scheduler using MPI one site communication.
     */
    TASK_STEALING,

    /**
     * The master worker design uses a central control unit: the master.
     * One process ist used as database server, one process is used as master and the other processes are Worker executor.
     * The master has a scheduling queue and distribute the scientific tasks to free workers.
     * Workers execute the scientific task and send new tasks back to the master.
     * Workers also send non-blocking messages to the database server to insert bookkeeping and statistic information.
     */
    MASTER_WORKER
};


#endif //CODE_DESIGNENUM_H
