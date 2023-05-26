/* file: 1DpearsonCorr.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 11 Dec 2020 */
/* version: 1.0 */
/* Description: This program outputs the steady state of 
the signal y[] that is obtained by correlating the signal 
x[] with the template h[] using Pearson correlation coefficient.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int checkIndex(int *arr, int length, int index) {
   if(index >= 0 && index < length)
      return arr[index];
   return 0;
}

void correlation(int *x, int lenX, int *h, int lenH, int *y, int lenY) {
   for(int d = 0; d < lenY; d++) {
      for(int i = 0; i < lenH; i++) {
        y[d] += checkIndex(x, lenX, i + d) * checkIndex(h, lenH, i);
      }
   }  
}

double calcMeanX(int *x, int from, int to, int size) {
   double rez = 0.0;
   for(int i = from; i < to; i++) {
      rez += x[i];
   }
   rez /= size;
   return rez;
}

double calcMeanH(int *h, int lenH) {
   double meanH = 0;
   for(int i = 0; i < lenH; i++) {
      meanH += h[i];
   }
   return meanH /= lenH;
}

void pearsonCorrelation(int *x, int lenX, int *h, int lenH, int *y, int lenY, double *Y1) {
   double meanH, meanX;
   meanH = calcMeanH(h, lenH);
   for (int d = 0; d < lenY; d++) {
      double sqrt1 = 0.0;
      double sqrt2 = 0.0;
      meanX = calcMeanX(x, d, d + lenH, lenH);
      for (int i = 0; i < lenH; i++) {
         sqrt1 += (h[i] - meanH) * (h[i] - meanH);
         sqrt2 += (x[i + d] - meanX) * (x[i + d] - meanX);
      }
      Y1[d] = (y[d] - (lenH * meanX * meanH)) /
      ((lenH - 1) * (sqrt(sqrt2 / (lenH - 1))) * (sqrt(sqrt1 / (lenH - 1))));
   }
}

int main(int argc, char* argv[]) {
   int *h, lenH, *x, lenX, *y, lenY;
   double *Y1;
   h = readSignal(&lenH);
   x = readSignal(&lenX);
   lenY = lenX - lenH + 1;
   y = makeIntArray(lenY);
   Y1 = makeDoubleArray(lenY);
   correlation(x, lenX, h, lenH, y, lenY);
   pearsonCorrelation(x, lenX, h, lenH, y, lenY, Y1);
   printSignal(lenY, Y1);
   free(h);
   free(x);
   free(y);
   free(Y1);
   return 0;
}