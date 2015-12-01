// master managed scheduling //
// for corsika code //
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
//#include "config.h"

#include "task_params.h"

////////////////////flags(TYPES OF MPI MESSAGES)//////////////////////
#define START 1000
#define REQUEST 1001
#define FINISH 1002
#define STOP 1003

//////////////////error codes///////////////////////////////
#define NA -1
#define NOT_FOUND -2

char sched_log[255];
FILE * sched_log_file;
int ts_logging=1;

struct node *q_head,*q_tail; //head and tail of the queue used for storing the waiting processes.

struct message_queue //structure of MPI message.
{
    int id1;        // I1CUTPAR (INT) : FIRST INDEX OF PARTICLE TO READ FROM CFILINP
    int id2;        // I2CUTPAR (INT) : LAST INDEX OF PARTICLE TO READ FROM CFILINP
    int lprim;      // (BOOLEAN) : TRUE(1), IF SHOWER IS PRIMARY || FALSE(0), IF SUBSHOWER IS SECONDARY
    int rnnum;      // RUN NUMBER
    int seed;       // SEED USED BY THE SUB SHOWER
    int uid;        // THE UNIQUE ID OF THE MPI JOB
    int parent_id;  // THE PARENT ID OF THE MPI JOB(USED TO RECONSTRUCT THE CUTFILE_NAME)
    double* stack;
};

struct book   //Keeps the information about whether a processor is "Busy(1)" or "Free(0)"
{
    int busy;
    int id;
};

struct node   //An entry for the QUEUE
{
    struct message_queue queue_data;
    struct node* next;
};

/*
function check_for_finish()
Called from main() by the MASTER to check if the simulation is over.
Returns TRUE if no processor is busy(SIMULATION OVER), else returns FALSE
*/
int check_for_finish(struct book* book,int num_proc)
{
    int i,check=1;
    for(i=1;i<num_proc;i++)
    {
        if(book[i].busy==1)
        {
            check=0;
            break;
        }
    }
    return check;
}

/*
function get_free_rank()
Called from main() by the MASTER to get a free processor rank.
Returns the RANK if found else returns the error code NOT_FOUND
*/
int get_free_rank(struct book* book,int num_proc)
{
    int i,check=0;
    for(i=1;i<num_proc;i++)
    {
        if(book[i].busy==0)
        {
            check=1;
            break;
        }
    }
    if(check==1)
        return i;
    else return NOT_FOUND;
}

/*
function queue_is_empty()
Called from main() by the MASTER
returns TRUE if the QUEUE is empty, else returns FALSE.
*/
int queue_is_empty()
{
    if(q_head==NULL)
        return 1;
    else return 0;
}

/*
function add_new_particle_to_queue()
Called from main() by the MASTER
adds a new item into the QUEUE.
*/
void add_new_particle_to_queue(task_type item)
{
    int i,j;
    FILE* file;
    char statfile[255],numstr[9];
    if (dbg_infos)
    {
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", MASTER);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        file =fopen(statfile,"a");
        fprintf(file,"\n[%f] QUEUE: Adding request %d %d %d DAT%06d-%09d-%09d.cut %d %d %p",MPI_Wtime(),item.uid,item.parent_id,item.lprim,item.rnnum,item.seed,item.uid,item.id1,item.id2,item.stack);
        fclose(file);
    }
    struct node* temp= (struct node*)malloc(sizeof(struct node));
    temp->queue_data.stack=(double*)malloc(sizeof(double)*(item.id2-item.id1+1)*(PARTICLE_INFO_COUNT+1));
    temp->queue_data.id1 = item.id1;
    temp->queue_data.id2 = item.id2;
    temp->queue_data.lprim = item.lprim;
    temp->queue_data.rnnum = item.rnnum;
    temp->queue_data.seed = item.seed;
    temp->queue_data.uid = item.uid;
    temp->queue_data.parent_id = item.parent_id;

    for(i=0;i<(item.id2-item.id1+1);i++)
        for(j=0;j<(PARTICLE_INFO_COUNT+1);j++)
            temp->queue_data.stack[(PARTICLE_INFO_COUNT+1)*i+j]=item.stack[(PARTICLE_INFO_COUNT+1)*i+j];

    temp->next = NULL;

    if(q_head==NULL)
    {
        q_head = temp;
        q_tail = temp;
    }
    else
    {
        q_tail->next = temp;
        q_tail = temp;
    }

    if (dbg_infos)
    {
        file =fopen(statfile,"a");
        fprintf(file,"\n[%f] QUEUE: Added %d %d %d DAT%06d-%09d-%09d.cut %d %d %p",MPI_Wtime(),temp->queue_data.uid,temp->queue_data.parent_id,temp->queue_data.lprim,temp->queue_data.rnnum,temp->queue_data.seed,temp->queue_data.uid,temp->queue_data.id1,temp->queue_data.id2,temp->queue_data.stack);
        fclose(file);
    }
    return;
}

