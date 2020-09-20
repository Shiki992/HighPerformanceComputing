#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "omp.h"
#define PI 3.14159265
#define n 100
 
int main(int argc, char **argv) {
    unsigned long realOut[n][n];
    unsigned long imagOut[n][n];
    unsigned long amplitudeOut[n][n];
 
    int height = n;
    int width = n;
    int yWave;
    int xWave;
    int ySpace;
    int xSpace;
    int i, j;
    double start,end;
    unsigned long inputData[n][n];
    for (unsigned long i = 0; i < n; i++) 
        {
            for (unsigned long j = 0; j < n; j++)
            {
                unsigned long x=1e5;
                inputData[i][j] = 1e5 + rand()%x;
            }
        }
            start= omp_get_wtime();
    
 
    #pragma omp parallel

    // Two outer loops iterate on output data.
{
    #pragma omp parallel for
        for (yWave = 0; yWave < height; yWave++) {
        #pragma omp parallel for
        for (xWave = 0; xWave < width; xWave++) {
            // Two inner loops iterate on input data.
            #pragma omp parallel for
            for (ySpace = 0; ySpace < height; ySpace++) {
                #pragma omp parallel for
                for (xSpace = 0; xSpace < width; xSpace++) {
                    // Compute real, imag, and ampltude.
                    #pragma omp critical
                    realOut[yWave][xWave] += (inputData[ySpace][xSpace] * cos(
                            2 * PI * ((1.0 * xWave * xSpace / width) + (1.0
                                    * yWave * ySpace / height)))) / sqrt(
                            width * height);
                    #pragma omp critical        
                    imagOut[yWave][xWave] -= (inputData[ySpace][xSpace] * sin(
                            2 * PI * ((1.0 * xWave * xSpace / width) + (1.0
                                    * yWave * ySpace / height)))) / sqrt(
                            width * height);
                    amplitudeOut[yWave][xWave] = sqrt(
                            realOut[yWave][xWave] * realOut[yWave][xWave]
                                    + imagOut[yWave][xWave]
                                            * imagOut[yWave][xWave]);
                }
//                printf(" %e + %e i (%e)\n", realOut[yWave][xWave],
//                        imagOut[yWave][xWave], amplitudeOut[yWave][xWave]);
            }
        }
    }}
    end= omp_get_wtime();
    printf(" time taken :: %f \n",end-start);
    return 0;
}
