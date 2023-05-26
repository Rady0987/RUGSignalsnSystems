/* file: linFilter.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 11 Dec 2020 */
/* version: 1.0 */
/* Description: This program outputs the signal y[] that is 
obtained by applying the filters with kernels h1[] and h2[]. */


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

void *safeCalloc(int sz) {
   void *p = calloc(sz, sizeof(int));
   if (p == NULL) {
      fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", sz);
      exit(EXIT_FAILURE);
   }
   return p;
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

void convolution(int *A, int lenA, int *B, int lenB, int *C) {
   int lenC = lenA + lenB - 1;
   for(int i = 0; i < lenC; i++) {
      for(int j = 0; j < lenA; j++) {
        C[i] += A[j] * checkIndex(B, lenB, i - j);
      }
   }  
}

int main(int argc, char *argv[]) {
   int lenA, *A, *A1, lenA1, *B, lenB, *C, lenC, *C1, lenC1;
   A = readSignal(&lenA);
   A1 = readSignal(&lenA1);
   B = readSignal(&lenB);
   lenC = lenA + lenB - 1;
   C = safeCalloc(lenC);
   convolution(A, lenA, B, lenB, C);
   lenC1 = lenC + lenA1 - 1;
   C1 = safeCalloc(lenC1);
   convolution(A1, lenA1, C, lenC, C1);
   printSignal(lenC1, C1);
   free(A);
   free(B);
   free(C);
   free(C1);
   return 0;
}