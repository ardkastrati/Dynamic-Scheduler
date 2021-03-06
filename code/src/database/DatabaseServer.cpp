#define NDEBUG

#include "DatabaseServer.h"
#include <mpi.h>
#include "../Const.h"
#include "../TypesExtern.h"
#include "../datamining/grid/GridLibrary.h"
#include "../scheduler/SchedulingStrategy.h"

using namespace std;

DatabaseServer::DatabaseServer(int rank, int number_of_processors) : Executor(rank, number_of_processors)
{
    DataMining_instance_flag = false;
    database_handler = new DatabaseHandler();
}
DatabaseServer::~DatabaseServer()
{
    delete database_handler;
    delete datamining_handler;
}

void DatabaseServer::execute(int argc, char *argv[])
{
    run();
}


void DatabaseServer::run()
{
    TaskData task_data;
    MPI_Status status;

    //database_handler->readStatistic();

    while (true) {

        MPI_Recv(&task_data, 1, MY_MPI_TASK_DATA_TYPE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == STOP) {
            return;
        }
        else if (status.MPI_TAG == DATAENTRY)
        {
        	  //store the new task
            database_handler->storeData(&task_data);

            //insert the new task in datamining
            if(!DataMining_instance_flag)
            {
            	if(task_data.event == 2)
            	{
            		double* initial_parameters;
            		//information of first task
            		long runtime_init = database_handler->dataMiningInquiry()->runtime[0];
            		initial_parameters = &(database_handler->dataMiningInquiry()->para[0]);
            		//if there is no datamining instance yet, create one
            		datamining_handler = new GridDataMining(database_handler, task_data.parameter_size, initial_parameters, &runtime_init, 1);
            		DataMining_instance_flag = true;
            	}


            } else {
            	//ended task = runtime exist, insert in datamining
            	if(task_data.event == 2)
            	{
            		long runtime = task_data.time_ended - task_data.time_started;
            		datamining_handler->insert(task_data.parameters, runtime);
                /*
                long runtimeo = datamining_handler->predict(task_data.parameters);
                cout << "predict: " << runtimeo << std::endl;
                */
            	}
            }
        }
        else if (status.MPI_TAG == DATAMINING) {
          if(!DataMining_instance_flag)
          {
            	if(database_handler->dataMiningInquiry()->runtime.size() != 0)
            	{
            		double* initial_parameters;
            		//information of first task
            		long runtime_init = database_handler->dataMiningInquiry()->runtime[0];
            		initial_parameters = &(database_handler->dataMiningInquiry()->para[0]);
            		//if there is no datamining instance yet, create one
            		datamining_handler = new GridDataMining(database_handler, task_data.parameter_size, initial_parameters, &runtime_init, 1);
            		DataMining_instance_flag = true;

                long runtime = datamining_handler->predict(task_data.parameters);
                //long runtime = 1;
                //cout << "predict: " << runtime << std::endl;
                //send prediction
                int target_rank = status.MPI_SOURCE;
                MPI_Send(&runtime, 1, MPI_LONG, target_rank, DATAMINING, MPI_COMM_WORLD);

            	} else {
                //default value
                long runtime = SchedulingStrategy::DEFAULT_RUNTIME;
                int target_rank = status.MPI_SOURCE;
                MPI_Send(&runtime, 1, MPI_LONG, target_rank, DATAMINING, MPI_COMM_WORLD);
              }
            } else {
              //predict
              long runtime = datamining_handler->predict(task_data.parameters);
              //long runtime = 1;
              //send prediction
              int target_rank = status.MPI_SOURCE;
              MPI_Send(&runtime, 1, MPI_LONG, target_rank, DATAMINING, MPI_COMM_WORLD);
            }
        }
    }
}
