#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "mpi.h"
int main ( int argc, char *argv[] )
{
	int id;
	int ierr;
	int p,len;
	char name[MPI_MAX_PROCESSOR_NAME];
	double start,end;
	ierr = MPI_Init(&argc,&argv);
	start = MPI_Wtime();
	   
	ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
	ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );
	MPI_Get_processor_name(name,&len);
	printf ( "Hello, world! from processor %s, rank(id) %d out of %d processors\n", name, id, p );
	end = MPI_Wtime();
	ierr = MPI_Finalize();
	printf("Time it takes: %f \n",end - start);
	return 0;
}
