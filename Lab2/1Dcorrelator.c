/* file: 1Dcorrelator.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 11 Dec 2020 */
/* version: 1.0 */
/* Description: This program outputs the steady state of the 
signal y[] that is obtained by correlating the signal x[] with 
the template h[].*/

#include <stdio.h>
#include <stdlib.h>

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

int checkIndex(int *arr, int length, int index) {
   if(index >= 0 && index < length)
      return arr[index];
   return 0;
}

void correlation(int *X, int lenX, int *H, int lenH, int *Y, int lenY) {
   for(int d = 0; d < lenY; d++) {
      for(int i = 0; i < lenH; i++) {
        Y[d] += checkIndex(X, lenX,i + d) * checkIndex(H, lenH, i);
      }
   }  
}

int main(int argc, char* argv[]) {
   int *H, lenH, *X, lenX, *Y, lenY;
   H = readSignal(&lenH);
   X = readSignal(&lenX);
   lenY = lenX - lenH + 1;
   Y = makeIntArray(lenY);
   correlation(X, lenX, H, lenH, Y, lenY);
   printSignal(lenY, Y);
   free(H);
   free(X);
   free(Y);
   return 0;
}