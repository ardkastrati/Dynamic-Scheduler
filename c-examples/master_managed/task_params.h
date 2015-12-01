/////////////////////initializing parameters///////////////////
//the number of data type block in the MPI message
#define BLOCK_COUNT_MESSAGE 2
//rank of the master ---(DONT CHANGE IT)
#define MASTER 0

#define MXLIST 200001
#define MAX_GROUP_SIZE 201
#if __MULTITHIN__
#define PARTICLE_INFO_COUNT 47
#else
#define PARTICLE_INFO_COUNT 19
#endif
#define NSTEP_MAX 15000
#define LISTFILE_MAX 1

//1 GByte Memory of 268435456 floats occupying each 4 bytes (use 1/10);
#define MAXBLOCKS 26830440 // 4680 records * 5733 = 4095 records * 6552;

// MPI signal types used in code
#define VALN 2120
#define STRP 2121
#define VALP 2122
#define STRE 2123
#define VALE 2124
#define STOREVNH 3131
#define STORRUNH 3232


double *particle_stack_or_cut_file,*particles_from_stack;
int job_count, runnumber, join_counts=1;
int II1;			//Pointer of current particle in group
int NSTEP1=0;			//number of vertical steps for generating longfile
int dbg_infos=0;	//Debugging switch to show details about MPI communication
int lcout;          // LCOUT(BOOLEAN)- tells weather to generate CUTFILES or not (run always done in parallel).
int MAXBUFSLAVE=0;	// Current length of subblock of particles
char statdir[255];  // output directory name for bookkeeping: information about running status, finished free slaves etc.
float Block[MAXBLOCKS];
float Event_header[312], Run_header[312];
int particle_block_counts=0, maxblock_switch=0, switch_first_runH=1, switch_first_evnH=1;
char statfile[255],numstr[9];


struct message //structure of MPI message. It is at the same time our task
{
    int id1;        // I1CUTPAR (INT) : FIRST INDEX OF PARTICLE TO READ FROM CFILINP
    int id2;        // I2CUTPAR (INT) : LAST INDEX OF PARTICLE TO READ FROM CFILINP
    int lprim;      // (BOOLEAN) : TRUE(1), IF SHOWER IS PRIMARY || FALSE(0), IF SUBSHOWER IS SECONDARY
    int rnnum;      // RUN NUMBER
    int seed;       // SEED USED BY THE SUB SHOWER
    int uid;        // THE UNIQUE ID OF THE MPI JOB
    int parent_id;  // THE PARENT ID OF THE MPI JOB(USED TO RECONSTRUCT THE CUTFILE_NAME)
    double stack[MAX_GROUP_SIZE*(PARTICLE_INFO_COUNT+1)];
};

typedef struct message task_type;
typedef double result_type[2];

struct process //structure for longfile
{
    char pstr[300];//text for number of particles
    char estr[300];//text for energy of particles
    double pbuffer[NSTEP_MAX][10];//buffer for containing number of particles
    double ebuffer[NSTEP_MAX][10];//buffer for containing energy of particles
};

struct process lngfile,pro;

MPI_Datatype struct_type,oldtypes[BLOCK_COUNT_MESSAGE]={MPI_INT,MPI_DOUBLE};

double dectcut,dectmax;      //DECTCUT and DECTMAX are the energy thresholds
