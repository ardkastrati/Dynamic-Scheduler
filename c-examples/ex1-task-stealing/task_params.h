// here is our task structure
// let us simplify it to the array of type
int task_type_length=2;
typedef double task_type_unit;
typedef double task_type[2];
// MPI has own types here - need to be defined
MPI_Datatype mpi_task_type_unit=MPI_DOUBLE;

// here are the numbers of task params, that will be used for statistics
// c counter from 0 to n-1 is used
int num_stat_task_params = 1;
int stat_task_params[1]; // we use only first param for stats

// here is our result structure
// the result is returned at the end of each run_task
// all results should be accumulated during the computation or at the end of it
// in a: single file/ database/ multiple files/ ???
int result_type_length=3;
typedef double result_type_unit;
typedef double result_type[3];



