# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# include "mpi.h"
void timestamp ( );
int main ( int argc, char *argv[] )
{
    int id;
    int ierr;
    int p;
    double start,end;
    ierr = MPI_Init(&argc,&argv);

    if ( ierr != 0 )
    {
        printf ( "\n" );
        printf ( "HELLO_MPI - Fatal error!\n" );
        printf ( "  MPI_Init returned nonzero IERR.\n" );
        exit ( 1 );
    }
    ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
    ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );
    start = MPI_Wtime();
    printf ( "P%d:    'Hello, world!'\n", id );
    end = MPI_Wtime();
    ierr = MPI_Finalize();
    printf("Time it takes: %f",end - start);
    return 0;
}