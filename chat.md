I got a C-lang function:

```c
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************/

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

// dx = distance to East, dy = distance to North
// lx = loudness at x, ly = loudness at y
// lo = loudness at origin
typedef struct {
  double dx, dy, power;
  double lx, ly, lo;
} sound_data_t;

// function prototypes
double calc_powi(double power);
double calc_spli(double powi, double ri);
double calc_dist(double x, double y);
double calc_spl_total(double data[], int src_count);
int calc_display_number(double spl_total);
int calc_intersections_quantity(double gridlength);
sound_data_t *read_data(sound_data_t data[], int *src_count);
void calc_stage1_loudness(sound_data_t data[], int src_count);
void stage_1_result(sound_data_t data[], int src_count);
void stage_2_result(sound_data_t data[], int src_count);
void stage_3_result(sound_data_t data[], int src_count);

// calculation functions
double calc_powi(double power) { return 10 * log10(power / W0); }

double calc_spli(double powi, double ri) {
  double r = (2 + ALPHA) * PI * pow(ri, 2);
  return powi + 10 * log10(Q / (4 * PI * pow(ri, 2)) + 4 / r);
}

double calc_dist(double x, double y) { return sqrt(pow(x, 2) + pow(y, 2)); }

double calc_spl_total(double data[], int src_count) {
  double spli_total = 0;
  for (int i = 0; i < src_count; i++) {
    spli_total += pow(10, data[i] / 10);
  }

  double intensity = 10 * log10(spli_total);
  return intensity;
}

// calculate the number of points of intersetion with grids in the field

// calculate the number of points of intersetion with grids in the field
int calc_intersections_quantity(double gridlength) {
  return (int)(WIDTH / gridlength + 1) * (HEIGHT / gridlength + 1);
}

int calc_display_number(double spl_total) {
  int result = 0;
  if (spl_total < 20) {
    result = 0;
  } else if (20 < spl_total && spl_total < 25) {
    result = 2;
  } else if (25 < spl_total && spl_total < 30) {
    result = 0;
  } else if (30 < spl_total && spl_total < 35) {
    result = 3;
  } else if (35 < spl_total && spl_total < 40) {
    result = 0;
  } else if (40 < spl_total && spl_total < 45) {
    result = 4;
  } else if (45 < spl_total && spl_total < 50) {
    result = 0;
  } else if (50 < spl_total && spl_total < 55) {
    result = 5;
  } else if (55 < spl_total && spl_total < 60) {
    result = 0;
  } else if (60 < spl_total && spl_total < 65) {
    result = 6;
  } else if (65 < spl_total && spl_total < 70) {
    result = 0;
  } else if (70 < spl_total && spl_total < 75) {
    result = 7;
  } else if (75 < spl_total && spl_total < 80) {
    result = 0;
  } else if (80 < spl_total && spl_total < 85) {
    result = 8;
  } else if (85 < spl_total && spl_total < 90) {
    result = 0;
  } else if (90 <= spl_total) {
    result = 9;
  }
  return result;
}

// read data from file, store each into corresponding attribute
// and record total number of data
sound_data_t *read_data(sound_data_t data[], int *src_count) {
  int line_count = 0;
  while (line_count < MAX_DATA) {
    double result = scanf("%lf%lf%lf", &data[line_count].dx,
                          &data[line_count].dy, &data[line_count].power);
    if (result == EOF) {
      break;
    } else if (result != 3) {
      printf("Invalid input\n");
      exit(EXIT_FAILURE);
    }
    line_count++;
  }

  *src_count = line_count;

  return data;
}

// stage 1
void calc_stage1_loudness(sound_data_t data[], int src_count) {
  for (int i = 0; i < src_count; i++) {
    data[i].lo =
        calc_spli(calc_powi(data[i].power), calc_dist(data[i].dx, data[i].dy));
  }
}

void stage_1_result(sound_data_t data[], int src_count) {
  printf("S1, number of sound sources: %d\n", src_count);
  for (int i = 0; i < src_count; i++) {
    printf("S1, %4.1lfm E, %4.1lfm N, power %7.5lfW, contributes %3.1lf dB "
           "at origin\n",
           data[i].dx, data[i].dy, data[i].power, data[i].lo);
  }
}

void stage_2_result(sound_data_t data[], int src_count) {
  // gridLength = 0.25, 0.5, 1.0
  // TODO: starting from 0.25 and determine on the left or right, reduce
  // calculation, current one is pure bruth force
  for (double gridLength = 1.0; gridLength >= 0.25; gridLength /= 2) {
    int dangerCount = 0;
    for (double y = HEIGHT + 1; y >= 0; y -= gridLength) {
      for (double x = 0; x <= WIDTH + 1; x += gridLength) {
        double spl_at_each_point[src_count];
        // This for loop calculate the SPL at certain cordinates in the
        // field from the sound sources and store them in an array in
        // order to calculate the total SPL at that point
        for (int i = 0; i < src_count; i++) {
          double dist = calc_dist(x - data[i].dx, y - data[i].dy);
          double spli = calc_spli(calc_powi(data[i].power), dist);
          spl_at_each_point[i] = spli;
        }
        double spl_total = calc_spl_total(spl_at_each_point, src_count);
        if (spl_total >= DANGER_LEVEL) {
          dangerCount++;
        }
      }
    }
    printf("S2, grid = %4.2lfm, danger points = %6d / %6d = %4.2lf%%\n",
           gridLength, dangerCount, calc_intersections_quantity(gridLength),
           (dangerCount * 100.0) / calc_intersections_quantity(gridLength));
  }
}

void stage_3_result(sound_data_t data[], int src_count) {
  for (double y = 99.0; (y < HEIGHT && 0 < y); y -= 2) {
    double spl_at_each_point[src_count];
    for (double x = 0.5; x < WIDTH; x++) {
      for (int i = 0; i < src_count; i++) {
        double dist = calc_dist(x - data[i].dx, y - data[i].dy);
        double spli = calc_spli(calc_powi(data[i].power), dist);
        spl_at_each_point[i] = spli;
      }
      double spl_total = calc_spl_total(spl_at_each_point, src_count);
      int result = calc_display_number(spl_total);

      if (x == 0.5) { // Beginning of each row
        if (result != 0) {
          printf("S3, %d", result);
        } else {
          printf("S3,  ");
        }
      } else {
        if (x == 73.5) { // End of each row
          if (result != 0) {
            printf("%d\n", result);
          } else {
            printf(" \n");
          }
        } else {
          if (result != 0) {
            printf("%d", result);
          } else {
            printf(" ");
          }
        }
      }
    }
  }
  // dont forget the ta daa!
  printf("\nta daa!\n");
}

int main(int argc, char *argv[]) {
  int src_count = 0;
  sound_data_t source[MAX_DATA];
  sound_data_t *data = read_data(source, &src_count);

  calc_stage1_loudness(data, src_count);
  stage_1_result(data, src_count);
  printf("\n");
  stage_2_result(data, src_count);
  printf("\n");
  stage_3_result(data, src_count);

  return 0;
}
```

