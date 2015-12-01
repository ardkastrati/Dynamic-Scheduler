// dummy code simulator test //
#include "scheduler.c"
#include <sys/stat.h>

#define MASTER 0
#define MAX_WEIGHT 80
#define MAX_ADDS 10

double global_runtime;
double my_worktime;

int total_additions;
int my_max_adds;

int rnnum0;

char input_fname[255];

char llog[255];
FILE * llog_f;

/*
function read_input()
Called from main.
This function reads the MPI input file for the parameters.
*/
void read_input(double* dectcut,double* dectmax,int* lprim,char* cutfilename,int* id1,int* id2,int* rnnum,int* seed,char * input_fname)
{
    int x,dum;
    char* end;
    char str1[10],str2[180],str3[32],str4[32],str5[1],str[255];
    FILE *file = fopen(input_fname,"r");
    if(file==NULL)
    {
        printf("Error opening the file for mpi input %s\n",input_fname);
        MPI_Abort(MPI_COMM_WORLD,19);
    }
    else
    {
        lcout=0;
        *id1=0;
        *id2=0;
        *seed=6;
        *rnnum=1;
        *dectcut=1E4;
        *dectmax=1E7;
        *lprim=1;
        int seeder=1;
        while(!feof(file))
        {
            strcpy(str1, " ");
            strcpy(str2, " ");
            strcpy(str3, " ");
            strcpy(str4, " ");
            strcpy(str5, " ");
            strcpy(str, " ");
            fgets (str , 255 , file);
            x= sscanf(str,"%s %s %s %s %s\n",str1,str2,str3,str4,str5);
            //puts(str);
            if(x>0)
            {
                if (dbg_infos)
                {
                    printf("\ntag %s value %s %s %s %s",str1,str2,str3,str4,str5);
                    fflush(stdout);
                }
                if(!strcmp(str1,"RUNNR")||!strcmp(str1,"runnr"))
                {
                    *rnnum= atoi(str2);
                }
                else if(!strcmp(str1,"SEED")||!strcmp(str1,"seed"))
                {
                    //if(seeder)
                    //{if (dbg_infos) printf("\n First Seed would be read and used for first output file names. The rest Seeds would be ignored");
                    *seed= atoi(str2);
                    //seeder= 0;
                    //}
                }
                else if(!strcmp(str1,"PARALLEL")||!strcmp(str1,"parallel"))
                {
                    *dectcut= strtod(str2,&end);
                    *dectmax= strtod(str3,&end);
                    dum= atoi(str4);
                    if(!strcmp(str5,"T")||!strcmp(str5,"t")) lcout= 1;
                }
                else if(!strcmp(str1,"DIRECT")||!strcmp(str1,"direct"))
                {
                    strcpy(statdir,str2);
                    struct stat sb;
                    if (stat(statdir, &sb) == 0 && S_ISDIR(sb.st_mode))
                    {
                        if (dbg_infos)
                        {
                            printf("\ntag %s as %s will be used for outputs",str1,statdir);
                            fflush(stdout);
                        }
                    }
                    else
                    {
                        if (dbg_infos)
                        {
                            printf("\nDirectory %s dose not exist. Will be created and used for outputs",statdir);
                            fflush(stdout);
                        }
                        int result = mkdir(statdir, 0700);
                        if (result)
                        {
                            printf("\nFailed to create directory %s using mkdir. Will abort with error %d",statdir, result);
                            MPI_Abort(MPI_COMM_WORLD,result);
                        }
                    }
                }
                else if(!strcmp(str1,"CUTFILE")||!strcmp(str1,"cutfile"))
                {
                    *lprim= 0;
                    strcpy(cutfilename,str2);
                    *id1= atoi(str3);
                    *id2= atoi(str4);
                }
            }
        }
        if (dbg_infos)
        {
            printf("Successfully red the input file %s\n",input_fname);
            fflush(stdout);
        }
        fclose(file);
    }
}

/*
function reconstruct_cfname()
Called from main() by the MASTER and SLAVE both
Reconstructs the CUTFILE name from the run number,seed and unique ID of parallel simulated particle.
*/
void reconstruct_cfname( char* cutfilename,int rnnum,int seed,int uid)
{
    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    sprintf(cutfilename,"DAT%06d-%09d-%09d.cut",rnnum,seed,uid);
    if (dbg_infos)
    {
        char statfile[255],numstr[9];
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", rank);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        FILE* file =fopen(statfile,"a");
        fprintf(file,"\n[%f] CUTFILENAME: reconstruct of cut file name as %s with rnnum = %d  seed = %d uid = %d",MPI_Wtime(),cutfilename,rnnum,seed,uid);
        fclose(file);
    }
    return;
}

/*
function reconstruct_ofname()
Called from main() by the SLAVE
Reconstructs the OUTPUTFILE name from the run number,seed, MPI ID and directory.
*/
void reconstruct_ofname( char* outfname, int rnnum, int seed, int uid)
{
    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if (rank>LISTFILE_MAX)
        sprintf(outfname,"/dev/null");
    else
        sprintf(outfname,"%sDAT%06d-%09d-%09d.lst",statdir,rnnum,seed,uid);
    if (dbg_infos)
    {sprintf(outfname,"%sDAT%06d-%09d-%09d.lst",statdir,rnnum,seed,uid);
        char statfile[255],numstr[9];
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", rank);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        FILE* file =fopen(statfile,"a");
        fprintf(file,"\n[%f] OUTPUTFILENAME: reconstruct of output file name as %s with rnnum = %d  seed = %d uid = %d",MPI_Wtime(),outfname,rnnum,seed,uid);
        fclose(file);
    }
    return;
}

/*
function parse_cfname()
Called from main() by the MASTER to parse the CUTFILENAME read from the command line/input file into the runnum,seed.mpiid
*/
void parse_cfname( char* cutfilename,int* rnnum,int* seed,int* uid)
{
    sscanf(cutfilename,"DAT%06d-%09d-%09d.cut",rnnum,seed,uid);
    if (dbg_infos)
    {
        char statfile[255],numstr[9];
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", *uid);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        FILE* file =fopen(statfile,"a");
        fprintf(file,"\n[%f] CUTFILENAME: parse of cut file name as %s with rnnum = %d  seed = %d uid = %d",MPI_Wtime(),cutfilename,*rnnum,*seed,*uid);
        fclose(file);
    }
    return;
}

/*function called by master to write down the resultant longfile after adding the content of all longfiles received from slaves.
This function is called inside the "finalize_simulation()" function*/
void write_joined_longfile(char *joinedlongfile)
{
    if (dbg_infos)
    {	int rank;
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);
        char statfile[255],numstr[9];
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", rank);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        FILE* file =fopen(statfile,"a");
        fprintf(file,"\n[%f] LONGFILE:The master processor %d is writing down the joined longfile with %d steps",MPI_Wtime(),MASTER,NSTEP1);
        fclose(file);
    }
    int i,j;
    FILE*longfile;
    //	char filename[255];
    //	strcpy(filename,joinedlongfile);
    longfile=fopen(joinedlongfile,"a");

    fprintf(longfile,"%s",lngfile.pstr);
    for(i=0;i<NSTEP1;i++)
    {	fprintf(longfile,"%6.1f",lngfile.pbuffer[i][0]);
        for(j=1;j<10;j++)
        {  if ( lngfile.pbuffer[i][j] < 0. ) lngfile.pbuffer[i][j]=1.e-12;//normalize values to zero
            fprintf(longfile,"%12.5e",lngfile.pbuffer[i][j]);
            //fprintf(longfile,"%6.1f%12.5e%12.5e%12.5e%12.5e%12.5e%12.5e%12.5e%12.5e%12.5e\n",lngfile.pbuffer[i][0],lngfile.pbuffer[i+1][1],lngfile.pbuffer[i+2][2],lngfile.pbuffer[i+3][3],lngfile.pbuffer[i+4][4],lngfile.pbuffer[i+5][5],lngfile.pbuffer[i+6][6],lngfile.pbuffer[i+7][7],lngfile.pbuffer[i+8][8],lngfile.pbuffer[i+9][9]);
        }
        fprintf(longfile,"\n");
    }

    fprintf(longfile,"%s",lngfile.estr);
    for(i=0;i<NSTEP1;i++)
    {	fprintf(longfile,"%6.1f",lngfile.ebuffer[i][0]);
        for(j=1;j<10;j++)
        {  if ( lngfile.ebuffer[i][j] < 0. ) lngfile.ebuffer[i][j]=1.e-12;//normalize values to zero
            fprintf(longfile,"%12.5e",lngfile.ebuffer[i][j]);
            //fprintf(longfile,"%6.1f%12.5e%12.5e%12.5e%12.5e%12.5e%12.5e%12.5e%12.5e%12.5e\n",lngfile.ebuffer[i][0],lngfile.ebuffer[i+1][1],lngfile.ebuffer[i+2][2],lngfile.ebuffer[i+3][3],lngfile.ebuffer[i+4][4],lngfile.ebuffer[i+5][5],lngfile.ebuffer[i+6][6],lngfile.ebuffer[i+7][7],lngfile.ebuffer[i+8][8],lngfile.ebuffer[i+9][9]);
        }
        fprintf(longfile,"\n");
    }

    fclose(longfile);
}

