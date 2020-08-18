#include<bits/stdc++.h>
// #include<vector>
#include<iostream>
using namespace std;
#include <omp.h>
int main()
// n is the array size
{       const long int n = 100;
        // const int num_of_threads = 1;
        double start,end;
        // vector<vector<unsigned long>> temp,a,b,c;
        unsigned long temp[100][100],a[100][100],b[100][100],c[100][100];
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
    {
        #pragma omp for
        for(unsigned long jj=0;jj<n;jj+= 10){
            #pragma omp for
            for(unsigned long kk=0;kk<n;kk+= 10){
                    #pragma omp for
                    for(unsigned long i=0;i<n;i++){
                            #pragma omp for
                            for(unsigned long j = jj; j<((jj+10)>n?n:(jj+10)); j++){
                                    unsigned long temp = 0;
                                    #pragma omp for
                                    for(unsigned long k = kk; k<((kk+10)>n?n:(kk+10)); k++){
                                            temp += a[i][k]*b[k][j];
                                    }
                                    c[i][j] += temp;
                            }
                    }
            }
        }
    }
    end = omp_get_wtime();

    cout << "Time taken="<<end - start<<endl;

}
