/* file: microphones.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 25 Nov 2020 */
/* version: 1.0 */
/* Description: This program computes the amplitude of the
sinusoid that is observed by the microphone from to sources. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;
const int speed = 343;

int main(int argc, char* argv[]) {
   int A, f, x0, x1, x2;
   double phase, w, w1, x, y;
   scanf("%d %d %lf", &A, &f, &phase);
   scanf("%d %d %d", &x0, &x1, &x2);
   w = 2 * pi * f * abs(x0 - x2) / speed;
   w1 = 2 * pi * f * abs(x1 - x2) / speed;
   x = A * (cos(w + phase) + cos(w1 + phase));
   y = A * (sin(w + phase) + sin(w1 + phase));
   printf("%.2lf\n", sqrt(x * x + y * y));
   return 0;

}