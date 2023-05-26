/* file: inverseFIR.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 11 Dec 2020 */
/* version: 1.0 */
/* Description: This program outputs the impulse reponse of the 
system if it might be a FIR system from the input signal X[] and output Y[] or 
"NO FIR" if it is not.*/


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

int sum(int *H, int lenH, int *X, int lenX, int index) {
   int rez = 0, j = index - 1;
   for(int i = 1; i <= index; i++) {
      rez += checkIndex(X, lenX, i) *  checkIndex(H, lenH, j);
      j--;
   }
   return rez;
}

int checkFIR(int *X, int lenX, int *H, int lenH, int *Y, int lenY) {
   int *arr, lenght;
   lenght = lenX + lenH - 1;
   arr = safeCalloc(lenght);
   convolution(X, lenX, H, lenH, arr);
   for(int i = 0; i < lenght; i++) {
      if(arr[i] != Y[i])
         return 1;
   }
   return 0;
}

int main(int argc, char *argv[]) {
   int lenX, *X, *H, lenH, *Y, lenY;
   X = readSignal(&lenX);
   Y = readSignal(&lenY);
   lenH = lenY + 1 - lenX;
   H = safeCalloc(lenH);
   for(int i = 0; i < lenH; i++) {
      H[i] = (Y[i] - sum(H, lenH, X, lenX, i)) / X[0];
   }
   if(checkFIR(X, lenX, H, lenH, Y, lenY)){
      printf("NO FIR\n");
   } else {
      printSignal(lenH, H);
   }
   free(X);
   free(Y);
   free(H);
   return 0;
}