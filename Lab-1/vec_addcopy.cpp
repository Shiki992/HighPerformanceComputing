#include<bits/stdc++.h>
using namespace std;
#include <omp.h>
int main()
// n is the array size
{       const int n = 2.16*1e8;
        const int num_of_threads = 32;
        double start,end;
        vector<unsigned long> temp(n);
        for (unsigned long i = 0; i < n; i++) {
                unsigned long x=1e5;
                temp[i] = 1e5 + rand()%x;
        }
        vector<unsigned long> a, b, c;
        a = temp;
        b = temp;
        c = temp;
        printf("\nThe size of temp, a ,b, c : %lu, %lu, %lu", a.size(), b.size(), c.size());
    start= omp_get_wtime();
    #pragma omp parallel 
    {   unsigned long thread_num = omp_get_thread_num();
        for (unsigned long i=thread_num * (n/num_of_threads); i <= thread_num * (n/num_of_threads) + n/num_of_threads; i++) {
                c[i] = a[i] + b[i];
        }

    }
    end= omp_get_wtime();
    printf("Time taken : %f",end-start);

 //    cout << endl;
 //    cout << "\n Vector1 :";    
 //  for (int i = 0; i < n; i++) {
 //    cout << a[i] << " ";
 //  }
 //  cout << endl;
 //  cout << "\n Vector2 :";    
 //  for (int i = 0; i < n; i++) {
 //    cout << b[i] << " ";
 //  }
 //  cout << endl;
 //    cout << "\n Ans :";    
        // for (int i = 0; i < n; i++) {
        //      cout << c[i] << " ";
        // }

    cout << "\n";

}
