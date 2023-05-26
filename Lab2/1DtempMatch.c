/* file: 1DtempMatch.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 11 Dec 2020 */
/* version: 1.0 */
/* Description: This program outputs a list of index locations 
where the Pearson Correlation is greater or equal to T, and the 
correlation value itself.*/

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

int checkIndex(int *arr, int length, int index) {
   if(index >= 0 && index < length)
      return arr[index];
   return 0;
}

void correlation(int *X, int lenX, int *H, int lenH, int *Y, int lenY) {
   for(int d = 0; d < lenY; d++) {
      for(int i = 0; i < lenH; i++) {
        Y[d] += checkIndex(X, lenX, i + d) * checkIndex(H, lenH, i);
      }
   }  
}

double calcMeanX(int *X, int from, int to, int size) {
   double rez = 0.0;
   for(int i = from; i < to; i++) {
      rez += X[i];
   }
   rez /= size;
   return rez;
}

double calcMeanH(int *H, int lenH) {
   double meanH = 0;
   for(int i = 0; i < lenH; i++) {
      meanH += H[i];
   }
   return meanH /= lenH;
}

void pearsonCorrelation(int *X, int lenX, int *H, int lenH, int *Y, int lenY, double *Y1) {
   double meanH, meanX;
   meanH = calcMeanH(H, lenH);
   for(int d = 0; d < lenY; d++) {
      double sqrt1 = 0.0;
      double sqrt2 = 0.0;
      meanX = calcMeanX(X, d, d + lenH, lenH);
      for(int i = 0; i < lenH; i++) {
         sqrt1 += (H[i] - meanH) * (H[i] - meanH);
         sqrt2 += (X[i + d] - meanX) * (X[i + d] - meanX);
      }
      Y1[d] = (Y[d] - (lenH * meanX * meanH)) /
      ((lenH - 1) * (sqrt(sqrt2 / (lenH - 1))) * (sqrt(sqrt1 / (lenH - 1))));
   }
}

int main(int argc, char* argv[]) {
   int *H, lenH, *X, lenX, *Y, lenY;
   double *Y1, T, eps = 0.0000001;
   scanf("%lf", &T);
   H = readSignal(&lenH);
   X = readSignal(&lenX);
   lenY = lenX - lenH + 1;
   Y = makeIntArray(lenY);
   Y1 = makeDoubleArray(lenY);
   correlation(X, lenX, H, lenH, Y, lenY);
   pearsonCorrelation(X, lenX, H, lenH, Y, lenY, Y1);
   for(int i = 0; i < lenY; i++) {
      if(Y1[i] > T || fabs(Y1[i] - T) < eps) {
         printf("%d %.5lf\n", i, Y1[i]);
      }
   }
   free(H);
   free(X);
   free(Y);
   free(Y1);
   return 0;
}