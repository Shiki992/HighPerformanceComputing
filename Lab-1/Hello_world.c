//OpenMP header
#include <omp.h>
#include<stdlib.h>
#include<stdio.h>

int main( int ac, char **av)

{

#pragma omp parallel
{
    printf("Hello World... from thread = %d\n",omp_get_thread_num());
}

return 0;

}

