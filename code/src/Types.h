#ifndef TYPES
#define TYPES

#define PARAMTER_LENGTH 100

#include <mpi.h>

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
    long time_appeared;
    int parent;
    int parameter_size;
    double parameters[PARAMTER_LENGTH];
} Task;

typedef struct _TaskData {
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

const int mpi_task_data_type_field_count = 11;
int mpi_task_data_type_blocklength[11] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, PARAMTER_LENGTH};
MPI_Datatype mpi_task_data_type_type[11] = {MPI_LONG,
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

MPI_Aint mpi_task_data_type_offset[11];



const int mpi_task_type_field_count = 4;

int mpi_task_type_blocklength[4] = {1, 1, 1, PARAMTER_LENGTH};
MPI_Datatype mpi_task_type_type[4] = {MPI_LONG,MPI_INT, MPI_INT, MPI_DOUBLE};

MPI_Datatype MY_MPI_TASK_TYPE;

MPI_Aint mpi_task_type_offsets[4];


MPI_Comm MY_MPI_COMM_TASKSTEALING;
#define MAX_INIT_TASKS 100
#endif // TYPES
