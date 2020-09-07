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
  double wtime;

  ierr = MPI_Init ( &argc, &argv );

  if ( ierr != 0 )
  {
    printf ( "\n" );
    printf ( "HELLO_MPI - Fatal error!\n" );
    printf ( "  MPI_Init returned nonzero IERR.\n" );
    exit ( 1 );
  }
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );
  if ( id == 0 ) 
  {
    wtime = MPI_Wtime ( );

    printf ( "\n" );
    printf ( "P%d:  HELLO_MPI - Master process:\n", id );
    printf ( "P%d:    C/MPI version\n", id );
    printf ( "P%d:    An MPI example program.\n", id );
    printf ( "P%d:    The number of processes is %d.\n", id, p );
    printf ( "\n" );
  }
  printf ( "P%d:    'Hello, world!'\n", id );

  if ( id == 0 )
  {
    wtime = MPI_Wtime ( ) - wtime;
    printf ( "P%d:    Elapsed wall clock time = %f seconds.\n", id, wtime );
  }
  ierr = MPI_Finalize ( );
  return 0;
}