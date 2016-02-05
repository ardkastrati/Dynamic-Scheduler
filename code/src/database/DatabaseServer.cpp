#include "DatabaseServer.h"
#include "../../lib/easylogging++.h"
#include <mpi.h>
#include "../Const.h"
#include "../TypesExtern.h"

DatabaseServer::DatabaseServer(int rank, int number_of_processors) : Executor(rank, number_of_processors)
{

}

void DatabaseServer::execute(int argc, char *argv[])
{
    LOG(INFO) << "Ich bin ein Datenbankserver";
    //run();
}

void DatabaseServer::preprocessing()
{
    Task task;
    //MPI_Send();
}

void DatabaseServer::run()
{
    Task task;
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