/*
function new_particle()
Called from function endoffile() to send a REQUEST message to the MASTER.
*/
void new_particle(int id1,int id2,int rnnum,int seed,int uid)
{
    FILE *file,*comm;
    char statfile[255],numstr[9];
    int i,rank;

    //MPI_Datatype struct_type_new_particle,oldtypes[BLOCK_COUNT_MESSAGE]={MPI_INT,MPI_DOUBLE};
    //int blockcounts[BLOCK_COUNT_MESSAGE]={7,MAX_GROUP_SIZE*(PARTICLE_INFO_COUNT+1)};//(id2-id1+1)
    //MPI_Aint offsets[BLOCK_COUNT_MESSAGE],extent;
    //setup description for the fields in the message structure

    //int ofst=0;
    //for(i=0;i<BLOCK_COUNT_MESSAGE;i++)
    //{
    //    offsets[i]=ofst;
    //    MPI_Type_extent(oldtypes[i], &extent);
    //    ofst = ofst + blockcounts[i]*extent;
    //}
    //Defining structured type and committing it.
    //MPI_Type_create_struct(BLOCK_COUNT_MESSAGE, blockcounts, offsets, oldtypes, &struct_type_new_particle);
    //MPI_Type_commit(&struct_type_new_particle);

    //MPI Buffer for communication
    struct message buff;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if (dbg_infos)
    {
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", rank);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] NEW PARTICLES: Sending request for a simulation of a new group consisting of %d particles from subshower with id= %d from simulation under run number %d and seed %d: ",MPI_Wtime(),id2-id1+1,uid,rnnum,seed);
        fclose(file);
    }
    char local_log[255];
    sprintf(local_log, "local-log-p%06d.log", rank);
    FILE * local_log_file = fopen(local_log,"a");
    fprintf( local_log_file, "NEW particle values id1=%d, id2=%d, rnnum=%d, seed=%d, uid=%d\n STACK is: ", id1, id2, rnnum, seed, uid);
    int j,c=0;
    for(i=id1;i<=id2;i++)
    {
        for(j=0;j<PARTICLE_INFO_COUNT;j++)
        {
            buff.stack[c*(PARTICLE_INFO_COUNT+1)+j] = particle_stack_or_cut_file[((i-1)*(PARTICLE_INFO_COUNT+1))+j];
            fprintf( local_log_file, "%f; ", buff.stack[c*(PARTICLE_INFO_COUNT+1)+j]);
        }
        c++;
        fprintf(local_log_file, " next:\n");
    }
    fclose(local_log_file);
    buff.id1=id1;
    buff.id2=id2;
    buff.lprim=0; // 0-False as of secondary particle
    buff.rnnum=rnnum;
    buff.seed=seed;
    buff.uid=uid;
    buff.parent_id=NA;//Parent ID is available only in Booking database of Master

    place_task(buff, rank);

    if (dbg_infos)
    {
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] NEW PARTICLES: New group with %d particles sent to Master from subshower with id= %d from simulation under run number %d and seed %d from stack %p",MPI_Wtime(),id2-id1+1,uid,rnnum,seed,buff.stack);
        fclose(file);
        strcpy(statfile,statdir);
        strcat(statfile,"Slave2MasterRequest");
        comm = fopen(statfile,"a");
        fprintf(comm,"\n\n[%f] %d %d %d %d %d %d %d %d %p",MPI_Wtime(),buff.uid,buff.parent_id,buff.lprim,buff.rnnum,buff.seed,buff.uid,buff.id1,buff.id2,buff.stack);
        fclose(comm);
    }

    //MPI_Type_free(&struct_type_new_particle);
}


