/* file: forwardNumTheoreticTrans.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 20 Jan 2021 */
/* version: 1.0 */
/* Description: This program outputs the steady state of the 
signal y[] that is obtained by using inplaceFFT theorem and 
the recursive FFT algorithm on the signal x[] and the kernel h[].*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned int uint;
const double pi = 3.141592653589793238462643383279502884;

uint powmod(uint base, uint exponent, uint prime) {
  /* This function computes: base raised to the power exponent modulus prime
   * in math notation: (base^exponent) mod prime
   */
  uint pm = 1;
  base = base%prime;
  while (exponent > 0) {
    if (exponent%2 == 1) { /* exponent is odd */
      pm = (pm*base)%prime;
    }
    exponent /= 2;
    base = (base*base)%prime;
  } 
  return pm;
}

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

void FFT(uint *array, int length, uint h, uint *recArr, uint prime) {
   uint hPow = 1, *evenCoef, *oddCoef;
   if(length == 1)
      return;
   length /= 2;
   evenCoef = recArr;
   oddCoef = recArr + length;

   for(int i = 0; i < length; i++) {
      evenCoef[i] = array[2 * i];
      oddCoef[i] = array[2 * i + 1];
   }

   FFT(oddCoef, length, powmod(h, 2, prime), array, prime);
   FFT(evenCoef, length, powmod(h, 2, prime), array, prime);
  
   for(int i = 0; i < length; i++) {
      array[i] = (evenCoef[i] + (hPow * oddCoef[i]) % prime ) % prime;
      array[length + i] = (evenCoef[i] + 2 * prime - (hPow * oddCoef[i]) % prime ) % prime;
      hPow = (hPow * h) % prime;
   }
}

int power2Size(int size) {
   int p = 1;
   while(p < size) {
      p *= 2;
   }
   return p;
}

void copyArray(int *array, int length, uint *cArray) {
   for (int i = 0; i < length; i++) {
      cArray[i] = array[i];
   }
}

int main(int argc, char* argv[]) {
   uint prime = 40961;
   int *x, lenX, pow2Len;
   uint *tmpX;

   x = readSignal(&lenX);
   pow2Len = power2Size(lenX);

   tmpX = safeMalloc(pow2Len * sizeof(uint));
   copyArray(x, lenX, tmpX);

   uint h, *recArr;
   /* recArr is passed to the FFT function to skip memory alloc at each recursive level */
   recArr = malloc(pow2Len * sizeof(uint));
   h = powmod(3, (prime - 1) / pow2Len, prime);
   FFT(tmpX, pow2Len, h, recArr, prime);
   free(recArr);

   for (int i = 0; i < lenX; i++) {
      x[i] = (int) tmpX[i];
   }
   
   printSignal(lenX, x);
   free(tmpX);
   free(x);
   return 0;
}