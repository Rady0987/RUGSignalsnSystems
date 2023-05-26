/* file: sameFreqSum.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 25 Nov 2020 */
/* version: 1.0 */
/* Description: This program outputs the equation for the sum of 
the signals A0 cos(2πft + ϕ0) + A1 cos(2πft + ϕ1) in the form
x(t) = A cos(2πft + ϕ)*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;

int main(int argc, char* argv[]) {
   double sinOne[2], sinTwo[2], f, x1, y1, x2, y2, x3, y3, r, theta;
   /* 0 -> amplitude, 1 -> phase */
   scanf("%lf %lf %lf %lf %lf", &f, &sinOne[0], 
   &sinOne[1], &sinTwo[0], &sinTwo[1]);
   x1 = sinOne[0] * cos(sinOne[1]);
   x2 = sinTwo[0] * cos(sinTwo[1]);
   y1 = sinOne[0] * sin(sinOne[1]);
   y2 = sinTwo[0] * sin(sinTwo[1]);
   x3 = x1 + x2;
   y3 = y1 + y2;
   r = sqrt(pow(x3, 2) + pow(y3, 2));
   if((int)r == 0) {
      printf("x(t)=0.00\n");
   } else {
      theta = atan2(y3, x3);
      printf("x(t)=%.2lf*cos(2*pi*%.2lf*t+%.2lf)\n", r, f, theta);
   }
   return 0;
}