void code_preprocessing_master(int argc, char *argv[], task_type *buff, int * initial_tasks_number )
{
    int  rank, num_proc, i;
    char cutfilename[255];
    FILE *check, *file, *comm;

    // create the MPI type for message passing
    int blockcounts[BLOCK_COUNT_MESSAGE]={7,MAX_GROUP_SIZE*(PARTICLE_INFO_COUNT+1)};
    MPI_Aint offsets[BLOCK_COUNT_MESSAGE],extent;
    //setup description for the fields in the message structure
    int ofst=0;
    for(i=0;i<BLOCK_COUNT_MESSAGE;i++)
    {
        offsets[i]=ofst;
        MPI_Type_extent(oldtypes[i], &extent);
        ofst = ofst + blockcounts[i]*extent;
    }

    // Now define structured type and commit it.
    MPI_Type_create_struct(BLOCK_COUNT_MESSAGE, blockcounts, offsets, oldtypes, &struct_type);
    MPI_Type_commit(&struct_type);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    total_additions=0; // number of tasks added on this proc
    my_worktime = 0; // time of WORKING only - calculated within the run_task
    my_max_adds = MAX_ADDS; //max number of tasks added on this proc

    int lprim=1;         //LPRIM(BOOLEAN)- tells weather CUTFILE should be read or not:primary(if 1) or secondary(if 0) particle simulation
    int id1,id2,rnnum,seed;

    //Reading the Command line Arguments
    if(argc<2)
    {
        // MPI_Abort(MPI_COMM_WORLD,rc);
        //Give default values to the parameters
        strcpy(input_fname,"parallel-inputs");
        printf("WARNING: input file is not defined. Default parameters and file \"%s\" will be used in non debugging mode.\n",input_fname);
        dbg_infos=0;
        //Read parameters from input file.
        read_input(&dectcut,&dectmax,&lprim,cutfilename,&id1,&id2,&rnnum,&seed,input_fname);
    }
    else
    {
        printf("Input: arguments read from the command line are ");
        for(i=1;i<argc;i++) printf("%s ",argv[i]);
        strcpy(input_fname,argv[1]);
        printf("\nFor inputs the FILE \"%s\" will be used\n",input_fname);

        if(argc>=3)
            if(!strcmp(argv[2],"T")||!strcmp(argv[2],"t"))
            {
                dbg_infos=1;
                printf("Debugging mode will be used to protocol steps done by MPI-slaves. Check the \"mpiid-$ID$-runprotocol.txt\" , where $ID$ is the unique identification of parallel running slave rank\n");
            }
            else
            {
                dbg_infos=0;
                printf("Debugging switch \"%d\". No additional information about parallel run will be produced\n",dbg_infos);
            }

        //Read parameters from input file.
        read_input(&dectcut,&dectmax,&lprim,cutfilename,&id1,&id2,&rnnum,&seed,input_fname);
    }

    if (dbg_infos)
    {
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", MASTER);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        check = fopen(statfile,"a");
        fprintf(check,"\n[%f]MASTER: Going to broadcast to slaves of MPI_World of size %d. The input file name \"%s\" output folder \"%s\" emax \"%f\" emin \"%f\" CUTFILE switch \"%d\" and Debug switch \"%d\"",MPI_Wtime(),num_proc,input_fname,statdir,dectmax,dectcut,lcout,dbg_infos);
        fflush(check);
    }
    // Broadcasting the name of steering file to all slaves
    MPI_Bcast(input_fname, 255, MPI_CHAR, MASTER, MPI_COMM_WORLD);
    // Broadcasting the name of output directory to all slaves
    MPI_Bcast(statdir, 255, MPI_CHAR, MASTER, MPI_COMM_WORLD);
    // Broadcasting the Energy threshold for single particle jobs to all slaves
    MPI_Bcast(&dectmax, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    // Broadcasting the Energy threshold for group of particle jobs to all slaves
    MPI_Bcast(&dectcut, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    // Broadcasting the Cutfile generation switch to all slaves
    MPI_Bcast(&lcout, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    // Broadcasting the Debugger switch to all slaves
    MPI_Bcast(&dbg_infos, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    // Broadcasting the Debugger switch to all slaves
    MPI_Bcast(&rnnum, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    if (dbg_infos)
    {
        fprintf(check,"\n[%f] MASTER: Broadcasted to slaves the input file name \"%s\" output folder \"%s\" emax \"%f\" emin \"%f\" CUTFILE switch \"%d\" Debug switch \"%d\" Run number \"%d\"",MPI_Wtime(),input_fname,statdir,dectmax,dectcut,lcout,dbg_infos,rnnum);
        fflush(check);
    }

    // unique id for the subshowers
    int uid=0;

    //starting the primary particle and allotting a unique id
    ++uid;

    rnnum0=rnnum; // global var for some functions

    initial_tasks_number[0]=1; //only one primary particle

    if(lprim==0)
    {//setting buffer for secondary particle
        buff[0].lprim=lprim;
        buff[0].id1=id1;
        buff[0].id2=id2;
        parse_cfname(cutfilename,&buff[0].rnnum,&buff[0].seed,&buff[0].parent_id);
        buff[0].uid=uid;
        if (dbg_infos)
        {
            fprintf(check,"\n[%f] CUTFILENAME:%s PARSED from RUNNUMBER= %d, SEED= %d, MPIID= %d",MPI_Wtime(),cutfilename,buff[0].rnnum,buff[0].seed,buff[0].parent_id);
            fprintf(check,"\n[%f] RUN_INFO: SECONDARY RUN, LPRIM = %d I1CUTPAR = %d I2CUTPAR = %d RUNNUMBER = %d SEED = %d ID = %d",MPI_Wtime(),buff[0].lprim,buff[0].id1,buff[0].id2,buff[0].rnnum,buff[0].seed,buff[0].uid);
        }
    }
    else
    {//setting buffer for primary particle
        buff[0].lprim=lprim;
        buff[0].id1=0;
        buff[0].id2=0;
        buff[0].rnnum=rnnum;
        buff[0].seed=seed;
        buff[0].uid=uid;
        buff[0].parent_id=MASTER;
        if (dbg_infos) fprintf(check,"\n[%f] RUN_INFO: PRIMARY RUN, LPRIM = %d LCOUT = %d I1CUTPAR = %d I2CUTPAR = %d RUNNUMBER = %d SEED = %d ID = %d",MPI_Wtime(),buff[0].lprim,lcout,buff[0].id1,buff[0].id2,buff[0].rnnum,buff[0].seed,buff[0].uid);
    }
    if (dbg_infos) fclose(check);

    //Recording the start time of the SIMULATION
    global_runtime = MPI_Wtime();

    if (dbg_infos)
    {  //Record status of Master to Slave communication in statistic file
        strcpy(statfile,statdir);
        strcat(statfile,"Master2SlaveOrder");
        comm = fopen(statfile,"w");
        fprintf(comm,"%d %d %d %d %d %d %d %d %p\n",buff[0].uid,buff[0].parent_id,buff[0].lprim,buff[0].rnnum,buff[0].seed,1,buff[0].id1,buff[0].id2,buff[0].stack);
        fclose(comm);
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", MASTER);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] START: The initial shower with id = %d and parent id = %d will run on the the rank = %d",global_runtime,buff[0].uid,buff[0].parent_id,1);
        fclose(file);
    }
}

void code_preprocessing_slave(int argc, char *argv[])
{
    int  rank, num_proc, i;
    int rnnum;
    FILE* file;

    int blockcounts[BLOCK_COUNT_MESSAGE]={7,MAX_GROUP_SIZE*(PARTICLE_INFO_COUNT+1)};
    MPI_Aint offsets[BLOCK_COUNT_MESSAGE],extent;
    //setup description for the fields in the message structure
    int ofst=0;
    for(i=0;i<BLOCK_COUNT_MESSAGE;i++)
    {
        offsets[i]=ofst;
        MPI_Type_extent(oldtypes[i], &extent);
        ofst = ofst + blockcounts[i]*extent;
    }

    // Now define structured type and commit it.
    MPI_Type_create_struct(BLOCK_COUNT_MESSAGE, blockcounts, offsets, oldtypes, &struct_type);
    MPI_Type_commit(&struct_type);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    total_additions=0; // number of tasks added on this proc
    my_worktime = 0; // time of WORKING only - calculated within the run_task
    srand(MPI_Wtime());
    my_max_adds = rand()%MAX_ADDS + 1; //max number of tasks added on this proc


    // Receiving the name of steering file from Master via Broadcast
    MPI_Bcast(input_fname, 255, MPI_CHAR, MASTER, MPI_COMM_WORLD);
    // Receiving the name of output directory From Master for all slaves
    MPI_Bcast(statdir, 255, MPI_CHAR, MASTER, MPI_COMM_WORLD);
    // Receiving the Energy threshold for single particle as a slave
    MPI_Bcast(&dectmax, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    // Receiving the Energy threshold for group of particle as a slave
    MPI_Bcast(&dectcut, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    // Receiving Cutfile switch as a slave
    MPI_Bcast(&lcout, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    // Receiving the Debugger switch as a slave
    MPI_Bcast(&dbg_infos, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    // Receiving the Run number as a slave
    MPI_Bcast(&rnnum, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    runnumber=rnnum;
    job_count= 0;			//Counter of initial particle-stacks managed by slave

    if (dbg_infos)
    {
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", rank);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] SLAVE: Receiving the input file name \"%s\" output folder \"%s\" emax \"%f\" emin \"%f\" CUTFILE switch \"%d\" Debug switch \"%d\" Run number \"%d\"",MPI_Wtime(),input_fname,statdir,dectmax,dectcut,lcout,dbg_infos,rnnum);
        fclose(file);
    }

}

/*
Called from main() by the MASTER to finalize the slave environment.
It broadcast messages to each slave giving order to FINALIZE environment.
It also receives longfiles generated by each slave and add their content to generate the final longfile.
*/
void code_postprocessing_master()
{
    MPI_Status status;
    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    double start_time = global_runtime;
    double stop_time = MPI_Wtime();
    global_runtime = stop_time - start_time;
    int i,j;
    int dummy=0,unused=0;
    int mpierr;
    char statfile[255],statfiles[255],numstr[9];
    FILE* file;

    //constructing output file name for resultant joinedlongfile generated by MASTER
    char joinedlongfile[255];
    sprintf(joinedlongfile,"%sDAT%06d-999999999.long",statdir,rnnum0);


    stop_time=MPI_Wtime();
    //Finish the simulation
    if (dbg_infos)
    {  //Record status of Master to Slave communication in statistic file
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", MASTER);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] FINALIZE: The shower simulation took %f minutes started at %f is finished at %f",MPI_Wtime(),(global_runtime)/60.,start_time,stop_time);
        fclose(file);
    }

    strcpy(statfile,statdir);
    strcat(statfile,"time.txt");
    file = fopen(statfile,"w");
    fprintf(file,"    START TIME\t\t STOP TIME\t  TIME (min)\n%f   %f   %f\n", start_time, stop_time, global_runtime/60.);
    fclose(file);

    for(i=1;i<num_proc;i++)
    {
        MPI_Recv(&dummy,1,MPI_SHORT,i,VALN,MPI_COMM_WORLD,&status);
        if (NSTEP1<dummy) NSTEP1=dummy;
        if (dummy==0) unused++;
        if (dbg_infos)
        {
            file =fopen(statfile,"a");
            fprintf(file,"\n[%f]: RECEIVE #%d from slave %d maximal vertical steps in long files as %d and will use %d. Unused tasks are %d",MPI_Wtime(), i, status.MPI_SOURCE, dummy, NSTEP1,unused);
            fclose(file);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    //MASTER receiving the longfile from each slave and adding their content to generate a single longfile.
    for(i=1;i<num_proc;i++)
    {
        if (dbg_infos)
        {
            file =fopen(statfile,"a");
            fprintf(file,"\n[%f]: RECEIVE #%d MASTER waiting to receiving the string, related to number of particles,from each slave. Unused tasks are %d. Latest communication were with slave %d",MPI_Wtime(),i,unused,status.MPI_SOURCE);
            fclose(file);
        }
        mpierr=MPI_Recv(lngfile.pstr,300,MPI_CHAR,i,STRP,MPI_COMM_WORLD,&status);
        //strcpy(lngfile.pstr,pro.pstr);
        if (dbg_infos)
        {
            strcpy(statfiles,statdir);
            strcat(statfiles,"mpiid-");
            sprintf(numstr, "%d", status.MPI_SOURCE);
            strcat(statfiles,numstr);
            strcat(statfiles,"-recv.long");
            file = fopen(statfiles,"a");
            if(mpierr==MPI_SUCCESS)
            {
                fprintf(file,"[%f]:pstr from slave %d is successfully received:\n",MPI_Wtime(),status.MPI_SOURCE);
                fprintf(file,"%s",pro.pstr);
            }
            else
                fprintf(file,"[%f]:pstr from slave %d is not successfully received\n",MPI_Wtime(),status.MPI_SOURCE);
            fclose(file);
        }
    }
    if (dbg_infos)
    {
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] Barrier: waiting to other slaves. Error code of MPI_Recv=%d",MPI_Wtime(),mpierr);
        fclose(file);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    for(i=1;i<num_proc;i++)
    {	int ii;
        if (dbg_infos)
        {
            file =fopen(statfile,"a");
            fprintf(file,"\n[%f]: RECEIVE #%d MASTER waiting to receiving the buffer containing the number of particles from each slave. Unused tasks are %d. Latest communication were with slave %d",MPI_Wtime(), i,unused,status.MPI_SOURCE);
            fclose(file);
        }
        mpierr=MPI_Recv(&(pro.pbuffer[0][0]),10*NSTEP1,MPI_DOUBLE,i,VALP,MPI_COMM_WORLD,&status);
        if (dbg_infos)
        {
            strcpy(statfiles,statdir);
            strcat(statfiles,"mpiid-");
            sprintf(numstr, "%d", status.MPI_SOURCE);
            strcat(statfiles,numstr);
            strcat(statfiles,"-recv.long");
            file = fopen(statfiles,"a");
            if(mpierr==MPI_SUCCESS)
            {
                fprintf(file,"\n[%f]:pro.pbuffer[%d][10] from slave %d is successfully received\n",MPI_Wtime(),NSTEP1,status.MPI_SOURCE);
                for(ii=0;ii<NSTEP1;ii++)
                {
                    fprintf(file,"\n%6.1f ",pro.pbuffer[ii][0]);
                    for(j=1;j<10;j++)
                        fprintf(file,"%12.5e",pro.pbuffer[ii][j]);
                }
            }
            else
                fprintf(file,"\n[%f]:pro[].pbuffer[%d][10] from slave %d is not successfully received",MPI_Wtime(),NSTEP1,status.MPI_SOURCE);
            fclose(file);
        }
        //MASTER adding the content of particle buffer received from each slave
        for(ii=0;ii<NSTEP1;ii++)
        {
            lngfile.pbuffer[ii][0]=pro.pbuffer[ii][0];
            for(j=1;j<10;j++)
                lngfile.pbuffer[ii][j]=lngfile.pbuffer[ii][j]+pro.pbuffer[ii][j];
        }
    }
    if (dbg_infos)
    {
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] Barrier: waiting to other slaves. Error code of MPI_Recv=%d",MPI_Wtime(),mpierr);
        fclose(file);
    }
    MPI_Barrier(MPI_COMM_WORLD);


    for(i=1;i<num_proc;i++)
    {
        if (dbg_infos)
        {
            file =fopen(statfile,"a");
            fprintf(file,"\n[%f]: RECEIVE #%d MASTER waiting to receiving the string related to energy of particles from each slave. Unused tasks are %d. Latest communication were with slave %d",MPI_Wtime(), i,unused,status.MPI_SOURCE);
            fclose(file);
        }
        mpierr=MPI_Recv(pro.estr,300,MPI_CHAR,i,STRE,MPI_COMM_WORLD,&status);
        strcpy(lngfile.estr,pro.estr);
        if (dbg_infos)
        {
            strcpy(statfiles,statdir);
            strcat(statfiles,"mpiid-");
            sprintf(numstr, "%d", status.MPI_SOURCE);
            strcat(statfiles,numstr);
            strcat(statfiles,"-recv.long");
            file = fopen(statfiles,"a");
            if(mpierr==MPI_SUCCESS)
            {
                fprintf(file,"\n[%f]:estr from slave %d is successfully received",MPI_Wtime(),status.MPI_SOURCE);
                fprintf(file,"\n%s",pro.estr);
            }
            else
                fprintf(file,"\n[%f]:estr from slave %d is not successfully received",MPI_Wtime(),status.MPI_SOURCE);
            fclose(file);
        }
    }
    if (dbg_infos)
    {
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] Barrier: waiting to other slaves. Error code of MPI_Recv=%d",MPI_Wtime(),mpierr);
        fclose(file);
    }
    MPI_Barrier(MPI_COMM_WORLD);


    for(i=1;i<num_proc;i++)
    {int ii;
        if (dbg_infos)
        {
            file =fopen(statfile,"a");
            fprintf(file,"\n[%f]: RECEIVE #%d MASTER waiting to receiving the buffer containing the energy of particles from each slave. Unused tasks are %d. Latest communication were with slave %d",MPI_Wtime(), i,unused,status.MPI_SOURCE);
            fclose(file);
        }
        mpierr=MPI_Recv(&(pro.ebuffer[0][0]),10*NSTEP1,MPI_DOUBLE,i,VALE,MPI_COMM_WORLD,&status);
        if (dbg_infos)
        {
            strcpy(statfiles,statdir);
            strcat(statfiles,"mpiid-");
            sprintf(numstr, "%d", status.MPI_SOURCE);
            strcat(statfiles,numstr);
            strcat(statfiles,"-recv.long");
            file = fopen(statfiles,"a");
            if(mpierr==MPI_SUCCESS)
            {
                fprintf(file,"\n[%f]:pro[].ebuffer[%d][10] from slave %d successfully received",MPI_Wtime(),NSTEP1,status.MPI_SOURCE);
                for(ii=0;ii<NSTEP1;ii++)
                {
                    fprintf(file,"\n%6.1f ",pro.ebuffer[ii][0]);
                    for(j=1;j<10;j++)
                        fprintf(file,"%12.5e",pro.ebuffer[ii][j]);
                }
                //		 for(i=0;i<NSTEP1;i++)
                //		 fprintf(file,"%6.1f %12.5e %12.5e %12.5e %12.5e %12.5e %12.5e %12.5e %12.5e %12.5e\n",pro.ebuffer[i][0],pro.ebuffer[i+1][1],pro.ebuffer[i+2][2],pro.ebuffer[i+3][3],pro.ebuffer[i+4][4],pro.ebuffer[i+5][5],pro.ebuffer[i+6][6],pro.ebuffer[i+7][7],pro.ebuffer[i+8][8],pro.ebuffer[i+9][9]);
            }
            else
                fprintf(file,"\n[%f]:pro[].ebuffer[%d][10] from slave %d not successfully received",MPI_Wtime(),NSTEP1,status.MPI_SOURCE);
            fclose(file);
        }
        //MASTER adding the content of energy buffer received from each slave
        for(ii=0;ii<NSTEP1;ii++)
        {
            lngfile.ebuffer[ii][0]=pro.ebuffer[ii][0];
            for(j=1;j<10;j++)
                lngfile.ebuffer[ii][j]=lngfile.ebuffer[ii][j]+pro.ebuffer[ii][j];
        }
    }
    if (dbg_infos)
    {
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] Barrier: waiting to other slaves. Error code of MPI_Recv= %d",MPI_Wtime(),mpierr);
        fclose(file);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    write_joined_longfile(joinedlongfile);

    MPI_Type_free(&struct_type);
}


void code_postprocessing_slave()
{
    int y1,y2,y3,y4,rank;
    int dummybuffer; //Dummy buffer for receive variable in collective communication
    char statfile[255],numstr[9];
    FILE *file;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if (dbg_infos)
    {
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", rank);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] FINALIZE: Going to finalize sending %d for number of particles in long file",MPI_Wtime(),NSTEP1);
        fclose(file);
    }

    y1=MPI_Send(&NSTEP1,1,MPI_SHORT,MASTER,VALN,MPI_COMM_WORLD);
    if (dbg_infos)
    {
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] BARRIER: to wait for other processes completing submission of number of particles: MPI communication error code %d",MPI_Wtime(),y1);
        fclose(file);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    //if (NSTEP1)
    //{
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] SEND: Going to send to MASTER the string related to particles generated inside longfile \n %s",MPI_Wtime(),lngfile.pstr);
            fclose(file);
        }
        y1=MPI_Send(lngfile.pstr,300,MPI_CHAR,MASTER,STRP,MPI_COMM_WORLD);
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            if(y1==MPI_SUCCESS)
                fprintf(file,"\n[%f]:pstr by slave %d is successfully sent",MPI_Wtime(),rank);
            else
                fprintf(file,"\n[%f]:pstr by slave %d is not successfully sent",MPI_Wtime(),rank);
            fclose(file);
        }
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] BARRIER: to wait for other processes completing submission of string about particles: MPI communication error code %d",MPI_Wtime(),y1);
            fclose(file);
        }
        MPI_Barrier(MPI_COMM_WORLD);

        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] SEND: Going to send to MASTER the buffer containing counts of particles generated inside longfile",MPI_Wtime());
            fclose(file);
        }
        y2=MPI_Send(&(lngfile.pbuffer[0][0]),10*NSTEP1,MPI_DOUBLE,MASTER,VALP,MPI_COMM_WORLD);
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            if(y2==MPI_SUCCESS)
            {int i;
                fprintf(file,"\n[%f]:pbuffer by slave %d is successfully sent",MPI_Wtime(),rank);
                for(i=0;i<NSTEP1;i++)
                {
                    fprintf(file,"\n%6.1f ",lngfile.pbuffer[i][0]);
                    for(dummybuffer=1;dummybuffer<10;dummybuffer++)
                        fprintf(file,"%12.5e",lngfile.pbuffer[i][dummybuffer]);
                }
            }
            else
                fprintf(file,"\n[%f]:pbuffer by slave %d is not successfully sent",MPI_Wtime(),rank);
            fclose(file);
        }
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] BARRIER: to wait for other processes completing submission of count of particles: MPI communication error code %d",MPI_Wtime(),y1);
            fclose(file);
        }
        MPI_Barrier(MPI_COMM_WORLD);

        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] SEND: Going to send to MASTER the string related to energy of particles generated inside longfile",MPI_Wtime());
            fclose(file);
        }
        y3=MPI_Send(lngfile.estr,300,MPI_CHAR,MASTER,STRE,MPI_COMM_WORLD);
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            if(y3==MPI_SUCCESS)
            {
                fprintf(file,"\n[%f]:estr by slave %d is successfully sent",MPI_Wtime(),rank);
                fprintf(file,"\n%s",lngfile.estr);
            }
            else
                fprintf(file,"\n[%f]:estr by slave %d is not successfully sent",MPI_Wtime(),rank);
            fclose(file);
        }
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] BARRIER: to wait for other processes completing submission of string about energy: MPI communication error code %d",MPI_Wtime(),y1);
            fclose(file);
        }
        MPI_Barrier(MPI_COMM_WORLD);

        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] SEND: Going to send to MASTER the buffer containing energy of particles generated inside longfile",MPI_Wtime());
            fclose(file);
        }

        y4=MPI_Send(&(lngfile.ebuffer[0][0]),10*NSTEP1,MPI_DOUBLE,MASTER,VALE,MPI_COMM_WORLD);
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            if(y4==MPI_SUCCESS)
            {int i;
                fprintf(file,"\n[%f]:ebuffer by slave %d is successfully sent",MPI_Wtime(),rank);
                for(i=0;i<NSTEP1;i++)
                {
                    fprintf(file,"\n%6.1f ",lngfile.ebuffer[i][0]);
                    for(dummybuffer=1;dummybuffer<10;dummybuffer++)
                        fprintf(file,"%12.5e",lngfile.ebuffer[i][dummybuffer]);
                }
            }
            else
                fprintf(file,"\n[%f]:ebuffer by slave %d is not successfully sent",MPI_Wtime(),rank);
            fclose(file);
        }
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] BARRIER: to wait for other processes completing submission of buffer of energies: MPI communication error code %d",MPI_Wtime(),y1);
            fclose(file);
        }
        MPI_Barrier(MPI_COMM_WORLD);

    //}
    /*else
    {
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] UNUSED: Slave %d were not participating in simulations or longfile is empty %d",MPI_Wtime(),rank,NSTEP1);
            fclose(file);
        }
    }*/
    MPI_Type_free(&struct_type);
}