When dealing with dataset 1 

30.0 70.0 0.0005
35.0 63.0 0.0006
36.5 27.0 0.0008
70.0 25.0 0.0020
20.0 50.0 0.0025

It have the correct danger point result output, which are 

S2, grid = 1.00m, danger points =    140 /   7575 = 1.85%
S2, grid = 0.50m, danger points =    570 /  29949 = 1.90%
S2, grid = 0.25m, danger points =   2230 / 119097 = 1.87%

However, when dealing with dataset 3 

0.1 0.1 0.00001
0.1 33.3 0.00010
0.1 66.7 0.00001
0.1 99.9 0.00001
37.0 0.1 0.00001
37.0 99.9 0.00001
73.9 0.1 0.00001
73.9 33.3 0.00001
73.9 66.7 0.00010
73.9 99.9 0.00001

My output are:

S2, grid = 1.00m, danger points =     10 /   7575 = 0.13%
S2, grid = 0.50m, danger points =     24 /  29949 = 0.08%
S2, grid = 0.25m, danger points =     87 / 119097 = 0.07%

But the correct output should be:

S2, grid = 1.00m, danger points =     10 /   7575 = 0.13%
S2, grid = 0.50m, danger points =     22 /  29949 = 0.07%
S2, grid = 0.25m, danger points =     76 / 119097 = 0.06%
