/* file: polToCart.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 25 Nov 2020 */
/* version: 1.0 */
/* Description: This program reads a Polar coordinate (r, θ)  
and converts it into the corresponding Cartesian coordinate (x, y)*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;

int main(int argc, char* argv[]) {
   double r, theta;
   scanf("%lf %lf", &r, &theta);
   printf("%.2lf %.2lf\n", r * cos(theta), r * sin(theta));
   return 0;
}