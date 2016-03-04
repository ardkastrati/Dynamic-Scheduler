#define NDEBUG

#include "DatabaseServer.h"
#include <mpi.h>
#include "../Const.h"
#include "../TypesExtern.h"


DatabaseServer::DatabaseServer(int rank, int number_of_processors) : Executor(rank, number_of_processors)
{
    DataMining_instance_flag = false;
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
        else if (status.MPI_TAG == DATAMINING) {


//int rank, int target_rank, DatabaseHandler* database, int parameter_count, double* initial_tasks_parameter, long* initial_task_runtime, int initial_task_count
            if(!DataMining_instance_flag)
	    {
	    	//datamining_handler = new GridDataMining(0, 0, database_handler, 2 , );
	        DataMining_instance_flag = true;
            }
	    
            int target_rank = status.MPI_SOURCE;
            long runtime = 10;
            MPI_Send(&runtime, 1, MPI_LONG, target_rank, DATAMINING, MPI_COMM_WORLD);
        }
    }
}
