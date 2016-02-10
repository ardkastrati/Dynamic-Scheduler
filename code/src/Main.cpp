/**
 * The main function of the program. This is the entry point.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#define NDEBUG

#include "../lib/easylogging++.h"
#include <mpi.h>
#include "Executor.h"
#include "Types.h"
#include "util/TimeUtility.h"
#include "util/CommandLineParser.h"

INITIALIZE_EASYLOGGINGPP

void create_mpi_task_types();


/**
 * The main function of the dynamic scheduler
 *
 * @param argc command line argument count
 * @param argv command line arguments
 *
 * @return 0 on success
 */
int main(int argc, char* argv[])
{
    long time_started = get_time_in_mirco();
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

    create_mpi_task_types();

    LOG(DEBUG) << "Rank / Number of processors: " << rank << " / " << number_of_processors;

    CommandLineParser parser;
    try {
        parser.parse(argc, argv);
    } catch (const char* msg)
    {
        LOG(ERROR) << msg;
        MPI_Abort(MPI_COMM_WORLD, -1);
    }
    StrategyEnum strategy = parser.get_strategy();
    DesignEnum design = parser.get_design();



    if (design == TASK_STEALING)
    {
        LOG(INFO) << "Run in task-stealing design";
        if (number_of_processors < 2) {

            LOG(INFO) << "You need at least 2 processes for task stealing!";
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
    }
    else if (design == MASTER_WORKER)
    {
        LOG(INFO) << "Run in Master-Worker design";
        if (number_of_processors < 3) {

            LOG(INFO) << "You need at least 3 processes for master worker!";
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
    }

    Executor * executor = Executor::get_new_executor_by_rank(rank, number_of_processors, design ,
    ENUM_FIFO);
    executor->execute(argc, argv);

    delete executor;

    MPI_Finalize();
    long time_end = get_time_in_mirco();
    long time_delta = time_end - time_started;
    double time_delta_sec = ((double) time_delta) / 1000000;
    LOG(DEBUG) << rank << " finalized";
    LOG(INFO) << "Finish! Total runtime: " << time_delta_sec << " seconds";
    return 0;
}



/**
 * Creates own MPI datatypes for communication.
 * Creates MY_MPI_TASK_TYPE for sending Task structures and creates MY_MPI_TASK_DATA_TYPE for sending TaskData structures.
 */
void create_mpi_task_types()
{

    //Create MY_MPI_TASK_TYPE datatype for communication
    mpi_task_type_offsets[0] = offsetof(Task, time_appeared);
    mpi_task_type_offsets[1] = offsetof(Task, parent);
    mpi_task_type_offsets[2] = offsetof(Task, parameter_size);
    mpi_task_type_offsets[3] = offsetof(Task, parameters);

    MPI_Type_create_struct(mpi_task_type_field_count,
                           mpi_task_type_blocklength,
                           mpi_task_type_offsets,
                           mpi_task_type_type,
                           &MY_MPI_TASK_TYPE);

    MPI_Type_commit(&MY_MPI_TASK_TYPE);

    mpi_task_data_type_offset[0] = offsetof(TaskData, time_appeared);
    mpi_task_data_type_offset[1] = offsetof(TaskData, time_started);
    mpi_task_data_type_offset[2] = offsetof(TaskData, time_ended);
    mpi_task_data_type_offset[3] = offsetof(TaskData, event);
    mpi_task_data_type_offset[4] = offsetof(TaskData, mode);
    mpi_task_data_type_offset[5] = offsetof(TaskData, parent);
    mpi_task_data_type_offset[6] = offsetof(TaskData, time_intercommunication_start);
    mpi_task_data_type_offset[7] = offsetof(TaskData, time_intercommunication_end);
    mpi_task_data_type_offset[8] = offsetof(TaskData, rank);
    mpi_task_data_type_offset[9] = offsetof(TaskData, parameter_size);
    mpi_task_data_type_offset[10] = offsetof(TaskData, parameters);

    MPI_Type_create_struct (mpi_task_data_type_field_count,
                            mpi_task_data_type_blocklength,
                            mpi_task_data_type_offset,
                            mpi_task_data_type_type,
                            &MY_MPI_TASK_DATA_TYPE);
    MPI_Type_commit(&MY_MPI_TASK_DATA_TYPE);

}