/**
 * This header defines the own data types, that are used in the project
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#ifndef TYPES
#define TYPES

#define PARAMTER_LENGTH 100

#include <mpi.h>
#include <vector>

//typedef int TaskType;
/*struct _TaskType {
    int parameter_size;
    double parameters[MAX_PARAMTER_LENGTH];
    int important_parameters_size;
    int index_important_parameters[int important_parameters_size][abc]

    //sum from i = 0 to c (a+b*i)
} TaskType;*/

typedef struct _StatisticInquiry {
	int parameter_size;
	std::vector<long> runtime;
	std::vector<double> para;
} StatisticInquiry;

typedef struct _Task {
	long id;
    long time_appeared;
	long runtime;
    int parent;
    int parameter_size;
    double parameters[PARAMTER_LENGTH];
} Task;

typedef struct _TaskData {
	long id;
    long time_appeared;
    long time_started;
    long time_ended;
    int event;
    int mode;
    int parent;
    int time_intercommunication_start;
    int time_intercommunication_end;
    int rank;
    int parameter_size;
    double parameters[PARAMTER_LENGTH];
} TaskData;

const int mpi_task_data_type_field_count = 12;
int mpi_task_data_type_blocklength[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, PARAMTER_LENGTH};
MPI_Datatype mpi_task_data_type_type[12] = {MPI_LONG,
											MPI_LONG,
                                            MPI_LONG,
                                            MPI_LONG,
                                            MPI_INT,
                                            MPI_INT,
                                            MPI_INT,
                                            MPI_INT,
                                            MPI_INT,
                                            MPI_INT,
                                            MPI_INT,
                                            MPI_DOUBLE};
MPI_Datatype MY_MPI_TASK_DATA_TYPE;

MPI_Aint mpi_task_data_type_offset[12];



const int mpi_task_type_field_count = 6;

int mpi_task_type_blocklength[6] = {1, 1, 1, 1, 1, PARAMTER_LENGTH};
MPI_Datatype mpi_task_type_type[6] = {MPI_LONG, MPI_LONG, MPI_LONG,MPI_INT, MPI_INT, MPI_DOUBLE};

MPI_Datatype MY_MPI_TASK_TYPE;

MPI_Aint mpi_task_type_offsets[6];


MPI_Comm MY_MPI_COMM_TASKSTEALING;
#define MAX_INIT_TASKS 100
#endif // TYPES
