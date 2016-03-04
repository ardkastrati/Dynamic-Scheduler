/**
 * This header defines extern the own data types, that are used in the project
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#ifndef TYPES_EXTERN
#define TYPES_EXTERN

#define PARAMTER_LENGTH 100

#include <vector>
#include <mpi.h>


typedef struct _StatisticInquiry {
	int parameter_size;
	std::vector<long> runtime;
	std::vector<double> para;
} StatisticInquiry;

typedef struct _Task {
	long id;
    long time_appeared;
	long runtime;
    long parent;
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
    long parent;
    int time_intercommunication_start;
    int time_intercommunication_end;
    int rank;
    int parameter_size;
    double parameters[PARAMTER_LENGTH];
} TaskData;

extern const int mpi_task_data_type_field_count;
extern int mpi_task_data_type_blocklength[12];
extern MPI_Datatype mpi_task_data_type_type[12];
extern MPI_Datatype MY_MPI_TASK_DATA_TYPE;

extern MPI_Aint mpi_task_data_type_offset[12];

extern const int mpi_task_type_field_count;

extern int mpi_task_type_blocklength[6];
extern MPI_Datatype mpi_task_type_type[6];

extern MPI_Datatype MY_MPI_TASK_TYPE;

extern MPI_Aint mpi_task_type_offsets[6];

extern MPI_Comm MY_MPI_COMM_TASKSTEALING;

#define MAX_INIT_TASKS 100
#endif // TYPES_EXTERN
