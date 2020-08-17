//OpenMP header
#include "omp.h"
#include<iostream>
#include<vector>
using namespace std;


int main( int ac, char **av)
{
vector<unsigned long> a[100000000],b[100000000],c[100000000];
double start,end;
// int threads=omp_set_num_threads(10);
// cout<<threads;    
for (unsigned long i = 0; i < 100000000; i++)
{
    a->push_back((rand()%10)*345600000000);
    // cout<<"a["<<i<<"] = "<<a[i]<<"\t";
    b->push_back((rand()%10)*345600000000);
    // cout<<"b["<<i<<"] = "<<b[i]<<endl;
}
// cout<<"Addition of 2 vectors A and B:\n";
start= omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp for
    for(unsigned long i=0; i<100000000; i++)
    { c->push_back(a[i]+b[i]);
      // cout<<c[i]<<" ";
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
