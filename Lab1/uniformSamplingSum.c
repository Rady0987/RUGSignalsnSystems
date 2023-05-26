/* file: uniformSamplingSum.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 25 Nov 2020 */
/* version: 1.0 */
/* Description: This program outputs n samples of the 
discrete time signal that is obtained after uniform 
sampling the sum of the m sinusoids. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;

void *safeMalloc(int sz) {
  void *p = calloc(sz, 1);
  if (p == NULL) {
    fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", sz);
    exit(EXIT_FAILURE);
  }
  return p;
}

double *makeDoubleArray(int n) {
  /* allocates dynamic double array of size/length n */
  return safeMalloc(n*sizeof(double));
}

void printIntArray(int length, double *arr) {
  printf("[");
  if (length > 0) {
    printf("%d", (int)arr[0]);
    for (int i = 1; i < length; i++) {
      printf(",%d", (int)arr[i]);
    }
  }
  printf("]\n");
}

int main(int argc, char* argv[]) {
   int samplRate, n, m;
   double A, f, phase, wHat, *samples;
   scanf("%d %d", &samplRate, &n);
   samples = makeDoubleArray(n);
   scanf("%d", &m);
   for(int i = 0; i < m; i++) {
      scanf("%lf %lf %lf", &A, &f, &phase);
      for(int j = 0; j < n; j++) {
         wHat = (2 * pi * f) / samplRate;
         samples[j] += A * cos(wHat * j + phase);
      }
   }
   printIntArray(n, samples);
   free(samples);
   return 0; 
}