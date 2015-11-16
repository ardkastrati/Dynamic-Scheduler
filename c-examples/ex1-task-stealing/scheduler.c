// task stealing via MPIRemote memory access //
// dummy test //
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <mpi.h>

#include "task_params.h"

#define SORT 1

MPI_Win win_q;
task_type_unit * QUEUE;

MPI_Win win_offs;
int * OFFSET;

MPI_Win win_status;
int * STATUS;

char sched_log[255];
FILE * sched_log_file;
int ts_logging=1;

int lock;

//functions for task stealing!!!
int read_last_task( task_type_unit * task0, int target_rank, int num_tries)
{
    // return codes:
    // 0 - element read
    // 1 - q is empty
    // 2 - element not read (more tries than <num_tries>)
    int ret = 0;
    int iamfree = 0;
    int my_offset;

    int tries_cntr=0;


    while(iamfree == 0 && (num_tries==0 || tries_cntr<num_tries)) //try to lock offs window putting -2 value
    {
        tries_cntr++;

        MPI_Win_lock( MPI_LOCK_EXCLUSIVE, target_rank, 0, win_offs );
        MPI_Get( &my_offset, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_offs );
        MPI_Put( &lock, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_offs ); //implicitly block OFFSET win on proc <rank> (block code -2)
        MPI_Win_unlock( target_rank, win_offs );
        if(my_offset >= -1) //if the window was not locked before
        {
            iamfree = 1;
        }
    }
    if(iamfree == 0) // q is still blocked - go furter
    {
        ret = 2;
        return(ret);
    }

    // offs window is now locked by me! work!
    if(my_offset == -1) //q is empty
    {
        ret = 1;
    }
    else
    {
        //if(ts_logging==1)
        {
            sched_log_file = fopen(sched_log,"a");
            fprintf(sched_log_file, "[%f] Take task N %d\n", MPI_Wtime(), my_offset);
            fclose(sched_log_file);
        }

        //task_type_unit buf[task_type_length];
        MPI_Win_lock( MPI_LOCK_EXCLUSIVE, target_rank, 0, win_q ); //lock the q
        MPI_Get( task0, task_type_length, mpi_task_type_unit, target_rank, my_offset, task_type_length, mpi_task_type_unit, win_q );
        MPI_Win_unlock( target_rank, win_q );

        //task0[0] = buf[0];
        //task0[1] = buf[1];


        my_offset--;

    }
    MPI_Win_lock( MPI_LOCK_EXCLUSIVE, target_rank, 0, win_offs );
    MPI_Put( &my_offset, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_offs ); //UNBLOCK OFFSET win (put proper offs val - either changed or not)
    MPI_Win_unlock( target_rank, win_offs );

    return(ret);
}

int read_last_task_own( task_type_unit * task0, int target_rank) // queue_del
{
    // return codes:
    // 0 - element read
    // 1 - q is empty
    int ret = 0;
    int iamfree = 0;
    int my_offset;
    int i;

    while(iamfree == 0 ) //try to lock offs window putting -2 value
    {
        MPI_Win_lock( MPI_LOCK_EXCLUSIVE, target_rank, 0, win_offs );
        my_offset = OFFSET[0];
        OFFSET[0] = lock;
        MPI_Win_unlock( target_rank, win_offs );
        if(my_offset >= -1) //if the window was not locked before
        {
            iamfree = 1;
        }
    }

    // offs window is now locked by me! work!
    if(my_offset == -1) //q is empty
    {
        ret = 1;
    }
    else
    {
        // get params
        //if(ts_logging==1)
        {
            sched_log_file = fopen(sched_log,"a");
            fprintf(sched_log_file, "[%f] Take task N %d\n", MPI_Wtime(), my_offset);
            fclose(sched_log_file);
        }

        MPI_Win_lock( MPI_LOCK_EXCLUSIVE, target_rank, 0, win_q ); //lock the q

        for(i=0; i<task_type_length; i++)
        {
            task0[i] = QUEUE[task_type_length * my_offset + i]; // or use memcpy
        }

        MPI_Win_unlock( target_rank, win_q );

        my_offset--;
    }

    MPI_Win_lock( MPI_LOCK_EXCLUSIVE, target_rank, 0, win_offs );
    OFFSET[0] = my_offset; //UNBLOCK OFFSET win (put proper offs val - either changed or not)
    MPI_Win_unlock( target_rank, win_offs );

    return(ret);
}

