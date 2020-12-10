#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <ctime>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cufft.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
typedef float2 Complex;





__global__ void ComplexMUL(Complex *a, Complex *b)
{
    int i = threadIdx.x;
    a[i].x = a[i].x * b[i].x - a[i].y*b[i].y;
    a[i].y = a[i].x * b[i].y + a[i].y*b[i].x;
}


int main()
{


    int N = 8192;
    int SIZE = N*N;

    cout<<"Initalizing values for Matrix 1...\n";
    Complex *fg = new Complex[SIZE];
    for (int i = 0; i < SIZE; i++){
        fg[i].x = pow(2,15)+rand()+0.13246549884; 
        fg[i].y = pow(2,15)+rand()+0.13246549884;
    }
    cout<<"Initalizing values for Matrix 2...\n";
    Complex *fig = new Complex[SIZE];
    for (int i = 0; i < SIZE; i++){
        fig[i].x = pow(2,15)+rand()+0.13246549884; // 
        fig[i].y = pow(2,15)+rand()+0.13246549884;
    }
    cout<<"Initalized values...\nDONE!\n";
    
    // for (int i = 0; i < 24; i=i+5)
    // {
    //     cout << fg[i].x << " " << fg[i + 1].x << " " << fg[i + 2].x << " " << fg[i + 3].x << " " << fg[i + 4].x << endl;
    // }
    // cout << "----------------" << endl;
    // for (int i = 0; i < 24; i = i + 5)
    // {
    //     cout << fig[i].x << " " << fig[i + 1].x << " " << fig[i + 2].x << " " << fig[i + 3].x << " " << fig[i + 4].x << endl;
    // }
    cout << "----------------" << endl;

    int mem_size = sizeof(Complex)* SIZE;


    clock_t start, end;

    
    cufftComplex *d_signal;
    cudaMalloc((void **) &d_signal, mem_size); 
    cudaMemcpy(d_signal, fg, mem_size, cudaMemcpyHostToDevice);

    
    cufftComplex *d_filter_kernel;
    cudaMalloc((void **)&d_filter_kernel, mem_size);
    cudaMemcpy(d_filter_kernel, fig, mem_size, cudaMemcpyHostToDevice);
    
  cufftHandle plan;
    cufftPlan2d(&plan, N, N, CUFFT_C2C);
     
    start=clock();
    // Transform signal and filter
    printf("Transforming signal cufftExecR2C\n");
    cufftExecC2C(plan, (cufftComplex *)d_signal, (cufftComplex *)d_signal, CUFFT_FORWARD);
    cufftExecC2C(plan, (cufftComplex *)d_filter_kernel, (cufftComplex *)d_filter_kernel, CUFFT_FORWARD);

    printf("Launching Complex multiplication<<< >>>\n");
    ComplexMUL <<< 512, 512 >> >(d_signal, d_filter_kernel);

    // Transform signal back
    printf("Transforming signal back cufftExecC2C\n");
    cufftExecC2C(plan, (cufftComplex *)d_signal, (cufftComplex *)d_signal, CUFFT_INVERSE);

    Complex *result = new Complex[SIZE];
    cudaMemcpy(result, d_signal, sizeof(Complex)*SIZE, cudaMemcpyDeviceToHost);
    end=clock(); 
  
    double time = double(end - start)/(CLOCKS_PER_SEC/double(1000.0)); 

    

    // for (int i = 0; i < SIZE; i=i+5)
    // {
    //     cout << result[i].x << " " << result[i + 1].x << " " << result[i + 2].x << " " << result[i + 3].x << " " << result[i + 4].x << endl;
    // }
    cout<<"Time Taken: "<<fixed<<time<<setprecision(5)<<" ms"<<endl;

    delete result, fg, fig;
    cufftDestroy(plan);
    //cufftDestroy(plan2);
    cudaFree(d_signal);
    cudaFree(d_filter_kernel);

}
