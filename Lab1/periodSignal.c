/* file: periodSignal.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 25 Nov 2020 */
/* version: 1.0 */
/* Description: This program outputs the fundamental 
period T0 (integer, in microseconds) of a sum of sinusoids 
as input. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;

int lcm(int a, int b) {
   int multiple = 1;
   while(multiple % b || multiple % a) {
      multiple++;
   }
   return multiple;
}

int main(int argc, char* argv[]) {
   int n, T0;
   scanf("%d", &n);
   int periods[n];
   for(int i = 0; i < n; i++) {
      scanf("%*d %d %*lf", &periods[i]);
   }
   T0 = periods[0];

   for(int i = 1; i < n; i++) {
      T0 = lcm(T0, periods[i]);
   }
   printf("%d\n", T0);
   return 0;
}