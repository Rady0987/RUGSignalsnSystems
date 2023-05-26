/* file: cartToPol.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 25 Nov 2020 */
/* version: 1.0 */
/* Description: This program reads a Cartesian coordinate (x, y) 
and converts it into the corresponding Polar coordinate (r, θ) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;

int main(int argc, char* argv[]) {
   double x, y, theta;
   scanf("%lf %lf", &x, &y);
   printf("%.2lf ", sqrt(pow(x, 2) + pow(y, 2)));
   theta = atan2(y, x);
   if(theta == pi)
      theta = -pi;
   printf("%.2lf\n", theta);
   return 0;
}