/* file: sumToProd.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 25 Nov 2020 */
/* version: 1.0 */
/* Description: This program outputs the new frequencies 
after turning the signal of a beat note (sum of sinusoids) 
to a product of sinusoids. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;

int main(int argc, char* argv[]) {
   double f0, f1;
   scanf("%lf %lf", &f0, &f1);
   printf("%.2lf %.2lf\n", (double)abs(f0 - f1) / 2, (f0 + f1) / 2);
   return 0;
}