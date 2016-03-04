#define NDEBUG

#include "DatabaseServer.h"
#include "../../lib/easylogging++.h"
#include <mpi.h>
#include "../Const.h"
#include "../TypesExtern.h"


DatabaseServer::DatabaseServer(int rank, int number_of_processors) : Executor(rank, number_of_processors)
{
    database_handler = new DatabaseHandler();
    //datamining_handler = new GridDataMining();
    //dataminer?
	//init
}
DatabaseServer::~DatabaseServer()
{
    //LOG(DEBUG) << "Destructor DatabaseServer";
    delete database_handler;
    //destruct rest
}

void DatabaseServer::execute(int argc, char *argv[])
{
    //LOG(DEBUG) << "Ich bin ein Datenbankserver";
    run();
}


void DatabaseServer::run()
{

	//temporärer thread für dataminer?
    TaskData task_data;
    MPI_Status status;
    while (true) {
        MPI_Recv(&task_data, 1, MY_MPI_TASK_DATA_TYPE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (status.MPI_TAG == STOP) {
            return;
        }
        else if (status.MPI_TAG == DATAENTRY)
        {
            database_handler->storeData(&task_data);
            //insert(&task_data);
            //clear data
            //LOG(DEBUG) << "Stored: " << task_data.parameters[0];
        }
    }
}
