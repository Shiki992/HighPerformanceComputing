//OpenMP header
#include "omp.h"
#include<iostream>
using namespace std;

// void v_add(double* x, double* y, double* z, int t) {
//   #pragma omp parallel
//   {
//     #pragma omp for
//     for(int i=0; i<t; i++)
//       z[i] = x[i] + y[i];
//   }
//   for (int i = 0; i < t; i++)
//   {
//       cout<<z[i];
//   }
  
// }

int main( int ac, char **av)
{
long double a[100000],b[100000],c[100000];
double start,end;
// int threads=omp_set_num_threads(10);
// cout<<threads;    
for (int i = 0; i < 100000; i++)
{
    a[i]=(rand()*4586.45587454666494456416162164964441616);
    cout<<"a["<<i<<"] = "<<a[i]<<"\t";
    b[i]=(rand()*4586.45587454666494456416162164964441616);
    cout<<"b["<<i<<"] = "<<b[i]<<endl;
}
cout<<"Addition of 2 vectors A and B:\n";
start= omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp for
    for(int i=0; i<100000; i++)
      {
          c[i] = a[i] * b[i];
          cout<<c[i]<<" ";
      
      }
    
  }
//     for (int i = 0; i < 10; i++)
//   {
//       cout<<c[i]<<" ";
//   }
  cout<<endl;

  end = omp_get_wtime();
  cout<<"time taken="<<end-start<<endl;


return 0;

}