void process_code_signal(MPI_Status stat, struct message buff)
{
    int i;
    switch(stat.MPI_TAG)
    {
    case STORRUNH:
        // store run header to file - code specific signal
    {
        if (switch_first_runH)
        {
            for (i=0;i<buff.rnnum;i++) Run_header[i] = buff.stack[i];
            switch_first_runH=0;
        }
        for (i=0;i<buff.rnnum;i++) buff.stack[i] = Run_header[i];
        i=MPI_Send(&buff,1,struct_type,stat.MPI_SOURCE,STORRUNH,MPI_COMM_WORLD);
        return;
    }
        break;

    case STOREVNH:
    { 	if (switch_first_evnH)
        {
            for (i=0;i<buff.rnnum;i++) Event_header[i] = buff.stack[i];
            switch_first_evnH=0;
        }
        for (i=0;i<buff.rnnum;i++) buff.stack[i] = Event_header[i];
        i=MPI_Send(&buff,1,struct_type,stat.MPI_SOURCE,STOREVNH,MPI_COMM_WORLD);
        return;
    }
        break;
    default:
    {
        if (dbg_infos)
        {
            strcpy(statfile,statdir);
            strcat(statfile,"mpiid-");
            sprintf(numstr, "%d", MASTER);
            strcat(statfile,numstr);
            strcat(statfile,"-runprotocol.txt");
            FILE *file = fopen(statfile,"a");
            fprintf(file,"\n[%f] ERROR: Unknown message type \n",MPI_Wtime());
            fclose(file);
        }
        return;
    }
        break;
    } //End of MPI status switches
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

// actualy here is external function called
void corsika(int* my_lprim, double* my_dectcut, double* my_dectmax, int* my_id1, int* my_id2, char* cut_fname, char* out_fname, char* input_fname, int* my_uid)
{
    int num_adds, i;
    int rank, num_proc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    num_adds = rand()%(MAX_ADDS/10+1)+1;


    if(total_additions>my_max_adds) num_adds=0;
    total_additions+=num_adds;

    double working_period = (rand()%MAX_WEIGHT+1)/(num_adds+1); // share the work
    // work - add new task - work - add new task - work etc
    // the working period here linearly depends on the firs param of the task
    pretend_that_you_work(working_period);

    for (i=0; i<num_adds; i++)
    {

        int id1 = my_id1[0] + 1;
        int id2 = my_id2[0] + 1;
        int seed = rand()%10000;
        new_particle(id1, id2, 111, seed, rank);

        pretend_that_you_work(working_period);
    }

}

void run_task(task_type buff, result_type * result0)
{
    int rank, num_proc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    double t_wrk;
    FILE * file, *comm;
    int i,j;
    char cutfilename[255], statfile2[255], outfname[255];

    srand(time(NULL));

    if (dbg_infos)
    {
        job_count++;		//Counting initial particle-stacks received by slave
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] START: Received a request with id \"%d\" generated by parent particle \"%d\" with seed \"%d\" and primary status \"%d\" and have to run particles from \"%d\" till \"%d\" from stack/cutfile %p",MPI_Wtime(),buff.uid,buff.parent_id,buff.seed,buff.lprim,buff.id1,buff.id2,buff.stack);
        fclose(file);
    }

    particles_from_stack = (double*)calloc((PARTICLE_INFO_COUNT+1)*(buff.id2-buff.id1+1)*MAX_GROUP_SIZE,sizeof(double)); //Stack of new secondary particles - stand alone or group
    if (dbg_infos)
    {
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] Initialized stack ",MPI_Wtime());
        for(i=0;i<(PARTICLE_INFO_COUNT+1)*(buff.id2-buff.id1+1)*MAX_GROUP_SIZE;i++)
            fprintf(file,"particles_from_stack[%d]=%f ", i, particles_from_stack[i] );
        fclose(file);
    }

    //Storing current particle stack into intermediate buffer
    for(i=0;i<(buff.id2-buff.id1+1);i++)
    {
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] START: Data of received particle nr. %d :",MPI_Wtime(), i);
            fclose(file);
        }
        for(j=0;j<(PARTICLE_INFO_COUNT+1);j++)
        {
            particles_from_stack[(PARTICLE_INFO_COUNT+1)*i+j]=buff.stack[(PARTICLE_INFO_COUNT+1)*i+j];
            if (dbg_infos)
            {
                file = fopen(statfile,"a");
                fprintf(file,"%f -> %f ", buff.stack[(PARTICLE_INFO_COUNT+1)*i+j],particles_from_stack[(PARTICLE_INFO_COUNT+1)*i+j]);
                fclose(file);
            }
        }
    }
    II1 = buff.id1;

    //Reconstruct the CUTFILE NAME to pass to CORSIKA
    reconstruct_cfname(cutfilename, buff.rnnum, buff.seed, buff.parent_id);

    //Reconstruct the OUTPUT FILE NAME to pass to CORSIKA
    if (dbg_infos)
    {
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] START: Seed =%f will be used for output filename ",MPI_Wtime(), particles_from_stack[(PARTICLE_INFO_COUNT+1)*(buff.id2-II1) + 18]);
        fclose(file);
    }
    double pseed=particles_from_stack[(PARTICLE_INFO_COUNT+1)*(buff.id2-II1) + 18];
    if ( pseed == 0. ) pseed=buff.seed;
    reconstruct_ofname(outfname,buff.rnnum,pseed,buff.uid);

    if (dbg_infos)
    {
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] START: will start %dth parallel run for sub-shower with ID =%d requested by ParentID =%d with seed=%d using options lprim=%d with particle %d till %d, CUTFILE=%s, outputfile=%s, steering file=%s",MPI_Wtime(),job_count,buff.uid,buff.parent_id,buff.seed,buff.lprim,buff.id1,buff.id2,cutfilename,outfname,input_fname);
        fclose(file);
        //Record status of "Master to " communication in statistic files
        strcpy(statfile2,statdir);
        strcat(statfile2,"Master2SlaveRecv");
        comm = fopen(statfile2,"a");
        fprintf(comm,"%d %d %d %d %d %d %d %d %p\n",buff.uid,buff.parent_id,buff.lprim,buff.rnnum,buff.seed,buff.uid,buff.id1,buff.id2,buff.stack);
        fclose(comm);
    }
    char local_log[255];
    sprintf(local_log, "local-log-p%06d.log", rank);
    FILE * local_log_file = fopen(local_log,"a");
    fprintf( local_log_file, "output file name is %s\n",outfname);
    fprintf( local_log_file, "\n[%f] STARTING CORSIKA with params %d, %f, %f, %d, %d, %s, %s, %s, %d\n STACK is \n", MPI_Wtime(),
             buff.lprim, dectcut, dectmax, buff.id1, buff.id2, cutfilename, outfname, input_fname, buff.uid);

    int c=0;
    for(i=buff.id1;i<=buff.id2;i++)
    {
        for(j=0;j<PARTICLE_INFO_COUNT;j++)
        {
            fprintf( local_log_file, "%f; ", buff.stack[c*(PARTICLE_INFO_COUNT+1)+j]);
        }
        c++;
        fprintf(local_log_file, " next:\n");
    }

    fclose(local_log_file);

    t_wrk = MPI_Wtime();
    result0[0][0] = t_wrk;

    corsika(&(buff.lprim),&dectcut,&dectmax,&(buff.id1),&(buff.id2),cutfilename,outfname,input_fname,&(buff.uid));

    result0[0][1] = MPI_Wtime();
    my_worktime += result0[0][1] - t_wrk;

    // the result here is a set of randoms

}

