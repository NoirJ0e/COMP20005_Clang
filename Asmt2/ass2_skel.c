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
int calc_intersections_quantity(double gridlength);
sound_data_t *read_data(sound_data_t data[], int *src_count);
void calc_stage1_loudness(sound_data_t data[], int src_count);
void stage_1_result(sound_data_t data[], int src_count);
void stage_2_result(sound_data_t data[], int src_count);

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
        data[i].lo = calc_spli(calc_powi(data[i].power),
                               calc_dist(data[i].dx, data[i].dy));
    }
}

void stage_1_result(sound_data_t data[], int src_count) {
    printf("S1, number of sound sources: %d\n", src_count);
    for (int i = 0; i < src_count; i++) {
        printf(
            "S1, %3.1lfm E, %3.1lfm N, power %7.5lfW, contributes %3.1lf dB "
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
                    if (data[i].dx == x && data[i].dy == y) {
                        if (data[i].dx - x == 0 && data[i].dy - y == 0) {
                          dangerCount++; // just at the sound source dB gonna be infinity
                          continue;
                        }
                    }
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

int main(int argc, char *argv[]) {
    int src_count = 0;
    sound_data_t source[MAX_DATA];
    sound_data_t *data = read_data(source, &src_count);

    calc_stage1_loudness(data, src_count);
    stage_1_result(data, src_count);
    printf("\n");
    stage_2_result(data, src_count);

    return 0;
}
