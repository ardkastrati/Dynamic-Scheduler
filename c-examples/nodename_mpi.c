/*
Using MPI Libraries in a C code
Parallel programming and graphical processors in Scientific applications: KSETA-Courses October 2013, KIT, Germany
Gevorg Poghosyan, Simulation Lab Elementary Particle and Astroparticle Physics, SCC, KIT, Germany
poghosyan@kit.edu

Exercise to demonstrates the use of MPI functions:
1) MPI_Init
2) MPI_Comm_rank
3) MPI_Comm_size
4) MPI_Finalize  
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[])
{	char *node_name;
	int mpitask_id,number_of_tasks_in_MPI_world;
// add in MPI start-up routines
// 1st: launch the MPI processes on each node
	MPI_Init(&argc,&argv);

// 2nd: request a thread id, sometimes called a "rank" from the MPI master process, which has rank or mpitask_id == 0
	MPI_Comm_rank(MPI_COMM_WORLD, &mpitask_id);

// 3rd: this is often useful, get the number of threads or processes launched by MPI, this should be Number of CPUs-1 as of numbering starts from zero
	MPI_Comm_size(MPI_COMM_WORLD, &number_of_tasks_in_MPI_world);

//	on EVERY process, allocate space for the machine name at his particular node memory
	node_name = (char *)calloc(80,sizeof(char));

//	get the machine name of this particular host - at least the first 80 characters of it
	gethostname(node_name,80);
	printf("Welcome into MPI World! This is the parallel thread with rank=%i from %i threads of the MPI_World, running on the node %s!\n",mpitask_id,number_of_tasks_in_MPI_world,node_name);
	free(node_name);
// Do not forgot to Terminate and clean up all MPI states	
	MPI_Finalize();
	return 0;
}
