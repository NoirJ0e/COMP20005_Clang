/* Program to analyze weather station data.

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

   Signed by: [Zilin Xu 1262248]
   Dated:     [2023/04/12]

*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************/

#define MAX_LINE 99999

typedef struct {
  int year, month, day, hour, minute;
  double solar, wind, temp;
  int position;
} weather_data_t;

typedef struct {
  double solar, wind, temp;
} max_data_t;

typedef struct {
  int month, count;
  double sum;
} solar_hourly_t;

weather_data_t *read_input(int *line_count) {
  // TODO: Sort this array by hour, this should boost efficiency for following
  // stage
  weather_data_t *total = malloc(sizeof(weather_data_t) * MAX_LINE);
  *line_count = 0;
  int position = 0;

  // skip the title row
  scanf("%*[^\n]%*c");

  // read the weather data into the array
  while (position < MAX_LINE &&
         scanf("%d %d %d %d %d %lf %lf %lf", &total[position].year,
               &total[position].month, &total[position].day,
               &total[position].hour, &total[position].minute,
               &total[position].solar, &total[position].wind,
               &total[position].temp) == 8) {
    total[position].position = position;
    position++;
  }

  *line_count = position;
  return total;
}

// TODO: find a way to boost its efficiency
max_data_t *find_max(weather_data_t *data, int line_count) {
  max_data_t *max = malloc(sizeof(max_data_t));
  // as this is pointer, use -> instead of .
  max->solar = 0;
  max->wind = 0;
  max->temp = 0;

  for (int i = 0; i < line_count; i++) {
    if (data[i].solar > max->solar) {
      max->solar = data[i].solar;
    }
    if (data[i].wind > max->wind) {
      max->wind = data[i].wind;
    }
    if (data[i].temp > max->temp) {
      max->temp = data[i].temp;
    }
  }

  return max;
}

void stage_1_result(weather_data_t *data, int line_count, max_data_t *max) {
  printf("S1, %d data rows in total\n", line_count);
  printf("S1, row %6d: at %02d:%02d on %02d/%02d/%4d, solar = %4.0lf, wind = "
         "%5.2lf, temp = %4.1lf\n",
         data[0].position, data[0].hour, data[0].minute, data[0].day,
         data[0].month, data[0].year, data[0].solar, data[0].wind,
         data[0].temp);
  printf("S1, row %6d: at %02d:%02d on %02d/%02d/%4d, solar = %4.0lf, wind = "
         "%5.2lf, temp = "
         "%4.1lf\n",
         data[line_count - 1].position, data[line_count - 1].hour,
         data[line_count - 1].minute, data[line_count - 1].day,
         data[line_count - 1].month, data[line_count - 1].year,
         data[line_count - 1].solar, data[line_count - 1].wind,
         data[line_count - 1].temp);
  printf("S1, max solar = %4.0lf\n"
         "S1, max wind  = %4.1lf\n"
         "S1, max temp  = %4.1lf\n",
         max->solar, max->wind, max->temp);
}

int avg_hourly_solar(weather_data_t *data, int line_count, int month,
                     int hour) {
  solar_hourly_t result;
  result.month = month;
  result.count = 0;
  result.sum = 0;
  for (int i = 0; i < line_count; i++) {
    if (data[i].month == month && data[i].hour == hour) {
      result.count++;
      result.sum += data[i].solar;
    }
  }
  // with <math.h>
  if (round(result.sum / result.count) >= 0.5) {
    return round(result.sum / result.count);
  } else {
    return 0;
  }
}

// TODO: GET CORRECT RESULT
void stage_2_table_content(weather_data_t *data, int line_count, int month,
                           int hour) {
  for (int hr = 1; hr <= hour; hr++) {
    printf("S2, %02d-%02d |", hr-1, hr);
    for (int m = 1; m <= month; m++) {
      if (m == 12) {
        printf(" %3d ", avg_hourly_solar(data, line_count, m, hr));
      } else {
        printf(" %3d \n", avg_hourly_solar(data, line_count, m, hr));
      }
    }
  }
}

void stage_2_result(weather_data_t *data, int line_count) {
  printf("S2,              Average Solar Energy by Month and Time of Day\n");
  printf("S2,        Jan  Feb  Mar  Apr  May  Jun  Jul  Aug  Sep  Oct  Nov  "
         "Dec\n");
  printf("S2,       "
         "+----+----+----+----+----+----+----+----+----+----+----+----+\n");
  stage_2_table_content(data, line_count, 12, 24);
}

int main() {
  int line_count = 0;
  // all input data will be stored in this array
  weather_data_t *data = read_input(&line_count);
  max_data_t *max = find_max(data, line_count);
  // print stage 1 result
  stage_1_result(data, line_count, max);
  stage_2_result(data, line_count);
  free(data); // free the memory allocated for the data array

  return 0;
}