/*
function endoffile()
Called from Subroutine CORSIKA() with the CUTFILE and PARICLES INFORMATION.
FOR every particle/Group(separate job) it calls the function new_particle to send a REQUEST message
*/
void endoffile_(int* array,int* size,int* rnnum,int* seed,int* uid)
{
    int i,j,k, rank;
    char statfile[255],numstr[9];
    FILE *file,*cf;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if (dbg_infos)
    {
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", rank);
        strcat(statfile,numstr);
        strcat(statfile,"-runprotocol.txt");
        file = fopen(statfile,"a");
        fprintf(file,"\n[%f] CORSIKA: There are new %d particle groups from subshower with id= %d from simulation under run number %d and seed %d \n",MPI_Wtime(),*size-1,*uid,*rnnum,*seed);
        fclose(file);
    }
    if(lcout==1)
    {//CUT file -checkpoint containing the new particles from CORSIKA stack will be generated
        char cutfile[255];
        char cutfilename[255];
        strcpy(cutfile,statdir);
        reconstruct_cfname(cutfilename,*rnnum,*seed,*uid);
        strcat(cutfile,cutfilename);
        cf=fopen(cutfile,"w");
        for(i=0;i<=(*size)-2;i++)
        {
            if(array[i]==array[i+1]-1)
            {//one particle stack
                fprintf(cf,"%d ",array[i]);
                for(j=0;j<(PARTICLE_INFO_COUNT+1);j++) fprintf(cf,"%E ", particle_stack_or_cut_file[((array[i]-1)*(PARTICLE_INFO_COUNT+1))+j]  );
                fprintf(cf,"\n");
            }
            if(array[i]<array[i+1]-1)
            {//group of particles in stack
                for(k=array[i];k<=array[i+1]-1;k++)
                {
                    fprintf(cf,"%d ",k);
                    for(j=0;j<(PARTICLE_INFO_COUNT+1);j++) fprintf(cf,"%E ", particle_stack_or_cut_file[((k-1)*(PARTICLE_INFO_COUNT+1))+j]  );
                    fprintf(cf,"\n");
                }
            }
        }
        fclose(cf);
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] CORSIKA: A cutfile containing requests of new sub-shower simulations have been generated",MPI_Wtime());
            fclose(file);
        }
    }
    for(i=0;i<=(*size)-2;i++)
    {
        new_particle(array[i],array[i+1]-1,*rnnum,*seed,*uid);
        if (dbg_infos)
        {
            file = fopen(statfile,"a");
            fprintf(file,"\n[%f] CORSIKA: Requests of new sub-shower simulations have been sent. First particle in group has a number %d in stack",MPI_Wtime(),array[i]);
            fclose(file);
        }
        array[i]=0;
    }
}

