// dummy code simulator test //
#include "scheduler.c"


#define MASTER 0
#define MAX_WEIGHT 80
#define MAX_ADDS 20

#define LOGGER_IS_ON 1
char local_log[255];
FILE * local_log_file;


double global_runtime;
double my_worktime;

int total_additions;
int my_max_adds;

void code_preprocessing_master(int argc, char *argv[], task_type *initial_tasks, int * initial_tasks_number )
{
    int  rank, num_proc;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    //if(LOGGER_IS_ON==1)
    {
        /* echo some info data for each rank */
        sprintf(local_log, "local-log-r%06d", rank);
        local_log_file = fopen(local_log,"a");
        fprintf( local_log_file, "[%f] Master: Starting computation,\n", MPI_Wtime());
        fclose(local_log_file);
    }

    total_additions=0; // number of tasks added on this proc
    my_worktime = 0; // time of WORKING only - calculated within the run_task
    my_max_adds = MAX_ADDS; //max number of tasks added on this proc

    stat_task_params[0]=0;
    //in this example there is only one task at the beginning
/*
    double task_param_1, task_param_2;

    // take the initial tasks parameters from the input file
    // do it on one process only, then broadcast to others
    // in order to avoid concurrent file access

    //Reading the Command line Arguments
    if(argc<2)
    {
        fprintf( stderr, "Input file schould be specified \n" );
        MPI_Finalize();
        exit(1);
    }
    else
    {
        strcpy(input_fname,argv[1]);
        fprintf( stderr, "\nFor inputs the FILE \"%s\" will be used\n",input_fname);

        //Read parameters from input file.
        read_input(&task_param_1,&task_param_2,input_fname);
    }

    // Broadcasting the name of steering file to all slaves
    MPI_Bcast(input_fname, 255, MPI_CHAR, MASTER, MPI_COMM_WORLD);
    // Broadcasting the first param to all slaves
    MPI_Bcast(&task_param_1, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    // Broadcasting the second param to all slaves
    MPI_Bcast(&task_param_2, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

    initial_tasks[0][0] = task_param_1;
    initial_tasks[0][1] = task_param_2;
*/

    //in this example there is only one task at the beginning
    // we define its params right here in code
    // normally it is taken fron a file or from batch params
    initial_tasks_number[0]=1;

    initial_tasks[0][0] = MAX_WEIGHT;
    initial_tasks[0][1] = MPI_Wtime();

    global_runtime = MPI_Wtime(); // start counting global total runtime from here
}

void code_preprocessing_slave(int argc, char *argv[])
{
    int  rank, num_proc;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    stat_task_params[0]=0;

   //if(LOGGER_IS_ON==1)
    {
        /* echo some info data for each rank */
        sprintf(local_log, "local-log-r%06d", rank);
        local_log_file = fopen(local_log,"a");
        fprintf( local_log_file, "[%f] Slave: Starting computation,\n", MPI_Wtime());
        fclose(local_log_file);
    }

    total_additions=0; // number of tasks added on this proc
    my_worktime = 0; // time of WORKING only - calculated within the run_task
    srand(time(NULL));
    my_max_adds = rand()%MAX_ADDS + 1; //max number of tasks added on this proc


/*
    recieve necessary params from MASTER
    // Broadcasting the name of steering file to all slaves
    MPI_Bcast(input_fname, 255, MPI_CHAR, MASTER, MPI_COMM_WORLD);
    // Broadcasting the first param to all slaves
    MPI_Bcast(&task_param_1, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    // Broadcasting the second param to all slaves
    MPI_Bcast(&task_param_2, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
*/
}

void code_postprocessing_master()
{
    int  rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    fprintf( stderr, "Process %d worked %f\n", rank, my_worktime );

    MPI_Barrier(MPI_COMM_WORLD); // by that time all have finished

    global_runtime = MPI_Wtime() - global_runtime;
    fprintf( stderr, "Global total worktime = [%f] \n", global_runtime );
}

void code_postprocessing_slave()
{
    int  rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    fprintf( stderr, "Process %d worked %f\n", rank, my_worktime );

    MPI_Barrier(MPI_COMM_WORLD); // by that time all have finished

}

void pretend_that_you_work(double idle_time)
{
    int i, r1, r2;
    double r3, seed, res;

    for(i=0; i<100000*(idle_time); i++)
    {
        srand(time(NULL));
        r1 = rand();
        r2 = rand();
        r3 = rand()/r1+ r1/r2;
        seed = r1*r2 + r2*r3 + r1*r3;
        res = seed/rand();
    }
}


void run_task(task_type task0, result_type * result0)
{
    int rank, num_proc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    int t1, t2, ttt;
    ttt=0;
    double t_wrk;

    srand(time(NULL));

    //if(LOGGER_IS_ON==1)
    {
        local_log_file = fopen(local_log,"a");
        fprintf( local_log_file, "\n[%f] Working... task params [%3.1f][%6.4f]...\n", MPI_Wtime(), task0[0], task0[1]);
        fclose(local_log_file);
    }

    t_wrk = MPI_Wtime();
    result0[0][0] = t_wrk/rand();

    int num_adds, i;

    num_adds = rand()%(MAX_ADDS/10+1)+1;

    //if(LOGGER_IS_ON==1)
    {
        local_log_file = fopen(local_log,"a");
        fprintf( local_log_file, "num adds %d, max adds %d, prevoiusly added %d\n", num_adds, my_max_adds, total_additions);
        fclose(local_log_file);
    }

    if(total_additions>my_max_adds) num_adds=0;
    total_additions+=num_adds;

    double working_period = task0[0]/(num_adds+1); // share the work
    // work - add new task - work - add new task - work etc
    // the working period here linearly depends on the firs param of the task
    pretend_that_you_work(working_period);

    task_type task1;
    for (i=0; i<num_adds; i++)
    {        
        //srand(time(NULL));
        task1[0] = rand()%MAX_WEIGHT + 1; // each new added task is smaller then previous
        task1[1] = rand() + MAX_WEIGHT/rand();

        //if(LOGGER_IS_ON==1)
        {
            local_log_file = fopen(local_log,"a");
            fprintf( local_log_file, "[%f] New task! Params [%3.1f][%6.4f]\n", MPI_Wtime(), task1[0], task1[1]);
            fclose(local_log_file);
        }

        place_task(task1, rank);

        pretend_that_you_work(working_period);
    }

    result0[0][1] = MPI_Wtime();
    result0[0][2] = rand()/t_wrk;

    //if(LOGGER_IS_ON==1)
    {
        local_log_file = fopen(local_log,"a");
        fprintf( local_log_file, "[%f] I worked for [%f] \n\n", MPI_Wtime(), MPI_Wtime()-t_wrk);
        fclose(local_log_file);
    }

    my_worktime += MPI_Wtime()-t_wrk;

    // the result here is a set of randoms

}


