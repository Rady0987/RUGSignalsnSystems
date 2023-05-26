/* file: 1DpearsonCorrelatorFFT.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 20 Jan 2022 */
/* version: 1.0 */
/* Description: This program outputs the steady state of 
the signal y[] that is obtained by correlating the signal 
x[] with the template h[] using Pearson correlation coefficient.*/

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

void printSignal(int len, double *x) {
   printf("%d: [", len);
   if (len > 0) {
	  printf("%.5lf", x[0]);
	  for (int i=1; i < len; i++) printf(",%.5lf", x[i]);
   }
   printf("]\n");
}

void copyArray(int *array, int length, double complex *cArray) {
   for (int i = 0; i < length; i++) {
      cArray[i] = array[i];
   }
}

int power2Size(int size) {
   int p = 1;
   while(p < size) {
      p *= 2;
   }
   return p;
}

void FFT(double complex *array, int length, double complex w, double complex *recArr) {
   double complex wPow = 1, *evenCoef, *oddCoef;
   if(length == 1)
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

void convolutionFFT(double complex *complexX, double complex *complexH, int length) {
   double complex w, *recArr;
   /* recArr is passed to the FFT function to skip memory alloc at each recursive level */
   recArr = malloc(length * sizeof(double complex));

   /* Fast Fourier Transform for h[] and x[]*/
   w = cexp(I * -2.0 * pi / length);
   FFT(complexX, length, w, recArr);
   FFT(complexH, length, w, recArr);

   /* Actual convolutionFFT stored in complex X array */
   for(int i = 0; i < length; i++) {
      complexX[i] *= complexH[i];
   }

   /* Inverse Fast Fourier Transform for the result from convolutionFFT*/
   w = cexp(I * 2.0 * pi / length);
   FFT(complexX, length, w, recArr);

   for(int i = 0; i < length; i++) {
      complexX[i] /= length;
   }
   free(recArr);
}

void pearsonCorrelation(int *x, int lenX, int *h, int lenH, int *y, int lenY, double *resultPearson) {
   int sumH = 0;
   int sumX = 0;
   int sumHpow2 = 0;
   int sumXpow2 = 0;

   for(int i = 0; i < lenH; i++) {
      sumH += h[i];
      sumX += x[i];
      sumHpow2 += h[i] * h[i];
      sumXpow2 += x[i] * x[i];
   }

   for(int i = 0; i < lenY; i++) {
      resultPearson[i] = (y[i] * lenH - (sumX * sumH)) / 
      (sqrt(lenH * sumHpow2 - sumH * sumH) * sqrt(lenH * sumXpow2 - sumX * sumX));

      sumX = sumX - x[i] + x[lenH + i]; 
      sumXpow2 = sumXpow2 - x[i] * x[i] + x[lenH + i] * x[lenH + i];
   }
}

int main(int argc, char* argv[]) {
   int *h, lenH, *x, lenX, *y, lenY, pow2Len;
   double complex *complexH, *complexX;
   double *pearsonResult;
   h = readSignal(&lenH);
   x = readSignal(&lenX);
   lenY = lenX - lenH + 1;
   pow2Len = power2Size(lenX + lenH - 1);
   y = makeIntArray(lenY + lenH - 1);
   pearsonResult = makeDoubleArray(lenY);

   complexH = safeMalloc(pow2Len * sizeof(double complex));
   complexX = safeMalloc(pow2Len * sizeof(double complex));

   copyArray(h, lenH, complexH);
   copyArray(x, lenX, complexX);

   convolutionFFT(complexX, complexH, pow2Len);

   for (int i = 0; i < lenY; i++) {
      y[i] = (int) round(creal(complexX[i]));
   }

   pearsonCorrelation(x, lenX, h, lenH, y, lenY, pearsonResult);
   printSignal(lenY, pearsonResult);

   free(complexH);
   free(complexX);
   free(h);
   free(x);
   free(y);
   free(pearsonResult);
   return 0;
}