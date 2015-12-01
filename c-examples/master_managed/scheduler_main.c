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
    int no_running,no_queued,no_finished,no_lost; //Number of jobs running,queued,finished and lost respectively.
    no_running=no_queued=no_finished=no_lost=0;

    int  rank, num_proc, mpierr;
    int i, j;

    FILE *comm, *file;
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

    task_type initial_buff[1];
    int initial_tasks_number; // for this code only one initial task

    disp_unit = sizeof( task_type );

    // lets start the game
    // run the preprocessing of the code - recieve information about initial tasks
    if(rank==MASTER)
    {
        code_preprocessing_master(argc, argv, initial_buff, &initial_tasks_number);
    }
    else
    {
        code_preprocessing_slave(argc, argv);
    }

    // here goes the scheduling part
    if(rank==MASTER)
    {
        task_type buff;
        //Initializing the array(book) to keep track of processors status: free/working
        struct book* book = (struct book*) malloc(num_proc*sizeof(struct book));

        //initialize the queue
        q_head=q_tail=NULL;

        //initialize all ranks as free
        for(i=0;i<num_proc;i++) book[i].busy=0;
        //allotting number of working/running slaves
        no_running++;
        //Printing status in statistic files
        if (dbg_infos) entry_update_start(initial_buff,1,&no_running,&no_queued,&no_finished,&no_lost);

        //Send the order to start the parallel CORSIKA task on slave with id=buff.uid
        MPI_Send(initial_buff,1,struct_type,1,START,MPI_COMM_WORLD);

        int uid = initial_buff[0].uid;
        //updating status for bookkeeping
        book[1].busy=1;
        book[1].id=uid;

master_back:;
        //check if slaves have finished their jobs and finalize simulation ??may be the queue of waiting jobs need to be checked again??
        if(check_for_finish(book,num_proc))
        {
            free(book);
            //Stopping all waiting slaves
            for(i=1;i<num_proc;i++)
            {
                if (dbg_infos)
                {
                    strcpy(statfile,statdir);
                    strcat(statfile,"mpiid-");
                    sprintf(numstr, "%d", MASTER);
                    strcat(statfile,numstr);
                    strcat(statfile,"-runprotocol.txt");
                    file =fopen(statfile,"a");
                    fprintf(file,"\n[%f] STOP: Sending STOP request to slave= %d",MPI_Wtime(),i);
                    fclose(file);
                }
                MPI_Send(&buff,1,MPI_SHORT,i,STOP,MPI_COMM_WORLD);
            }
            //do the post-processing
            code_postprocessing_master();
        }
        else
        {
            MPI_Status stat;
            //Clearing the buffer to avoid any ambiguity
            clear_buffer(&buff);

            if (dbg_infos)
            {
                strcpy(statfile,statdir);
                strcat(statfile,"mpiid-");
                sprintf(numstr, "%d", MASTER);
                strcat(statfile,numstr);
                strcat(statfile,"-runprotocol.txt");
                file = fopen(statfile,"a");
                fprintf(file,"\n[%f] WAITING: Waiting to receive ANY message from ANY slave",MPI_Wtime());
                fclose(file);
            }
            MPI_Recv(&buff,1,struct_type,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&stat);

            switch(stat.MPI_TAG)
            {
            case REQUEST:
            //Slave sent a 'REQUEST' informing to master about being ready for a new job
            {
                int parent_rank=stat.MPI_SOURCE;
                //get the parent id (requesting id) from the bookkeeping
                int parent_id=book[parent_rank].id;

                if (dbg_infos)
                {
                    //Record status of Slave to Master communication in statistic files
                    strcpy(statfile,statdir);
                    strcat(statfile,"Slave2MasterRecv");
                    comm = fopen(statfile,"a");
                    fprintf(comm,"%d %d %d %d %d %d %d %p\n",buff.uid,buff.lprim,buff.rnnum,buff.seed,buff.uid,buff.id1,buff.id2,buff.stack);
                    fclose(comm);

                    strcpy(statfile,statdir);
                    strcat(statfile,"mpiid-");
                    sprintf(numstr, "%d", MASTER);
                    strcat(statfile,numstr);
                    strcat(statfile,"-runprotocol.txt");

                    file = fopen(statfile,"a");
                    fprintf(file,"\n[%f] REQUEST: received request from slave with rank %d running subshower with id %d asking to run another parallel task for %d particles with following parameters",MPI_Wtime(),parent_rank,parent_id,buff.id2-buff.id1+1);
                    for(i=0;i<(buff.id2-buff.id1+1);i++)
                    {
                        fprintf(file,"\n");
                        for(j=0;j<(PARTICLE_INFO_COUNT+1);j++) fprintf(file,"%f ",buff.stack[i*(PARTICLE_INFO_COUNT+1)+j]);
                    }
                    //					fprintf(file,"\n[%f] For each above mentioned particle/group a new parallel CORSIKA run will be started",MPI_Wtime());
                    fclose(file);
                }

                //alloc a new unique ID to the particle
                int child_id= ++uid;
                buff.uid = child_id;
                buff.parent_id = parent_id;
                //fetch a free rank
                int child_rank= get_free_rank(book,num_proc);

                //if all slaves are busy, insert the task into a queue
                if(child_rank==NOT_FOUND)
                {
                    add_new_particle_to_queue(buff);
                    no_queued++;
                    if (dbg_infos) entry_update_queue(&buff,&no_running,&no_queued,&no_finished,&no_lost);
goto master_back;
                }
                else  //Functioning if a free rank is found
                {
                    no_running++;//allotting the number of working/running slaves

                    if (dbg_infos)
                    {//MPI World tagging in statistic files
                        strcpy(statfile,statdir);
                        strcat(statfile,"mpiid-");
                        sprintf(numstr, "%d", MASTER);
                        strcat(statfile,numstr);
                        strcat(statfile,"-runprotocol.txt");
                        file = fopen(statfile,"a");
                        fprintf(file,"\n[%f] START: The task with unique id = %d and parent id = %d will run on the the rank = %d",MPI_Wtime(),child_id,parent_id,child_rank);
                        fclose(file);
                        entry_update_start(&buff,child_rank,&no_running,&no_queued,&no_finished,&no_lost);
                    }

                    MPI_Send(&buff,1,struct_type,child_rank,START,MPI_COMM_WORLD);     //send the order to start the task

                    if (dbg_infos)
                    {
                        //Record status of Master to Slave communication in statistic files
                        strcpy(statfile,statdir);
                        strcat(statfile,"Master2SlaveOrder");
                        comm = fopen(statfile,"a");
                        fprintf(comm,"%d %d %d %d %d %d %d %d %p\n",buff.uid,buff.parent_id,buff.lprim,buff.rnnum,buff.seed,child_rank,buff.id1,buff.id2,buff.stack);
                        fclose(comm);
                    }

                    //updating status for bookkeeping
                    book[child_rank].busy=1;
                    book[child_rank].id=child_id;

                }
goto master_back;
            }
            break;

            case FINISH:
                //Steps of MASTER when a 'FINISH' message is received from a SLAVE
            {
                int free_rank=stat.MPI_SOURCE;
                int finished_id=book[free_rank].id;

                //Type cast the buffer as the message received now contains timing information instead of the particle information.
                double* mpi_time = (double*)(&buff);

                //Record status of parallel runs in statistic files
                no_finished++;
                no_running--;
                if (dbg_infos)
                {
                    char statfile[255];
                    strcpy(statfile,statdir);
                    strcat(statfile,"status_finish");
                    file = fopen(statfile,"a");
                    fprintf(file,"%d %d %f %f %f %d %d %d %d\n",finished_id,free_rank,MPI_Wtime(),mpi_time[0],mpi_time[1],no_running,no_queued,no_finished,no_lost);
                    fclose(file);
                }

                //updating status for bookkeeping
                book[free_rank].busy=0;
                book[free_rank].id=NA;

                //MPI World tagging in statistic files
                if (dbg_infos)
                {
                    strcpy(statfile,statdir);
                    strcat(statfile,"mpiid-");
                    sprintf(numstr, "%d", MASTER);
                    strcat(statfile,numstr);
                    strcat(statfile,"-runprotocol.txt");
                    file = fopen(statfile,"a");
                    fprintf(file,"\n[%f] FINISH: The rank = %d running unique id = %d is now set as free in bookkeeping",MPI_Wtime(),free_rank,finished_id);
                    fclose(file);
                }
                //Check the queue to see if any jobs is waiting
                if(!queue_is_empty())
                {	int mpierr;
                    //read a pending task and remove it from the queue
                    struct message temp= queue_del();
                    no_running++;
                    no_queued--;
                    if (dbg_infos)
                    {
                        file = fopen(statfile,"a");
                        fprintf(file,"\n[%f] FINISH: The task with unique id = %d previously waiting in queue will run on rank = %d",MPI_Wtime(),temp.uid,free_rank);
                        fclose(file);
                        entry_update_resume(&temp,free_rank,&no_running,&no_queued,&no_finished,&no_lost);
                    }

                    //Sending the order to start the task on free rank
                    mpierr=MPI_Send(&temp,1,struct_type,free_rank,START,MPI_COMM_WORLD);

                    if (dbg_infos)
                    {
                        file = fopen(statfile,"a");
                        fprintf(file,"\n[%f] FINISH: Sent of request to slave %d returned error code %d",MPI_Wtime(),free_rank,mpierr);
                        fclose(file);
                        //Record status of Master to Slave communication in statistic files
                        strcpy(statfile,statdir);
                        strcat(statfile,"Master2SlaveOrder");
                        comm = fopen(statfile,"a");
                        fprintf(comm,"%d %d %d %d %d %d %d %d %p\n",temp.uid,temp.parent_id,temp.lprim,temp.rnnum,temp.seed,free_rank,temp.id1,temp.id2,temp.stack);
                        fclose(comm);
                    }
                    //updating status for bookkeeping
                    book[free_rank].busy=1;
                    book[free_rank].id=temp.uid;
                }
goto master_back;
            }
            break;

            default:
            {
                process_code_signal(stat, buff);
goto master_back;
            }
                break;
            } //End of MPI status switches
        } //End of bookkeeping
    } //End of IF on Rank is Master
    else
    {
        MPI_Status stat;
        task_type buff;	//MPI Buffer for Communication
        double mpi_time[2];		//To record time for CORSIKA

slave_back:;
        clear_buffer(&buff);	//Clearing the Buffer to avoid ambiguity.
        II1=-1;					//Resetting the pointer for current particle in group
        particle_stack_or_cut_file = (double*)calloc((PARTICLE_INFO_COUNT+1)*MXLIST,sizeof(double)); //Stack for possible new secondary particles

        //Waiting for ANY type of message(new particle) from the MASTER.
        if (dbg_infos)
        {
            strcpy(statfile,statdir);
            strcat(statfile,"mpiid-");
            sprintf(numstr, "%d", rank);
            strcat(statfile,numstr);
            strcat(statfile,"-runprotocol.txt");
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] WAITING: Waiting for a new message with STOP/START request from master",MPI_Wtime());
            fclose(file);
        }

        MPI_Recv(&buff,1,struct_type,0,MPI_ANY_TAG,MPI_COMM_WORLD,&stat);

        //////Function of slave if the a 'STOP' message is recieved
        if(stat.MPI_TAG==STOP)
        {
            if (dbg_infos)
            {
                file = fopen(statfile,"a");
                fprintf(file,"\n[%f] STOP: Received a stop command from master the rank %d is exiting ",MPI_Wtime(),rank);
                fprintf(file,"\n[%f] STOP: Going to send the information about maximal vertical steps in long files %d ",MPI_Wtime(),NSTEP1);
                fclose(file);
            }
            code_postprocessing_slave();
            if (MAXBUFSLAVE)
            {
                write_block_fort(MAXBUFSLAVE,Block); //Write out particle block, MAXBUFSLAVE = maxbuf after 1st run
                maxblock_switch = 32000;//Finalising write out of particle blocks, 32000 > 23456 which is used in write_block_fort to check for last run
                write_block_fort(MAXBUFSLAVE,Block);//write out Event end and Run end blocks
            }
            else
            {
                if (dbg_infos)
                {
                    file = fopen(statfile,"a");
                    fprintf(file,"\n[%f] DATA: No data in buffer of particles Buffer is %d ",MPI_Wtime(),MAXBUFSLAVE);
                    fclose(file);
                }
            }

            free(particle_stack_or_cut_file);
        }
        //////FUNCTION OF SLAVE IF THE A 'START' MESSAGE IS RECIEVED (REFER THE DOCUMENTAION)
        if(stat.MPI_TAG==START)
        {   //CALL of CORSIKA SUBROUTINE

            run_task(buff, &mpi_time);
            //send message to the master reporting about the finished simulation
            //sending doubles instead of mpi_structure type. Be careful in the master to type cast the buffer
            MPI_Send(mpi_time,2,MPI_DOUBLE,MASTER,FINISH,MPI_COMM_WORLD);
            free(particles_from_stack);
            free(particle_stack_or_cut_file);
            //////////////////going back to waiting state//////////////////////
goto slave_back;
        }
    }

    MPI_Finalize();
    exit(0);
}
