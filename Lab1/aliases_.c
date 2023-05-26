/* file: aliases?.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 25 Nov 2020 */
/* version: 1.0 */
/* Description: This program outputs YES if uniform sampling 
of the two sinusoids using the given sampling rate yields the 
same discrete output. Otherwise, it should output NO. */

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

int *makeIntArray(int n) {
  /* allocates dynamic int array of size/length n */
  return safeMalloc(n*sizeof(int));
}

void printDoubleArray(int length, double *arr) {
  printf("[");
  if (length > 0) {
    printf("%.2lf", arr[0]);
    for (int i=1; i<length; i++) {
      printf(",%.2lf", arr[i]);
    }
  }
  printf("]\n");
}

void checkAliases(double *sample1, double *sample2) {
   for(int i = 0; i < 100; i++) {
      if((int)sample1[i] != (int)sample2[i]) {
         printf("NO\n");
         return;
      }
   }
   printf("YES\n");
}

int main(int argc, char* argv[]) {
   int samplRate;
   double A1, f1, phase1, A, f, phase, wHat, *sampleOne, *sampleTwo;
   scanf("%d", &samplRate);
   scanf("%lf %lf %lf", &A, &f, &phase);
   scanf("%lf %lf %lf", &A1, &f1, &phase1);
   sampleOne = safeMalloc(100 * sizeof(double));
   sampleTwo = safeMalloc(100 * sizeof(double));
   for(int i = 0; i < 100; i++) {
      wHat = (2 * pi * f) / samplRate;
      sampleOne[i] = A * cos(wHat * i + phase);
      wHat = (2 * pi * f1) / samplRate;
      sampleTwo[i] = A1 * cos(wHat * i + phase1);
   }
   checkAliases(sampleTwo, sampleOne);
   free(sampleOne);
   free(sampleTwo);
   return 0;
}