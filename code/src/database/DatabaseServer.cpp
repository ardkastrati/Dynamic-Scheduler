#include "DatabaseServer.h"
#include "../easylogging++.h"
#include <mpi.h>
#include "../Const.h"
#include "../Types.h"

DatabaseServer::DatabaseServer(int rank, int number_of_processors) : Executer(rank, number_of_processors)
{

}

void DatabaseServer::execute(int argc, char *argv[])
{
    LOG(INFO) << "Ich bin ein Datenbankserver";
    //run();
}

void DatabaseServer::preprocessing()
{
    TaskType task;
    //MPI_Send();
}

void DatabaseServer::run()
{
    TaskType task;
    MPI_Status status;
    while (true) {
        LOG(INFO) << "Database Running";
        MPI_Recv(&task, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        LOG(INFO) << "Database recv";
        if (status.MPI_TAG == STOP) {
            return;
        }
    }
}
