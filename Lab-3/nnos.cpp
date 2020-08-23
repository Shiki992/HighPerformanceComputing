#include<iostream>
#include<omp.h>
#define N 100000000
using namespace std;

unsigned long reduction(){
    unsigned long res;
#pragma omp parallel
    {
        #pragma omp parallel for reduction(+:res)
        for (size_t i = 0; i < N; i++)
        {
            res += 1e5 + rand()%(N);
        }
        
    }
    return res;
}

unsigned long critical(){
    unsigned long res;
    #pragma omp parallel
    {
        #pragma omp critical
        for (size_t i = 0; i < N; i++)
        {
            res += 1e5 + rand()%(N);
        }
        
    }
    return res;
}

int main(){
    unsigned long res1, res2;
    double start1,end1,start2,end2;
    start1= omp_get_wtime();
    res1 = reduction();
    end1= omp_get_wtime();
    start2= omp_get_wtime();
    res2 = critical();
    end2= omp_get_wtime();
    cout<<"time taken for reduction ="<<end1-start1<<" res = "<<res1<<endl;
    cout<<"time taken for critical section ="<<end2-start2<<" res = "<<res2<<endl;
    return 0;

}