/*
function printstatusstart()
Called from CORSIKA, for debugging purpose
*/
void printstatusstart_(int* uid,double dectcut,double dectmax,int* id1,int* id2,int* lprim,char cfname[255],char input_fname[255],int* lcout)
{
    FILE* file;
    char statfile[255];
    strcpy(statfile,statdir);
    strcat(statfile,"corsika_status_start");
    if(*uid==1)
    {
        file = fopen(statfile,"w");
        fprintf(file,"#Unique ID of shower; ID of first particle; ID of last particle; Primary/secondary switch; cutfilename/stack; when using input %s; outputting into %s; Energy thresholds max %f and cut %f; Cutfile generation switch %d; and debugging switch %d\n", input_fname, statdir, dectcut, dectmax, *lcout, dbg_infos);
        fprintf(file,"%d %d %d %d %s\n",*uid,*id1,*id2,*lprim,"Initial Particle");
    }
    else
    {
        file = fopen(statfile,"a");
        fprintf(file,"%d %d %d %d %s\n",*uid,*id1,*id2,*lprim,cfname);
    }
    fclose(file);
}

/*
function printstatusfinish()
Called from CORSIKA, for debugging purpose
*/
void printstatusfinish_(int* uid,double dectcut,double dectmax,int* id1,int* id2,int* lprim,char cfname[255],char input_fname[255],int* lcout)
{
    FILE* file;
    char statfile[255];
    strcpy(statfile,statdir);
    strcat(statfile,"corsika_status_finish");
    if(*uid==1)
    {
        file = fopen(statfile,"w");
        fprintf(file,"#Unique ID of shower; ID of first particle; ID of last particle; Primary/secondary switch cutfilename/stack; when using input %s; outputting into %s; Energy thresholds max %f and cut %f; Cutfile generation switch %d; and debugging switch %d\n", input_fname, statdir, dectcut, dectmax, *lcout, dbg_infos);
        fprintf(file,"%d %d %d %d %s\n",*uid,*id1,*id2,*lprim,"Initial Particle");
    }
    else
    {
        file = fopen(statfile,"a");
        fprintf(file,"%d %d %d %d %s\n",*uid,*id1,*id2,*lprim,cfname);
    }
    fclose(file);
}

//function storetext() called from CORSIKA, to store text for longfiles.
void storetext_(int*type,int*nstep,double *thstep,int *nrrun)
{	NSTEP1 = *nstep;
    char statfile[255],numstr[9];
    FILE* comm;
    if (dbg_infos)
    {	int rank;
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", rank);
        strcat(statfile,numstr);
        strcat(statfile,".long");
        comm = fopen(statfile,"a");
        fprintf(comm,"[%f]:Text of type=%d sent by CORSIKA\n",MPI_Wtime(),(*type));
        fclose(comm);
    }

    switch(*type)
    {
    case 0:
    {
        sprintf(lngfile.pstr, " LONGITUDINAL DISTRIBUTION IN %5d VERTICAL STEPS OF%6.1f G/CM**2 FOR SHOWER  %06d\n DEPTH     GAMMAS   POSITRONS   ELECTRONS         MU+         MU-     HADRONS     CHARGED      NUCLEI   CHERENKOV\n",NSTEP1,*thstep,runnumber);
        if (dbg_infos)
        {
            FILE* comm = fopen(statfile,"a");
            fprintf(comm,"pstr=%s\n",lngfile.pstr);
            fclose(comm);
        }
    } break;
    case 1:
    {
        if (dbg_infos)
        {
            FILE* comm = fopen(statfile,"a");
            fprintf(comm,"pstr=%s\n",lngfile.pstr);
            fclose(comm);
        }

    } break;
    case 2:
    {
        sprintf(lngfile.estr, " LONGITUDINAL ENERGY DEPOSIT IN %5d VERTICAL STEPS OF%6.1f G/CM**2 FOR SHOWER  %06d\n DEPTH    GAMMA     EM IONIZ     EM CUT     MU IONIZ     MU CUT     HADR IONIZ   HADR CUT   NEUTRINO      SUM\n",NSTEP1,*thstep,runnumber);
        if (dbg_infos)
        {
            FILE* comm = fopen(statfile,"a");
            fprintf(comm,"estr=%s\n",lngfile.estr);
            fclose(comm);
        }

    } break;
    case 3:
    {
        sprintf(lngfile.estr, " LONGITUDINAL ENERGY DEPOSIT IN %5d SLANT  STEPS OF%6.1f  G/CM**2 FOR SHOWER %06d \n DEPTH    GAMMA     EM IONIZ     EM CUT     MU IONIZ     MU CUT     HADR IONIZ   HADR CUT   NEUTRINO      SUM\n",NSTEP1,*thstep,runnumber);
        if (dbg_infos)
        {
            FILE* comm = fopen(statfile,"a");
            fprintf(comm,"estr=%s\n",lngfile.estr);
            fclose(comm);
        }
    } break;

    }
}

