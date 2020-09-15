#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>
#include<math.h>
int main(int argc, char **argv)
{
  /* double a[1000],b[1000];
   for(int i=0;i<100000;i++)
        {       a[i]= pow(2,15)+rand()+0.13246549884;//rand();
                b[i]= pow(2,16)+rand()+0.75245496088;//rand();
                //printf("%f   %f\n",a[i],b[i]);
        }
   */
        int node;
        int world_size,cnt=0;
        double start, end,tsum = 0;
        srand(time(NULL));
        MPI_Init(&argc,&argv);
        start = MPI_Wtime();
        MPI_Comm_rank(MPI_COMM_WORLD, &node);
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        if(node == 0)
        {
                double a[100000],b[100000],c[100000];
                 for(int i=0;i<100000;i++)
                {
                        a[i]= pow(2,15)+rand()+0.13246549884;
                        b[i]= pow(2,16)+rand()+0.75245496088;

                }
                int load_per_proc;

                if(world_size!=1)
                        load_per_proc=100000/(world_size-1);
                else
                        load_per_proc=100000;

                double c1[load_per_proc];
                MPI_Status status;

                if(world_size>1)
                {
                        for(int i=1;i<world_size;i++)
                        {       MPI_Send(&load_per_proc,1,MPI_INT,i,1,MPI_COMM_WORLD);  

                                MPI_Send(&a,100000,MPI_DOUBLE,i,0,MPI_COMM_WORLD);

                                MPI_Send(&b,100000,MPI_DOUBLE,i,0,MPI_COMM_WORLD); 
                        }
                        int n1,remi,j;
                        for(int i1=1;i1<world_size;i1++)
                        {
                                 MPI_Recv(&n1,1,MPI_INT,MPI_ANY_SOURCE,2,MPI_COMM_WORLD,&status);
                                MPI_Recv(&c1,load_per_proc,MPI_DOUBLE,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
                                for(int i=(n1-1)*load_per_proc,j=0;i<(n1)*load_per_proc;i++,j++)
                                        c[i]=c1[j];
                        }
                        int rem = (world_size-1)*load_per_proc;
                        for(int ii= rem;ii<100000;ii++)
                        {
                              c[ii]=a[ii]*b[ii];
                        }

                }
                else
                {
                        for(int i=0;i<100000;i++)
                                c[i]=a[i]*b[i];

                }

        }
        else           
        {
                double a[100000],b[100000];
                MPI_Status status;
                int load_per_proc;
                MPI_Recv(&load_per_proc,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);          

                MPI_Recv(&a,100000,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&status);                
                MPI_Recv(&b,100000,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&status);                 
                double c[load_per_proc];
                int j,rem;
                 MPI_Send(&node,1,MPI_INT,0,2,MPI_COMM_WORLD);



                for(int i=(node-1)*load_per_proc,j=0;i<node*load_per_proc;i++,j++)
                        c[j]=a[i]*b[i];

                 MPI_Send(&c,load_per_proc,MPI_DOUBLE,0,0,MPI_COMM_WORLD);

        }
         end = MPI_Wtime();
        if(node == 0)
            {printf(" time taken :: %f \n",end-start);
            tsum+=end-start;
            cnt++;}


        MPI_Finalize();
        double avg = tsum/cnt;
        printf("avg = %f \n",avg);

return 0;
}
