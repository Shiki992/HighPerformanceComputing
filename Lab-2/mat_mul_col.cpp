
#include<bits/stdc++.h>
// #include<vector>
#include<iostream>
using namespace std;
#include <omp.h>
int main()
// n is the array size
{       const long int n = 999;
        // const int num_of_threads = 1;
        double start,end;
        // vector<vector<unsigned long>> temp,a,b,c;
        unsigned long temp[999][999],a[999][999],b[999][999],c[999][999];
        for (unsigned long i = 0; i < n; i++) {
            for (unsigned long j = 0; j < n; j++)
            {
                unsigned long x=1e5;
                // temp[i][j] = 1e5 + rand()%x;
                a[i][j] = 1e5 + rand()%x;
                b[i][j] = 1e5 + rand()%x;
            }
        }
        // c = temp;
        // printf("\nThe size of temp, a ,b, c : %lu, %lu, %lu", a.size(), b.size(), c.size());
        start = omp_get_wtime(); 
    #pragma omp parallel 
    {   unsigned long thread_num = omp_get_thread_num();
        #pragma omp for
        for (unsigned long j = 0; j < n; j++){ 
            #pragma omp for
            for (unsigned long i = 0; i < n; i++) {
                c[i][j] = c[i][j] + (a[i][j] * b[i][j]); 
            }
        }
    }
    end = omp_get_wtime();

    cout << "Time taken="<<end - start<<endl;

}