//function joinmatrix() called inside CORSIKA by each slave to add the content of longfiles generated.
void joinmatrix_(double longmatrix[NSTEP_MAX*10],int*type)
{
    int j;
    char statfile[255],numstr[9];
    FILE *comm;
    if (dbg_infos)
    {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d", rank);
        strcat(statfile,numstr);
        strcat(statfile,".long");
        comm = fopen(statfile,"a");
        fprintf(comm,"[%f]:longmatrix of type=%d sent by CORSIKA \n",MPI_Wtime(),(*type));
        fclose(comm);
    }
    for(j=0;j<NSTEP1*10;j++)
    {
        if (dbg_infos)
        {
            comm = fopen(statfile,"a");
            fprintf(comm,"Buffer[%d,0-9] and corresponding matrix",j);
            fclose(comm);
        }
        switch (*type)
        {
        case 0:
        {int i = (int)(j/10);
            if (j%10)
                lngfile.ebuffer[i][j%10]=lngfile.ebuffer[i][j%10]+longmatrix[j];
            else
                lngfile.ebuffer[i][j%10]=longmatrix[j];
            if (dbg_infos)
            {
                comm = fopen(statfile,"a");
                fprintf(comm,"[%d] %12.5f -> %12.5f \n",j%10,longmatrix[j],lngfile.ebuffer[i][j%10]);
                fclose(comm);
            }
        } break;
        case 1:
        {int i = (int)(j/10);
            if(j%10)
                lngfile.pbuffer[i][j%10]=lngfile.pbuffer[i][j%10]+longmatrix[j];
            else
                lngfile.pbuffer[i][j%10]=longmatrix[j];
            if (dbg_infos)
            {
                comm = fopen(statfile,"a");
                fprintf(comm,"[%d] %12.5f -> %12.5f \n",j%10,longmatrix[j],lngfile.pbuffer[i][j%10]);
                fclose(comm);
            }
        } break;
        }
    }
}

void write_block_fort(int maxbuf, float *Block)
{
    char statfile[250],numstr[9];
    int rank,i,a,mreclength=21*maxbuf;//nsubbl*maxbuf = 6552 (if thinning) or 5733 (no thinning)
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    sprintf(statfile,"%sDAT%06.0f-%06d",statdir,Run_header[1],rank);//ERhdr[1] contains the run number
    FILE *comm, *file = fopen(statfile,"a");
    if (dbg_infos)
    {
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d",rank);
        strcat(statfile,numstr);
        strcat(statfile,"-datablocks.txt");
        comm = fopen(statfile,"a");
        fprintf(comm,"[%f]: Generating file %sDAT%06.0f-%06d\n",MPI_Wtime(),statdir,Run_header[1],rank);
        fclose(comm);
    }
    a=mreclength*sizeof(float);//Record length = size of 6552 floats
    if ( maxblock_switch < 1 ) //First time recording the DAT output
    {	int nz,ins;
        nz=(particle_block_counts+maxbuf+maxbuf)%mreclength;
        ins=mreclength-nz;
        for(i=0;i<ins;i++) Block[particle_block_counts++]=0.0;//filling rest of particle buffer with 0 to fit the mreclength size blocks (including the first 2 headers)
        if (dbg_infos)
        {
            comm = fopen(statfile,"a");
            fprintf(comm,"[%f]: Check the new size of Block array %d \n",MPI_Wtime(),particle_block_counts%mreclength);
            fclose(comm);
        }
        // Write first record
        fwrite(&a,sizeof(int),1,file);//Writing record length
        fwrite(Run_header,sizeof(float),maxbuf,file); //sizeof(float) is 4 bytes
        fwrite(Event_header,sizeof(float),maxbuf,file); //sizeof(float) is 4 bytes
        fwrite(Block,sizeof(float),mreclength-2*maxbuf,file);//complete the first record with particles
        fwrite(&a,sizeof(int),1,file);//Writing record length
        if (dbg_infos)
        {
            comm = fopen(statfile,"a");
            fprintf(comm,"[%f]: The first write_block() call wrote Run %f and Event %f headers before particle blocks\n",MPI_Wtime(),Run_header[0],Event_header[0]);
            fclose(comm);
        }
        // Write the rest of the particle subblocks from second to the last record
        for(i=0;i<particle_block_counts/mreclength;i++)
        {
            fwrite(&a,sizeof(int),1,file);
            fwrite(&(Block[mreclength-2*maxbuf+i*mreclength]),sizeof(float),mreclength,file);
            fwrite(&a,sizeof(int),1,file);
        }

        if (dbg_infos)
        {
            comm = fopen(statfile,"a");
            fprintf(comm,"[%f]: The first write_block() call wrote next %d particle blocks\n",MPI_Wtime(),particle_block_counts/mreclength);
            fclose(comm);
        }
    }
    if ( maxblock_switch >=1  && maxblock_switch < 23456 ) //Additional recordings into output
    {int nz,ins;
        nz=particle_block_counts%mreclength;
        ins=mreclength-nz;
        for(i=0;i<ins;i++) Block[particle_block_counts++]=0.0;//filling rest with 0 to fit the mreclength size blocks.
        for(i=0;i<particle_block_counts/mreclength;i++)
        {
            fwrite(&a,sizeof(int),1,file);
            fwrite(&(Block[i*mreclength]),sizeof(float),mreclength,file);
            fwrite(&a,sizeof(int),1,file);
        }
        if (dbg_infos)
        {
            comm = fopen(statfile,"a");
            fprintf(comm,"[%f]: The additional write_block() call wrote next %d particle blocks\n",MPI_Wtime(),particle_block_counts/mreclength);
            fclose(comm);
        }
    }
    if ( maxblock_switch > 23456 ) //Last recording into output before finalize
    {float Event_and_Run_end[mreclength];
        int numtasks;
        MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
        // RUNH = 211285.2812500000000000;
        // EVTH = 217433.0781250000000000;
        // LONG =  52815.2968750000000000;
        // EVTE =   3397.3918457031250000;
        // RUNE =   3301.3325195312500000;

        for( i=0; i<mreclength; i++ ) Event_and_Run_end[i] = 0.0; //Initialising with 0

        Event_and_Run_end[0] = 3397.3918457031250000;
        Event_and_Run_end[1] = 1.*Run_header[1]; //ERhdr[1] contains the run number
        for( i=2; i<7; i++ ) Event_and_Run_end[i] = 1.*particle_block_counts/7; //Estimation (<=) of the number of particles

        Event_and_Run_end[maxbuf] = 3301.3325195312500000;
        Event_and_Run_end[maxbuf+1] = 1.*Run_header[1];
        Event_and_Run_end[maxbuf+2] = 1.*Run_header[1];
        Event_and_Run_end[maxbuf+3] = 1.*numtasks;

        fwrite(&a,sizeof(int),1,file);
        fwrite(Event_and_Run_end,sizeof(float),mreclength,file);
        fwrite(&a,sizeof(int),1,file);
        if (dbg_infos)
        {
            comm = fopen(statfile,"a");
            fprintf(comm,"[%f]: The write_block() call wrote %f Run and %f Event end before final close\n",MPI_Wtime(),Event_and_Run_end[0],Event_and_Run_end[maxbuf]);
            fclose(comm);
        }
    }
    fclose(file);
}

