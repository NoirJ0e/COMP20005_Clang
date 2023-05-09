#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA 100
#define P0 0.00002
#define W0 1e-12
#define ALPHA 0.5
#define Q 2


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
  double power = 0.0006;
  double east = 35.0, north = 63.0, test = sqrt(pow(east, 2) + pow(north, 2));

  double dB_east = calc_spli(calc_powi(power), east);
  printf("%lf\n", dB_east);

  double dB_north = calc_spli(calc_powi(power), north);
  printf("%lf\n", dB_north);

  double dB_origin = calc_spl_total(dB_east, dB_north);
  printf("%lf\n", dB_origin);

  double dB_test = calc_spli(calc_powi(power), test);
  printf("%lf\n", dB_test);


  return 0;
}
