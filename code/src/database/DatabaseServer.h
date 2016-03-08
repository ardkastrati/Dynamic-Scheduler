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
	 * The constructor of the DatabaseServer. Initializes MPI communication and connection to the
	 * Database through DatabaseHandler.
	 * @param rank rank of the MPI node
	 * @param number_of_processors
	 */
    DatabaseServer(int rank, int number_of_processors);

    /*
     * Destructor of the DatabaseServer.
     */
    ~DatabaseServer();

    /*
     * Begins the execution of the DatabaseServer.
     */
    void execute(int argc, char* argv[]);

private:

    /**
     * A flag to show if an instance of the DataMining modul exists yet.
     */
    bool DataMining_instance_flag;

    /*
     * Instance of a DatabaseHandler
     */
    DatabaseHandler*  database_handler;

    /*
     * Instance of a DataminingHandler
     */
    GridDataMining*  datamining_handler;

    /*
     * Runs during the execution and contains the communication over MPI.
     * It receives data asynchronous and inserts the information of each task in the Database.
     *
     */
    void run();

};

#endif // DATABASESERVER_H