//Function called from corsika to store the particle data in buffer of each parallel task
void joindat_(int *maxbuf, int *nsubbl, float outvect[6552] )
{
    int i,j,rank;
    MAXBUFSLAVE=*maxbuf;
    char statfile[255],numstr[9];
    FILE* comm;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if (dbg_infos)
    {
        strcpy(statfile,statdir);
        strcat(statfile,"mpiid-");
        sprintf(numstr, "%d",rank);
        strcat(statfile,numstr);
        strcat(statfile,"-outvect.txt");
        comm = fopen(statfile,"a");
        fprintf(comm,"\n[%f]: slave=%d calling function joindat() %dth times storing in local memory the record from array outvect[%d] generated inside CORSIKA\n",MPI_Wtime(),rank,join_counts++,(*maxbuf * *nsubbl));
        fclose(comm);
    }

    for(j=0;j<(*nsubbl);j++)
    {
        if (dbg_infos&&(rank<LISTFILE_MAX))
        {
            comm = fopen(statfile,"a");
            fprintf(comm,"\n Subblock Nr.%d outvect[%d]=%f\n",j,j*(*maxbuf),outvect[j*(*maxbuf)]);
            fclose(comm);
        }
        if (switch_first_runH || switch_first_evnH)
        {
            MPI_Datatype struct_type_event,oldtypes[BLOCK_COUNT_MESSAGE]={MPI_INT,MPI_DOUBLE};
            int blockcounts[BLOCK_COUNT_MESSAGE]={7,MAX_GROUP_SIZE*(PARTICLE_INFO_COUNT+1)};
            MPI_Aint offsets[BLOCK_COUNT_MESSAGE],extent;
            //setup description for the fields in the message structure
            int ofst=0;
            for(i=0;i<BLOCK_COUNT_MESSAGE;i++)
            {
                offsets[i]=ofst;
                MPI_Type_extent(oldtypes[i], &extent);
                ofst = ofst + blockcounts[i]*extent;
            }
            //Defining structured type and committing it.
            MPI_Type_create_struct(BLOCK_COUNT_MESSAGE, blockcounts, offsets, oldtypes, &struct_type_event);
            MPI_Type_commit(&struct_type_event);
            struct message buff;
            MPI_Status status;

            if ( 211285.1 < outvect[j*(*maxbuf)] && outvect[j*(*maxbuf)] < 211285.4 )
            {//========== RUNH subblock found =========================================
                if (dbg_infos&&(rank<LISTFILE_MAX))
                {
                    comm = fopen(statfile,"a");
                    fprintf(comm,"\n[%f]: Run Header subblock",MPI_Wtime());
                    fclose(comm);
                }
                for(i=0;i<(*maxbuf);i++)
                {
                    Run_header[i]=outvect[j*(*maxbuf)+i];
                    if (dbg_infos&&(rank<LISTFILE_MAX))
                    {
                        comm = fopen(statfile,"a");
                        fprintf(comm,"outvect[%d]=%f\t",j*(*maxbuf)+i,outvect[j*(*maxbuf)+i]);
                        fclose(comm);
                    }
                    buff.stack[i]=Run_header[i];
                }
                buff.rnnum=(*maxbuf);
                i=MPI_Send(&buff,1,struct_type_event,MASTER,STORRUNH,MPI_COMM_WORLD);
                i=MPI_Recv(&buff,1,struct_type_event,MASTER,STORRUNH,MPI_COMM_WORLD,&status);
                if(i!= MPI_SUCCESS)
                {
                    printf("FATAL ERROR: When sending Message from %d to Master with rank %d\n",rank, MASTER);
                    MPI_Abort(MPI_COMM_WORLD,i);
                }
                for(i=0;i<(*maxbuf);i++) Run_header[i]=buff.stack[i];
                switch_first_runH=0;
            }
            //========== EVTH subblock found =========================================
            else if ( 217433.0 < outvect[j*(*maxbuf)] && outvect[j*(*maxbuf)] < 217433.2 )
            {
                if (dbg_infos&&(rank<LISTFILE_MAX))
                {
                    comm = fopen(statfile,"a");
                    fprintf(comm,"\n[%f]: Event Header subblock",MPI_Wtime());
                    fclose(comm);
                }
                for(i=0;i<(*maxbuf);i++)
                {
                    Event_header[i]=outvect[j*(*maxbuf)+i];
                    if (dbg_infos&&(rank<LISTFILE_MAX))
                    {
                        comm = fopen(statfile,"a");
                        fprintf(comm,"outvect[%d]=%f\t",j*(*maxbuf)+i,outvect[j*(*maxbuf)+i]);
                        fclose(comm);
                    }
                    buff.stack[i]=Event_header[i];
                }
                buff.rnnum=(*maxbuf);
                i=MPI_Send(&buff,1,struct_type_event,MASTER,STOREVNH,MPI_COMM_WORLD);
                i=MPI_Recv(&buff,1,struct_type_event,MASTER,STOREVNH,MPI_COMM_WORLD,&status);
                if(i!= MPI_SUCCESS)
                {
                    printf("FATAL ERROR: When sending Message from %d to Master with rank %d\n",rank, MASTER);
                    MPI_Abort(MPI_COMM_WORLD,i);
                }
                for(i=0;i<(*maxbuf);i++) Event_header[i]=buff.stack[i];
                switch_first_evnH=0;
            }
            MPI_Type_free(&struct_type_event);
        }
        //========== LONG subblock found =========================================
        if ( 52815.2 < outvect[j*(*maxbuf)] && outvect[j*(*maxbuf)] < 52815.3 )
        {
            if (dbg_infos&&(rank<LISTFILE_MAX))
            {
                comm = fopen(statfile,"a");
                fprintf(comm,"\n[%f]: Long subblock outvect[%d]=%f",MPI_Wtime(),j*(*maxbuf)+i,outvect[j*(*maxbuf)+i]);
                fclose(comm);
            }
        }
        //========== particle data subblock ======================================
        else if ( ( 1000.0 < outvect[j*(*maxbuf)] && outvect[j*(*maxbuf)] < 3301.3 ) ||
                  ( 3301.4 < outvect[j*(*maxbuf)] && outvect[j*(*maxbuf)]   < 3397.3 ) ||
                  ( 3397.4 < outvect[j*(*maxbuf)] && outvect[j*(*maxbuf)]  < 52815.2 ) ||
                  ( 52815.3 < outvect[j*(*maxbuf)] && outvect[j*(*maxbuf)]  < 77000.0 ) ||
                  ( 116000.0 < outvect[j*(*maxbuf)] && outvect[j*(*maxbuf)] < 195000.0 ))
        {
            if (dbg_infos&&(rank<LISTFILE_MAX))
            {
                comm = fopen(statfile,"a");
                fprintf(comm,"\n[%f]: Particle subblock",MPI_Wtime());
                fclose(comm);
            }
            for(i=0;i<*maxbuf;i++)
            {
                Block[particle_block_counts++]=outvect[j*(*maxbuf)+i];
                if (dbg_infos&&(rank<LISTFILE_MAX))
                {
                    comm = fopen(statfile,"a");
                    fprintf(comm,"outvect[%d]=%f\t",j*(*maxbuf)+i,outvect[j*(*maxbuf)+i]);
                    fclose(comm);
                }
            }
        }
        //========== EVTE subblock found =========================================
        else if ( 3397.3 < outvect[j*(*maxbuf)] && outvect[j*(*maxbuf)] <  3397.5 )
        {
            if (dbg_infos&&(rank<LISTFILE_MAX))
            {
                comm = fopen(statfile,"a");
                fprintf(comm,"\n[%f]: Event End subblock outvect[%d]=%f",MPI_Wtime(),j*(*maxbuf)+i,outvect[j*(*maxbuf)+i]);
                fclose(comm);
            }
        }
        //========== RUNE subblock found =========================================
        else if ( 3301.2 < outvect[j*(*maxbuf)]&& outvect[j*(*maxbuf)] < 3301.5 )
        {
            if (dbg_infos&&(rank<LISTFILE_MAX))
            {
                comm = fopen(statfile,"a");
                fprintf(comm,"\n[%f]: Run End subblock outvect[%d]=%f",MPI_Wtime(),j*(*maxbuf)+i,outvect[j*(*maxbuf)+i]);
                fclose(comm);
            }
        }
        else if ( outvect[j*(*maxbuf)] == 0.000000 )
            if (dbg_infos&&(rank<LISTFILE_MAX))
            {
                comm = fopen(statfile,"a");
                fprintf(comm,"\n[%f]: Empty subblock outvect[%d]=%f",MPI_Wtime(),j*(*maxbuf)+i,outvect[j*(*maxbuf)+i]);
                fclose(comm);
            }
    }
    if( particle_block_counts>=(MAXBLOCKS-21*(*maxbuf)) ) //Write down to escape the stack overflow
    {
        write_block_fort((*maxbuf),Block);
        maxblock_switch++;
        if (dbg_infos)
        {
            strcpy(statfile,statdir);
            strcat(statfile,"write_1GB_block.txt");
            FILE* file = fopen(statfile,"a");
            fprintf(file,"[%f]: slave with rank %d has written out the block containing %d elements due to limitation of memory. maxblock_switch=%d\n",MPI_Wtime(),rank,particle_block_counts,maxblock_switch);
            fclose(file);
        }
        particle_block_counts=0;
    }
}
