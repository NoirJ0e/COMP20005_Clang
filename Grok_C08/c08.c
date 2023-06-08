// Ex 01
/* #include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double p1, p2;
} vector_t;

double distance(vector_t p1, vector_t p2) {
  return (sqrt(pow(p2.p1 - p1.p1,2)+pow(p2.p2 - p1.p2,2)));
}

int main(void) {
  vector_t p1, p2;
  printf("Enter two points: ");
  scanf(" (%lf,%lf) (%lf,%lf)", &p1.p1, &p1.p2, &p2.p1, &p2.p2);
  printf("distance between (%.1lf,%4.1lf) and (%.1lf,%4.1lf) is %.1lf\n", p1.p1, p1.p2, p2.p1, p2.p2, distance(p1, p2));
} */

// Ex 02

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 100

typedef struct {
   int num_points;
   double x[MAX_POINTS];
   double y[MAX_POINTS];
} poly_t;

double distance(double x1, double y1, double x2, double y2) {
   return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

double perimeter(poly_t P) {
   double perim = 0;
   for (int i = 0; i < P.num_points; i++) {
       double x1 = P.x[i];
       double y1 = P.y[i];
       double x2 = P.x[(i + 1) % P.num_points];
       double y2 = P.y[(i + 1) % P.num_points];
       perim += distance(x1, y1, x2, y2);
   }
   return perim;
}

int main() {
   poly_t P;
   P.num_points = 0;

   printf("Enter (3-100) points counter-clockwise:\n");
   while (scanf("%lf,%lf", &P.x[P.num_points], &P.y[P.num_points]) == 2) {
       P.num_points++;
       if (P.num_points >= MAX_POINTS) {
           printf("Polygon has too many points!\n");
           return 1;
       }
   }

   if (P.num_points == 0 || P.num_points == 1 || P.num_points == 2) {
       printf("Invalid number of points!\n");
       return 1;
   }

   double perim = perimeter(P);
   printf("Perimeter is %.4lf\n", perim);

   return 0;
}

