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

int calc_display_number(double spl_total) {
  int result = 0;
  static const int result_values[] = {0, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9};
  static const double range_values[] = {20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90};
  static const int num_ranges = sizeof(range_values) / sizeof(range_values[0]);

  for (int i = 0; i < num_ranges; i++) {
    if (spl_total < range_values[i]) {
      break;
    }
    result = result_values[i];
  }

  return result;
}

int main(void) {
  double spl_total = 81.0;
  int result = calc_display_number(spl_total);
  printf("result: %d\n", result);
  return 0;

}