void add_element_unsorted( task_type task0, int rank  )
{
    int iamfree = 0;
    int my_offset;
    int i;

    while(iamfree == 0) //try to lock offs window putting -2 value
    {
        MPI_Win_lock( MPI_LOCK_EXCLUSIVE, rank, 0, win_offs );
        my_offset = OFFSET[0];
        OFFSET[0] = lock;
        MPI_Win_unlock( rank, win_offs );
        if(my_offset >= -1) //if the window was not locked before
        {
            iamfree = 1;
        }
    }

    //if(ts_logging==1)
    {
        sched_log_file = fopen(sched_log,"a");
        fprintf(sched_log_file, "[%f] Adding task [%3.1f][%6.4f] to my queue\n", MPI_Wtime(), task0[0], task0[1]);
        fclose(sched_log_file);
    }
    my_offset++;

    MPI_Win_lock( MPI_LOCK_EXCLUSIVE, rank, 0, win_q ); //lock the q

    for(i=0; i<task_type_length; i++)
    {
        QUEUE[task_type_length * my_offset + i] = task0[i]; // or use memcpy
    }

    MPI_Win_unlock( rank, win_q );

    //if(ts_logging==1)
    {
        sched_log_file = fopen(sched_log,"a");
        fprintf(sched_log_file, "[%f] New number of tasks is N %d\n", MPI_Wtime(), my_offset);
        fclose(sched_log_file);
    }

    MPI_Win_lock( MPI_LOCK_EXCLUSIVE, rank, 0, win_offs );
    OFFSET[0] = my_offset;
    MPI_Win_unlock( rank, win_offs );
}

void add_element_sorted( task_type task0, int rank, int sort_param_num )
{
    int iamfree = 0;
    int my_offset;
    int i;

    while(iamfree == 0) //try to lock offs window putting -2 value
    {
        MPI_Win_lock( MPI_LOCK_EXCLUSIVE, rank, 0, win_offs );
        my_offset = OFFSET[0];
        OFFSET[0] = lock;
        MPI_Win_unlock( rank, win_offs );
        if(my_offset >= -1) //if the window was not locked before
        {
            iamfree = 1;
        }
    }

    //if(ts_logging==1)
    {
        sched_log_file = fopen(sched_log,"a");
        fprintf(sched_log_file, "[%f] Adding task [%3.1f][%6.4f] to my queue, sorted, sort param num %d\n", MPI_Wtime(), task0[0], task0[1], sort_param_num);
        fclose(sched_log_file);
    }
    my_offset++;

    task_type_unit local_q[my_offset*task_type_length];
    MPI_Win_lock( MPI_LOCK_EXCLUSIVE, rank, 0, win_q ); //lock the q
    //locally copy the whole queue
    //MPI_Get( local_q, my_offset*task_type_length, mpi_task_type_unit, rank, 0, my_offset*task_type_length, mpi_task_type_unit, win_q ); //get the last value from queue window
    memcpy(local_q, QUEUE, sizeof(task_type_unit)*my_offset*task_type_length);

    MPI_Win_unlock( rank, win_q );

    // seek for the item before which we should place our new task
    int my_index=0;
    task_type_unit my_param = local_q[sort_param_num];
    for(i=sort_param_num; (i<my_offset*task_type_length) && (task0[sort_param_num]>my_param); i+=task_type_length)
    {
        my_param = local_q[i];
        my_index = i-sort_param_num;
    }
    if(task0[sort_param_num]>my_param) my_index+=task_type_length;

    // we have to shift the last part of the queue
    // z.b. in such a primitive way as I did or using memcpy
    // starting from last element ending with index, move each param of each element to the next position

    MPI_Win_lock( MPI_LOCK_EXCLUSIVE, rank, 0, win_q ); //lock the q
    // now put the new element to its place
    for(i=0; i<task_type_length; i++)
    {
        QUEUE[my_index + i] = task0[i]; // or use memcpy
    }
    for(i=my_offset*task_type_length-1; i>=my_index; i-- )
    {
        QUEUE[i+task_type_length] = local_q[i];
    }
    MPI_Win_unlock( rank, win_q );

    //if(ts_logging==1)
    {
        sched_log_file = fopen(sched_log,"a");
        fprintf(sched_log_file, "[%f] New number of tasks is N %d\n", MPI_Wtime(), my_offset);
        fclose(sched_log_file);
    }

    MPI_Win_lock( MPI_LOCK_EXCLUSIVE, rank, 0, win_offs );
    OFFSET[0] = my_offset;
    MPI_Win_unlock( rank, win_offs );
}

void place_task(task_type task0, int rank )
{
    if (SORT == 1)
    {
        //I use the first sort param here
        //well, in my case there is only one
        // but for you there schould be an opportunity to choose one of
        // according to your scheduling policy
        add_element_sorted(task0, rank, stat_task_params[0]);
    }
    else
    {
        add_element_unsorted(task0, rank);
    }
}

void set_status( int new_status, int rank )
{
    MPI_Win_lock( MPI_LOCK_EXCLUSIVE, rank, 0, win_status );
    STATUS[0] = new_status;
    MPI_Win_unlock( rank, win_status );
}

int check_for_finish( int num_proc, int rank ) //checks if all processors are idle - returns num of working processors
{
    int accumulated_status = 0; // starting accumulate
    int tmp_status;
    int target_rank;

    for(target_rank=0; target_rank<num_proc; target_rank++) // cycle: check all other processors status;
    {
        if (target_rank!=rank)
        {
            MPI_Win_lock( MPI_LOCK_SHARED, target_rank, 0, win_status );
            MPI_Get( &tmp_status, 1, MPI_INT, target_rank, 0, 1, MPI_INT, win_status );
            MPI_Win_unlock( target_rank, win_status );

            accumulated_status+=tmp_status;
        }
    } // checking all statuses
    return accumulated_status;
}
