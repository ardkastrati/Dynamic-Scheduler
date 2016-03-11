#include "easylogging++.h"
#include <mpi.h>
#include "Executer.h"
#include <string>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
    LOG(INFO) << "Scheduler started";
    int mpierr;
    mpierr = MPI_Init(&argc, &argv);
    if (mpierr != MPI_SUCCESS)
    {
        LOG(ERROR) << "ERROR: ERROR INITIATING THE MPI ENVIRONMENT, THE PROGRAM WILL ABORT" << std::endl;
        MPI_Abort(MPI_COMM_WORLD, mpierr);
    }


    int rank;
    int number_of_processors;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processors);

    LOG(INFO) << "Rank / Number of processors: " << rank << " / " << number_of_processors;


    //TODO: Argument processing
    Executer* executer = Executer::get_new_executer_by_rank(rank, number_of_processors, "single-queue", "fifo");
    executer->execute(argc, argv);

    delete executer;

    MPI_Finalize();
    LOG(INFO) << rank << " finalized";
    return 0;
}
