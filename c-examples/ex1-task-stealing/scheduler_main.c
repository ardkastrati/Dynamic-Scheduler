// task stealing via MPIRemote memory access //
// dummy test //

#include "code.c"

#define QUEUE_SIZE 1024
#define MAX_INI_TASKS 5000

int zero_val;
int disp_unit;
int first;

int main( int argc, char *argv[] )
{
    int  rank, num_proc, mpierr;
    int i;

    // initialize the mpi environment
    mpierr = MPI_Init(&argc, &argv);
    if(mpierr!= MPI_SUCCESS)
    {
        printf("ERROR: ERROR INITIATING THE MPI ENVIRONMENT, THE PROGRAM WILL ABORT\n");
        MPI_Abort(MPI_COMM_WORLD,mpierr);
    }

    // from now on, the code is done BY ALL the processes the same
    // if you want one process do a specific function, manipulate with its rank

    // get the rank of the current processer and the total number of them
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    task_type initial_tasks[MAX_INI_TASKS];
    int initial_tasks_number;

    //if(ts_logging==1)
    {
        /* echo some info data for each rank */
        sprintf(sched_log, "sched-log-r%06d", rank);
        sched_log_file = fopen(sched_log,"a");
        fprintf( sched_log_file, "Let the game begin!!\n");
        fclose(sched_log_file);
    }


    //initialize scheduler
    zero_val = 0;
    lock = -2;
    first = 1;
    disp_unit = sizeof( task_type );


    MPI_Aint size = QUEUE_SIZE * disp_unit; // the size of the RMA window for the QUEUE on each process
    MPI_Aint size0 = sizeof(int); // the size of the halp RMA windows for offsets and for statuses

    MPI_Alloc_mem(size, MPI_INFO_NULL, &QUEUE);
    MPI_Alloc_mem(size0, MPI_INFO_NULL, &OFFSET);
    MPI_Alloc_mem(size0, MPI_INFO_NULL, &STATUS);



    /* create an MPI memory window   */
    /* for Remote Memory Access      */
    MPI_Win_create( QUEUE, size, disp_unit, MPI_INFO_NULL, MPI_COMM_WORLD, &win_q );
    MPI_Win_create( OFFSET, size0, disp_unit, MPI_INFO_NULL, MPI_COMM_WORLD, &win_offs );
    MPI_Win_create( STATUS, size0, disp_unit, MPI_INFO_NULL, MPI_COMM_WORLD, &win_status );


    // lets start the game
    // run the preprocessing of the code - recieve information about initial tasks
    if(rank == 0)
    {
        code_preprocessing_master(argc, argv, initial_tasks, &initial_tasks_number);

        sched_log_file = fopen(sched_log,"a");
        for(i=0; i<initial_tasks_number; i++)
        {
            fprintf( sched_log_file, "Task %d: [%f][%f];\n", i, initial_tasks[i][0], initial_tasks[i][1]);
        }
        fclose(sched_log_file);
    }
    else
    {
        code_preprocessing_slave(argc, argv);
    }

    // now place the tasks recieved on preprocessing stage to the queue(s)
    // in this example I simply put them to master's queue
    OFFSET[0] = -1; // no tasks nowhere yet

    if(rank == 0)
    {
        for(i=0; i<initial_tasks_number; i++)
        {
            place_task(initial_tasks[i], rank);
        }
    }

    task_type task0;
    result_type result0;
    int accumulated_status=1; // variable is used to keep the number of non-idle processes
                              // if all processes are idle - is set to 0;
    int target_rank;
    int empty;
    int working_status = 1;
    int idle_status = 0;

    int my_status=1; // set working status as default
    STATUS[0]=1;

    char local_res[255];
    sprintf(local_res, "local-res-r%06d.csv", rank);
    FILE * local_res_file;

    // here goes the task stealing cycle as showed in PSE-Scheduling.pdf, slide 11
    // HERE GOES THE TASK STEALING CYCLE
    while(accumulated_status>0)
    {
        //try own QUEUE
        //if(ts_logging==1)
        {
            sched_log_file = fopen(sched_log,"a");
            fprintf( sched_log_file, "Trying own q!!\n");
            fclose(sched_log_file);
        }
        empty = 0;
        target_rank = rank; //SELF cycle
        while(empty == 0)
        {
            empty = read_last_task_own(&(task0[0]), target_rank);

            if(empty == 0)
            {
                if(my_status==0) //change own status if necessary
                {
                    set_status(working_status, rank);

                    my_status=1;
                    //if(ts_logging==1)
                    {
                        sched_log_file = fopen(sched_log,"a");
                        fprintf( sched_log_file, "[%f] I am working!\n", MPI_Wtime());
                        fclose(sched_log_file);
                    }
                }

                //if(ts_logging==1)
                {
                    sched_log_file = fopen(sched_log,"a");
                    fprintf( sched_log_file, "[%f] How-how-how! I have work [%3.1f][%6.4f] to DO!\n", MPI_Wtime(), task0[0], task0[1]);
                    fclose(sched_log_file);
                }

                run_task(task0, &result0);
                //if(ts_logging==1)
                {
                    sched_log_file = fopen(sched_log,"a");
                    fprintf( sched_log_file, "[%f] Work is done, my master!\n\n", MPI_Wtime());
                    fclose(sched_log_file);
                }
                // here you have to organize the results collection, i.e. placing in a database
                // in this example I simply place the results on each process in a single cumulative .csv file
                local_res_file = fopen(local_res,"a");
                for(i=0; i<task_type_length; i++)
                {
                    fprintf( local_res_file, "%f;", task0[i]);

                }
                for(i=0; i<result_type_length; i++)
                {
                    fprintf( local_res_file, "%f;", result0[i]);
                }
                fprintf( local_res_file, "\n");
                fclose(local_res_file);
            }
            else
            {
                //if(ts_logging==1)
                {
                    sched_log_file = fopen(sched_log,"a");
                    fprintf( sched_log_file, "[%f] SELF nothing ....\n\n", MPI_Wtime());
                    fclose(sched_log_file);
                }
                empty = 1;
            }
        }

        int fail_cntr=0;

        while((empty>0) && (accumulated_status>0))
        {
            target_rank=((rank+1)>=num_proc)?0:(rank+1);
            int cntr;

            for(cntr=0; (cntr<num_proc-1) && (empty>0); cntr++) // cycle: all other processors;
            {
                empty = read_last_task(task0, target_rank, 0);

                if(empty == 0)
                {
                    if(my_status==0)
                    {
                        set_status(working_status, rank);

                        my_status = 1;
                        //if(ts_logging==1)
                        {
                            sched_log_file = fopen(sched_log,"a");
                            fprintf( sched_log_file, "[%f] I am working!\n", MPI_Wtime());
                            fclose(sched_log_file);
                        }
                    }

                    //if(ts_logging==1)
                    {
                        sched_log_file = fopen(sched_log,"a");
                        fprintf( sched_log_file, "[%f] How-how-how! I have work [%3.1f][%6.4f] to STEAL from %d!\n", MPI_Wtime(), task0[0], task0[1], target_rank);
                        fclose(sched_log_file);
                    }

                    run_task(task0, &result0);
                    // here you have to organize the results collection, i.e. placing in a database
                    // in this example I simply place the results on each process in a single cumulative .csv file
                    //if(ts_logging==1)
                    {
                        sched_log_file = fopen(sched_log,"a");
                        fprintf( sched_log_file, "[%f] Work is done, my master!\n\n", MPI_Wtime());
                        fclose(sched_log_file);
                    }

                    local_res_file = fopen(local_res,"a");
                    for(i=0; i<task_type_length; i++)
                    {
                        fprintf( local_res_file, "%f;", task0[i]);

                    }
                    for(i=0; i<result_type_length; i++)
                    {
                        fprintf( local_res_file, "%f;", result0[i]);
                    }
                    fprintf( local_res_file, "\n");
                    fclose(local_res_file);
                }// not empty - got val!

                target_rank = ((target_rank+1)>=num_proc)?0:(target_rank+1);

            }// cycle: all other processors;

            if(empty > 0)
            {
                if(my_status==1) // if nothing found in this cycle - put "idle" state
                {
                    set_status(idle_status, rank);

                    my_status=0;
                    //if(ts_logging==1)
                    {
                        sched_log_file = fopen(sched_log,"a");
                        fprintf( sched_log_file, "[%f] I am Idle =(\n", MPI_Wtime());
                        fclose(sched_log_file);
                    }
                }
                fail_cntr++;

                if(fail_cntr > 100) // once in a hundred
                {
                    accumulated_status = check_for_finish( num_proc, rank);
                    fail_cntr=0;
                }

            } // try to find out number of idles
        }// infinite cycle - check other Qs
    }//infinite GLOBAL cycle


    /* free window buffer */
    MPI_Win_free( &win_q );
    MPI_Win_free( &win_offs );
    MPI_Win_free( &win_status );
    MPI_Free_mem(QUEUE);
    MPI_Free_mem(OFFSET);
    MPI_Free_mem(STATUS);
    /* done */

    if(rank == 0)
    {
        code_postprocessing_master();
    }
    else
    {
        code_postprocessing_slave();
    }


    MPI_Finalize();
    exit(0);
}