/*
function queue_del()
Called from main() by the MASTER
Identifies if there is a job waiting
Deletes an element from the QUEUE and is returns it to MASTER for further run.
*/
struct message queue_del()
{
    FILE* file;
    char statfile[255],numstr[9];
    if (dbg_infos)
    {
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", MASTER);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        file =fopen(statfile,"a");
        fprintf(file,"\n[%f] QUEUE: Deleting Request",MPI_Wtime());
        fclose(file);
    }

    struct message a;
    if(queue_is_empty(q_head,q_tail))
    {
        if (dbg_infos)
        {
            file =fopen(statfile,"a");
            fprintf(file,"\n[%f] QUEUE: QUEUE_UNDERFLOW_ERROR, QUEUE IS EMPTY",MPI_Wtime());
            fclose(file);
        }
        else
        {
            printf("\n[%f] QUEUE: QUEUE_UNDERFLOW_ERROR, QUEUE IS EMPTY",MPI_Wtime());
            fflush(stdout);
        }
    }
    else
    {
        int i,j;
        a.id1 = q_head->queue_data.id1;
        a.id2 = q_head->queue_data.id2;
        a.lprim = q_head->queue_data.lprim;
        a.rnnum = q_head->queue_data.rnnum;
        a.seed = q_head->queue_data.seed;
        a.uid = q_head->queue_data.uid;
        a.parent_id = q_head->queue_data.parent_id;

        for(i=0;i<(a.id2-a.id1+1);i++)
            for(j=0;j<(PARTICLE_INFO_COUNT+1);j++)
                a.stack[(PARTICLE_INFO_COUNT+1)*i+j]=q_head->queue_data.stack[(PARTICLE_INFO_COUNT+1)*i+j];

        struct node* temp = q_head;
        if(q_head->next==NULL)
        {
            q_head=q_tail=NULL;
        }
        else
        {
            q_head = q_head->next;
        }
        free(temp->queue_data.stack);//free the memory of stack of deleted particle
        free(temp);
        if (dbg_infos)
        {
            file =fopen(statfile,"a");
            fprintf(file,"\n[%f] QUEUE: DELETED %d %d %d DAT%06d-%09d-%09d.cut %d %d %p",MPI_Wtime(),a.uid,a.parent_id,a.lprim,a.rnnum,a.seed,a.uid,a.id1,a.id2,a.stack);
            fclose(file);
        }
    }
    return(a);
}

/*
function place_task
is called from the code interface
*/
void place_task(task_type buff, int rank )
{
    //Send the REQUEST message to the master
    int mpierr=MPI_Send(&buff,1,struct_type,MASTER,REQUEST,MPI_COMM_WORLD);
    if(mpierr!= MPI_SUCCESS)
    {
        printf("FATAL ERROR: When sending Message from %d to Master with rank %d\n",rank, MASTER);
        MPI_Abort(MPI_COMM_WORLD,mpierr);
    }
}

/*
function clear_buffer()
Called from main() by the MASTER/SLAVE
Called from new_particle()
Clears the contents of the buffer to avoid ambiguity.
*/
void clear_buffer(struct message* buff)
{
    buff->id1=0;
    buff->id2=0;
    buff->lprim=-1;
    buff->rnnum=-1;
    buff->seed=-1;
    buff->uid=-1;
    buff->parent_id=-1;
    return;
}

