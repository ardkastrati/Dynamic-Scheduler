/**
 * The main function of the program. This is the entry point.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#include "../lib/easylogging++.h"
#include <mpi.h>
#include "Executor.h"
#include "Types.h"

INITIALIZE_EASYLOGGINGPP

void create_mpi_task_type();
void parse_command_line_parameters(int argc, char* argv[], char*);

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

    create_mpi_task_type();

    LOG(INFO) << "Rank / Number of processors: " << rank << " / " << number_of_processors;

    //TODO: Argument processing
    Executor * executer = Executor::get_new_executor_by_rank(rank, number_of_processors, "single-queue", "fifo");
    executer->execute(argc, argv);

    delete executer;

    MPI_Finalize();
    LOG(INFO) << rank << " finalized";
    return 0;
}



/**
 * Creates own MPI datatypes for communication.
 * Creates MY_MPI_TASK_TYPE for sending Task structures and creates MY_MPI_TASK_DATA_TYPE for sending TaskData structures.
 */
void create_mpi_task_type()
{

    //Create MY_MPI_TASK_TYPE datatype for communication
    mpi_task_type_offsets[0] = offsetof(Task, parameter_size);
    mpi_task_type_offsets[1] = offsetof(Task, parameters);

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