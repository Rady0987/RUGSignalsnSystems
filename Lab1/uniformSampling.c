/* file: uniformSampling.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 25 Nov 2020 */
/* version: 1.0 */
/* Description: This program outputs n samples of the discrete 
time signal that is obtained after uniform sampling of 
x(t) = Acos(2πft + ϕ) using the sampling rate fs. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;

void printIntArray(int length, int *arr) {
  printf("[");
  if (length > 0) {
    printf("%d", arr[0]);
    for (int i=1; i<length; i++) {
      printf(",%d", arr[i]);
    }
  }
  printf("]\n");
}

int main(int argc, char* argv[]) {
   int samplRate, n;
   double A, f, phase, wHat;
   scanf("%d %d %lf %lf %lf", &samplRate, &n, &A, &f, &phase);
   int samples[n];
   for(int i = 0; i < n; i++) {
      wHat = (2 * pi * f) / samplRate;
      samples[i] = A * cos(wHat * i + phase);
   }
   printIntArray(n, samples);
   return 0;
}