/*
function entry_update_start()
Called from main() by the MASTER
Writes the status about the jobs started into a file called "status_start"
*/
void entry_update_start(struct message* buff,int rank,int* no_running,int* no_queued,int* no_finished,int* no_lost)
{
    char statfile[255];
    strcpy(statfile,statdir);
    strcat(statfile,"status_start");
    FILE* file = fopen(statfile,"a");
    fprintf(file,"%d %d %d %d %d %d %d %d %d %f %d %d %d %d\n",buff->uid,buff->parent_id,buff->lprim,buff->rnnum,buff->seed,buff->uid,buff->id1,buff->id2,rank,MPI_Wtime(),*no_running,*no_queued,*no_finished,*no_lost);
    fclose(file);

    strcpy(statfile,statdir);
    strcat(statfile,"relation");
    file = fopen(statfile,"a");
    fprintf(file,"%d %d\n",buff->uid,buff->parent_id);
    fclose(file);
}

/*
function entry_update_queue()
Called from main() by the MASTER
Writes the status about the jobs queued into a file called "queue_add"
*/
void entry_update_queue(struct message* buff,int* no_running,int* no_queued,int* no_finished,int* no_lost)
{
    char statfile[255];
    strcpy(statfile,statdir);
    strcat(statfile,"queue_add");
    FILE* file = fopen(statfile,"a");
    fprintf(file,"%d %d %d %d %d %d %d %d %f %d %d %d %d\n",buff->uid,buff->parent_id,buff->lprim,buff->rnnum,buff->seed,buff->uid,buff->id1,buff->id2,MPI_Wtime(),*no_running,*no_queued,*no_finished,*no_lost);
    fclose(file);
}


/*
function entry_update_lost()
Called from main() by the MASTER
Writes the status about the jobs lost into a file called "lost_jobs"
*/
void entry_update_lost(struct message* buff,int* no_running,int* no_queued,int* no_finished,int* no_lost)
{
    (*no_lost)++;

    char statfile[255];
    strcpy(statfile,statdir);
    strcat(statfile,"lost_jobs");
    FILE* file = fopen(statfile,"a");
    fprintf(file,"%d %d %d %d %d %d %d %d %d %d %d %d\n",buff->uid,buff->parent_id,buff->lprim,buff->rnnum,buff->seed,buff->uid,buff->id1,buff->id2,*no_running,*no_queued,*no_finished,*no_lost);
    fclose(file);
}

/*
function entry_update_resumed()
Called from main() by the MASTER
Writes the status about the jobs resumed into a file called "status_start"
*/
void entry_update_resume(struct message* buff,int rank,int* no_running,int* no_queued,int* no_finished,int* no_lost)
{
    char statfile[255];

    strcpy(statfile,statdir);
    strcat(statfile,"status_start");
    FILE* file = fopen(statfile,"a");
    fprintf(file,"%d %d %d %d %d %d %d %d %d %f %d %d %d %d\n",buff->uid,buff->parent_id,buff->lprim,buff->rnnum,buff->seed,buff->uid,buff->id1,buff->id2,rank,MPI_Wtime(),*no_running,*no_queued,*no_finished,*no_lost);
    fclose(file);

    strcpy(statfile,statdir);
    strcat(statfile,"relation");
    file =fopen(statfile,"a");
    fprintf(file,"%d %d\n",buff->uid,buff->parent_id);
    fclose(file);
}

/*
function entry_update_finished()
Called from main() by the MASTER
Writes the status about the jobs started into a file called "status_finish"
*/
void entry_update_finish(int uid,int rank,double mpi_time1,double mpi_time2,int* no_running,int* no_queued,int* no_finished,int* no_lost)
{
    (*no_finished)++;
    (*no_running)--;
    char statfile[255];

    strcpy(statfile,statdir);
    strcat(statfile,"status_finish");
    FILE* file = fopen(statfile,"a");
    fprintf(file,"%d %d %f %f %f %d %d %d %d\n",uid,rank,MPI_Wtime(),mpi_time1,mpi_time2,*no_running,*no_queued,*no_finished,*no_lost);
    fclose(file);
}
