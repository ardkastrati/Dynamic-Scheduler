#include "logger.hpp"
#include <mpi.h>
#include "executer.hpp"

static string TAG = "MAIN";

using namespace std;

int main(int argc, char* argv[]) {
    Logger::log(TAG, "Scheduler started", Logger::LEVEL_MED);
    MPI_Init(NULL, NULL);
    int rank;
    int number_of_processors;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processors);
    Logger::log(TAG, "Ich habe die Nummer " + to_string(rank), Logger::LEVEL_HIGH);
    
    Executer* executer = Executer::get_executer_by_rank(rank, number_of_processors);
    (*executer).execute();

    MPI_Finalize();
    return 0;
}
