/* file: inplaceFFTFFT.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 20 Jan 2021 */
/* version: 2.0 */
/* Description: This program outputs the steady state of the 
signal y[] that is obtained by using inplaceFFT theorem and 
the recursive FFT algorithm on the signal x[] and the kernel h[].*/

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;

int *readSignal(int *len) {
   int *x;
   char c;
   scanf("%d:", len);
   x = calloc(*len, sizeof(int));
   do c = getchar(); while (c != '[');
   if (*len > 0) {
	   scanf("%d", &x[0]);
	   for (int i=1; i < *len; i++) scanf(",%d", &x[i]);
   }
   do c = getchar(); while (c != ']');
   return x;
}

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
  return safeMalloc(n * sizeof(int));
}

double *makeDoubleArray(int n) {
  /* allocates dynamic double array of size/length n */
  return safeMalloc(n * sizeof(double));
}

void printSignal(int len, int *x) {
   printf("%d: [", len);
   if (len > 0) {
	  printf("%d", x[0]);
	  for (int i=1; i < len; i++) printf(",%d", x[i]);
   }
   printf("]\n");
}

void FFT(double complex *array, int length, double complex w, double complex *recArr) {
   double complex wPow = 1, *evenCoef, *oddCoef;
   if(length < 2)
      return;
   length /= 2;
   evenCoef = recArr;
   oddCoef = recArr + length;

   for(int i = 0; i < length; i++) {
      evenCoef[i] = array[2 * i];
      oddCoef[i] = array[2 * i + 1];
   }

   FFT(oddCoef, length, w * w, array);
   FFT(evenCoef, length, w * w, array);
  
   for(int i = 0; i < length; i++) {
      array[i] = evenCoef[i] + wPow * oddCoef[i];
      array[length + i] = evenCoef[i] - wPow * oddCoef[i];
      wPow *= w;
   }
}

int power2Size(int size) {
   int p = 1;
   while(p < size) {
      p *= 2;
   }
   return p;
}

void copyArray(int *array, int length, double complex *cArray) {
   for (int i = 0; i < length; i++) {
      cArray[i] = array[i];
   }
}

void inplaceFFT(double complex *arr, int length) {
   double complex w, *recArr;
   w = cexp(I * -2.0 * pi / length);
   /* recArr is passed to the FFT function to skip memory alloc at each recursive level */
   recArr = malloc(length * sizeof(double complex));
   FFT(arr, length, w, recArr);
   free(recArr);
}

void inplaceInverseFFT(double complex *arr, int length) {
   double complex w, *recArr;
   w = cexp(I * 2.0 * pi / length);
   /* recArr is passed to the FFT function to skip memory alloc at each recursive level */
   recArr = malloc(length * sizeof(double complex));
   FFT(arr, length, w, recArr);
   free(recArr);
   for(int i = 0; i < length; i++) {
      arr[i] /= length;
   }
}

int main(int argc, char* argv[]) {
   int *h, lenH, *x, lenX, *y, lenY, pow2Len;
   double complex *complexH, *complexX;
   h = readSignal(&lenH);
   x = readSignal(&lenX);
   lenY = lenX + lenH - 1;
   pow2Len = power2Size(lenY);
   y = makeIntArray(lenY);

   complexH = safeMalloc(pow2Len * sizeof(double complex));
   complexX = safeMalloc(pow2Len * sizeof(double complex));

   copyArray(h, lenH, complexH);
   copyArray(x, lenX, complexX);

   inplaceFFT(complexH, pow2Len);
   inplaceFFT(complexX, pow2Len);

   /* Actual convolution stored in complex X array */
   for(int i = 0; i < pow2Len; i++) {
      complexX[i] *= complexH[i];
   }

   inplaceInverseFFT(complexX, pow2Len);
   for (int i = 0; i < lenY; i++) {
      y[i] = (int) round(creal(complexX[i]));
   }
   
   printSignal(lenY, y);
   free(complexH);
   free(complexX);
   free(h);
   free(x);
   free(y);
   return 0;
}