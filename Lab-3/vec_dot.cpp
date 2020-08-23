#include<omp.h>
#include<iostream>
#define ARRAY_SIZE 340000
using namespace std;
int main(){

     const long int n = ARRAY_SIZE;
        // const int num_of_threads = 1;
        double start,end;
        // vector<vector<unsigned long>> temp,a,b,c;
        unsigned long temp[ARRAY_SIZE],a[ARRAY_SIZE],b[ARRAY_SIZE],c[ARRAY_SIZE];
        for (unsigned long i = 0; i < n; i++) {
                unsigned long x=1e5;
                temp[i] = 1e5 + rand()%x;
                a[i] = 1e5 + rand()%x;
                b[i] = 1e5 + rand()%x;  
        }

    unsigned long global_sum = 0.0;
    start= omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp for
    for(int i=0; i<ARRAY_SIZE; i++)
      #pragma omp critical
        global_sum += a[i] * b[i];
  }
  end= omp_get_wtime();
  cout << "Time taken="<<end - start<<endl;
}