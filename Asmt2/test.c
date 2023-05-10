#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA 100
#define P0 0.00002
#define W0 1e-12
#define ALPHA 0.5
#define Q 2
#define FIELD_SIZE 7400
#define WIDTH 74
#define HEIGHT 100
#define DANGER_LEVEL 80
#define PI 3.141592653589793238


double calc_powi(double power) {
  return 10 * log10(power / W0);
}

double calc_spli(double powi, double ri) {
  double r = (2+ALPHA) * M_PI * pow(ri,2);
  return powi + 10 * log10(Q/(4 * M_PI * pow(ri, 2)) + 4/r);
}

double calc_spl_total(double dB_east, double dB_north) {
  return 10 * log10(pow(10, dB_east/10) + pow(10, dB_north/10));
}

int main() {
  if (0 == 0.0) {
    printf("1");
  } else {
    printf("2");
  }

  return 0;
}
