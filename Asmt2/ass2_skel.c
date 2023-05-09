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

// dx = distance to East, dy = distance to North
// lx = loudness at x, ly = loudness at y
// lo = loudness at origin
typedef struct {
  double dx, dy, power;
  double lx, ly, lo;
} sound_data_t;

// calculation functions
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
    data[i].lo = calc_spli(calc_powi(data[i].power), sqrt(pow(data[i].dx, 2) + pow(data[i].dy, 2)));
  }
}
//
void stage_1_result(sound_data_t data[], int src_count) {
  printf("S1, number of sound sources = %d\n", src_count);
  for (int i = 0; i < src_count; i++) {
    printf("S1, %3.1lfm E, %3.1lfm N, power of %7.5lfW, contributes %3.1lf dB at origin\n",
           data[i].dx, data[i].dy, data[i].power, data[i].lo);
  }
}


int main(int argc, char *argv[]) {
  int src_count = 0;
  sound_data_t source[MAX_DATA];
  sound_data_t *data = read_data(data, &src_count);

  printf("src_count: %d\n", src_count);

  calc_stage1_loudness(data, src_count);
  stage_1_result(data, src_count);

  return 0;
}
