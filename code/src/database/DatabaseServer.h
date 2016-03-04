#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include "../Executor.h"
#include "DatabaseHandler.h"
#include "../datamining/grid/GridDataMining.h"
#include "../datamining/DataMining.h"

class DatabaseServer: public Executor
{
public:

	/*
	 * The constructor of the DatabaseServer, initialize MPI communication and connection to the
	 * Database through DatabaseHandler.
	 * @param rank rank of
	 * @param number_of_processor
	 */
    DatabaseServer(int rank, int number_of_processors);

    /*
     * The destructor
     */
    ~DatabaseServer();

    /*
     * The function starts the execution of the DatabaseServer.
     */
    void execute(int argc, char* argv[]);

private:

    /**
     * A flag to show if an instance of the DataMining modul exist yet.
     */
    bool DataMining_instance_flag;

    /*
     * Instance of a DatabaseHandler
     */
    DatabaseHandler*  database_handler;

    /*
     * Instance of a DatabaseHandler
     */
    GridDataMining*  datamining_handler;

    /*
     * The run function is running during the execution and contains the communication over MPI.
     * It receives data asynchronous and insert the information of each task in the Database.
     *
     */
    void run();

};

#endif // DATABASESERVER_H
