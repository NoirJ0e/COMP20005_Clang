/* Program to create sound-level maps.

   Skeleton written by Alistair Moffat, ammoffat@unimelb.edu.au,
   April 2023, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Zilin Xu 1262248
   Dated:     09/05/2023

   Programming is fun!

*/

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
#define WIDTH 74.0
#define HEIGHT 100.0
#define DANGER_LEVEL 80
#define PI 3.141592653589793238

// dx = distance to East, dy = distance to North, power = power of sound source
// lx = loudness at x, ly = loudness at y, lo = loudness at origin
typedef struct {
    double dx, dy, power,lo;
} sound_data_t;

// function prototypes
double calc_pow_i(double power);
double calc_spl_i(double powi, double ri);
double calc_prms(double x, double y);
double calc_spl_total(double data[], int src_count);
int calc_intersections_quantity(double gridlength);
sound_data_t *read_data(sound_data_t data[], int *src_count);
void calc_stage1_loudness(sound_data_t data[], int src_count);
void stage_1_result(sound_data_t data[], int src_count);
void stage_2_result(sound_data_t data[], int src_count);
// with arm64 cpu can pass int spl_total, but with x64 cpu it will miss a result
// int stage_3_table_content(int spl_total);
int stage_3_table_content(double spl_total);
void stage_3_result(sound_data_t data[], int src_count);

// calculation functions, according to formula provided in handout
double calc_pow_i(double power) { return 10 * log10(power / W0); }

double calc_spl_i(double powi, double ri) {
    double r = (2 + ALPHA) * PI * pow(ri, 2);
    return powi + 10 * log10(Q / (4 * PI * pow(ri, 2)) + 4 / r);
}

double calc_prms(double x, double y) { return sqrt(pow(x, 2) + pow(y, 2)); }

double calc_spl_total(double data[], int src_count) {
    double spli_total = 0;
    for (int i = 0; i < src_count; i++) {
        spli_total += pow(10, data[i] / 10);
    }

    return 10 * log10(spli_total);  // spl_total, according to formula
}

// calculate the number of points of intersetion with grids in the field
int calc_intersections_quantity(double gridlength) {
    return (int)(WIDTH / gridlength + 1) * (HEIGHT / gridlength + 1);
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
        data[i].lo = calc_spl_i(calc_pow_i(data[i].power),
                                calc_prms(data[i].dx, data[i].dy));
    }
}

void stage_1_result(sound_data_t data[], int src_count) {
    printf("S1, number of sound sources: %d\n", src_count);
    for (int i = 0; i < src_count; i++) {
        printf(
            "S1, %4.1lfm E, %4.1lfm N, power %7.5lfW, contributes %3.1lf dB "
            "at origin\n",
            data[i].dx, data[i].dy, data[i].power, data[i].lo);
    }
}

// stage 2
void stage_2_result(sound_data_t data[], int src_count) {
    // as handout required, gridlength is 1m, 0.5m, 0.25m
    for (double gridLength = 1.0; gridLength >= 0.25; gridLength /= 2) {
        int dangerCount =
            0;  // while gridLength changes, dangerCount should reset
        // imagine the field as a cordination system, x-axis is East, y-axis is
        // North start all calculation from the origin, which is (0,0)
        for (double y = HEIGHT; y >= 0; y -= gridLength) {
            for (double x = 0; x <= WIDTH; x += gridLength) {
                double spl_at_each_point[src_count];
                /* This for loop calculate the SPL at certain cordinates in the
                field from the sound sources and store them in an array in
                order to calculate the total SPL at that point after*/
                for (int i = 0; i < src_count; i++) {
                    double dist = calc_prms(x - data[i].dx, y - data[i].dy);
                    double spli = calc_spl_i(calc_pow_i(data[i].power), dist);
                    spl_at_each_point[i] = spli;
                }
                // calculate the total SPL at that point and check if it's
                // dangerous
                double spl_total = calc_spl_total(spl_at_each_point, src_count);
                if (spl_total >= DANGER_LEVEL) {
                    dangerCount++;
                }
            }
        }

        // print out the result
        printf("S2, grid = %4.2lfm, danger points = %6d / %6d = %4.2lf%%\n",
               gridLength, dangerCount, calc_intersections_quantity(gridLength),
               (dangerCount * 100.0) / calc_intersections_quantity(gridLength));
    }
}

// stage 3

int stage_3_table_content(double spl_total) {
  if (spl_total >= 90) {
    return 9;
  } else if (spl_total < 20) {
    return 0;
  } else if (((int)spl_total % 10) >= 5) {
    return 0;
  }
  return (int)(spl_total / 10);
}

// there's no rounding for spl_total, only check the integer part thus using
// double to take parameter is unnecessary, conditions are based on the handout
/* int stage_3_table_content(double spl_total) {
    if (spl_total >= 90) {
        return 9;
    }
    switch ((int)spl_total) {
        case 20 ... 24:
            return 2;
        case 30 ... 34:
            return 3;
        case 40 ... 44:
            return 4;
        case 50 ... 54:
            return 5;
        case 60 ... 64:
            return 6;
        case 70 ... 74:
            return 7;
        case 80 ... 84:
            return 8;
        default:
            return 0;
    }
} */


void stage_3_result(sound_data_t data[], int src_count) {
    // according my knowledgebae,there's no way to output a table from bottom to
    // top in CLI, so start from top to bottom, unlike stage2, have to start
    // from top left corner
    for (double y = 99.0; (y < HEIGHT && 0 < y);
         y -= 2) {  // values provided by handout
        // same idea as stage2, calculate SPL at each point and store them in an
        // array and check final result
        double spl_at_each_point[src_count];
        printf("S3, ");
        for (double x = 0.5; x < WIDTH; x++) {
            for (int i = 0; i < src_count; i++) {
                double dist = calc_prms(x - data[i].dx, y - data[i].dy);
                double spli = calc_spl_i(calc_pow_i(data[i].power), dist);
                spl_at_each_point[i] = spli;
            }
            double spl_total = calc_spl_total(spl_at_each_point, src_count);
            int result = stage_3_table_content(spl_total);

            // print out the result table
            if (result != 0) {
              printf("%d", result);
            } else {
              printf(" ");
            }
        }
        printf("\n");
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
