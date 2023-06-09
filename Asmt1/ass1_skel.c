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

   Signed by: Zilin Xu 1262248
   Dated:     2023/04/12

   Programming is fun!

*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************/

#define MAX_LINE 99999
#define LEAST_RES 0.5

// customized structs

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

typedef struct {
  double max;
  double min;
} month_cap_t;


// read the input file and return the data in a dynamic array
weather_data_t *read_input(weather_data_t total[], int *line_count) {
  // lines in each input file is not same, so use dynamic allocation to create
  // variable array in order to reduce potential memory usage

  // as we don't know how many lines in the input file, use a variable to record
  // the line count because it will be modified in this function, it need to be
  // passed by reference
  *line_count = 0;
  int position = 0;

  // skip the title row
  scanf("%*[^\n]%*c");

  // read the weather data into the array
  while (position < MAX_LINE) {
    int result = scanf("%d %d %d %d %d %lf %lf %lf", &total[position].year,
                       &total[position].month, &total[position].day,
                       &total[position].hour, &total[position].minute,
                       &total[position].solar, &total[position].wind,
                       &total[position].temp);
    if (result == EOF) {
      break;
    } else if (result != 8) {
      printf("Error: input file not correct at line %d", position + 1);
      exit(EXIT_FAILURE);
    }

    total[position].position =
        position; // stage 1 require first and last row of data input
    position++;
  }

  *line_count = position; // update the total line count
  return total;
}

// find the maxvalue of solar, wind and temp in the data
max_data_t find_max(weather_data_t *data, int line_count) {
  max_data_t max;
  // initialize the max value
  max.solar = 0;
  max.wind = 0;
  max.temp = 0;

  for (int i = 0; i < line_count; i++) {
    if (data[i].solar > max.solar) {
      max.solar = data[i].solar;
    }
    if (data[i].wind > max.wind) {
      max.wind = data[i].wind;
    }
    if (data[i].temp > max.temp) {
      max.temp = data[i].temp;
    }
  }

  return max;
}

// print out the result of stage 1
void print_stage_1_result(weather_data_t *data, int line_count,
                          max_data_t max) {
  printf("S1, %d data rows in total\n", line_count);
  printf("S1, row %5d: at %02d:%02d on %02d/%02d/%4d, solar = %4.0lf, wind = "
         "%5.2lf, temp = %4.1lf\n",
         data[0].position, data[0].hour, data[0].minute, data[0].day,
         data[0].month, data[0].year, data[0].solar, data[0].wind,
         data[0].temp);
  printf("S1, row %5d: at %02d:%02d on %02d/%02d/%4d, solar = %4.0lf, wind = "
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
         max.solar, max.wind, max.temp);
  printf("\n");
}

// calculate average solar for each hour gap in each month
int calc_avg_hourly_solar(weather_data_t *data, int line_count, int month,
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
  if (round(result.sum / result.count) >= LEAST_RES) { // by requirement, if result < 0.5 then return ..
    return round(result.sum / result.count);
  } else {
    return 0;
  }
}

// print out the result of stage 2 table
void stage_2_table_content(weather_data_t *data, int line_count, int month,
                           int hour) {
  for (int hr = 1; hr <= hour; hr++) {
    printf("S2, %02d-%02d |", hr - 1, hr);
    for (int m = 1; m <= month; m++) {
      if (calc_avg_hourly_solar(data, line_count, m, hr - 1) >= LEAST_RES) {
        if (m == 12) {
          printf(" %3d\n", calc_avg_hourly_solar(data, line_count, m, hr - 1));
        } else {
          printf(" %3d ", calc_avg_hourly_solar(data, line_count, m, hr - 1));
        }
      } else {
        if (m == 12) {
          printf("  ..\n");
        } else {
          printf("  .. ");
        }
      }
    }
  }
}

// print out the final result of stage 2
void print_stage_2_result(weather_data_t *data, int line_count) {
  printf("S2,              Average Solar Energy by Month and Time of Day\n");
  printf("S2,        Jan  Feb  Mar  Apr  May  Jun  Jul  Aug  Sep  Oct  Nov  "
         "Dec\n");
  printf("S2,       "
         "+----+----+----+----+----+----+----+----+----+----+----+----+\n");
  stage_2_table_content(data, line_count, 12, 24);
  printf("\n");
}

// find the max and min temperature in the data for each month
month_cap_t find_month_cap(weather_data_t *data, int line_count, int month) {
  month_cap_t result;
  result.max = 0.0;
  result.min = 50.0; // assume the lowest temperature is 50, if set to 0 it's
                     // so hard to change

  // update the max and min value
  for (int i = 0; i < line_count; i++) {
    if (data[i].month == month) {
      if (data[i].temp > result.max) {
        result.max = data[i].temp;
      }
      if (data[i].temp < result.min) {
        result.min = data[i].temp;
      }
    }
  }
  return result;
}

// create stage 3 table content, the graph
void create_stage_3_table(weather_data_t *data, int line_count, int month) {
  month_cap_t result = find_month_cap(data, line_count, month);
  if (month == 1) {
    printf("S3, Jan |");
  } else if (month == 2) {
    printf("S3, Feb |");
  } else if (month == 3) {
    printf("S3, Mar |");
  } else if (month == 4) {
    printf("S3, Apr |");
  } else if (month == 5) {
    printf("S3, May |");
  } else if (month == 6) {
    printf("S3, Jun |");
  } else if (month == 7) {
    printf("S3, Jul |");
  } else if (month == 8) {
    printf("S3, Aug |");
  } else if (month == 9) {
    printf("S3, Sep |");
  } else if (month == 10) {
    printf("S3, Oct |");
  } else if (month == 11) {
    printf("S3, Nov |");
  } else if (month == 12) {
    printf("S3, Dec |");
  }
  for (int i = -5; i < 50; i++) {
    if (i == 49) {
      printf("|");
      break;
    } else if (i < round(result.min) - 1 || i >= round(result.max)) {
      printf(" ");
    } else {
      printf("*");
    }
  }
}

// print out the final result of stage 3
void print_stage_3_result(weather_data_t *data, int line_count) {
  printf("S3,                  Min/Max Temperature by Month\n");
  printf("S3,    -5    0    5   10   15   20   25   30   35   40   45   50\n");
  printf("S3,     "
         "+----+----+----+----+----+----+----+----+----+----+----+\n");
  for (int i = 1; i <= 12; i++) {
    create_stage_3_table(data, line_count, i);
    printf("\n");
  }
  printf("S3,     +----+----+----+----+----+----+----+----+----+----+----+\n");
  printf(
      "S3,    -5    0    5   10   15   20   25   30   35   40   45   50\n\n");
  printf("ta daa!\n");
}

// function prototypes

weather_data_t *read_input(weather_data_t total[], int *line_count);
max_data_t find_max(weather_data_t *data, int line_count);
void print_stage_1_result(weather_data_t *data, int line_count, max_data_t max);
int calc_avg_hourly_solar(weather_data_t *data, int line_count, int month,
                          int hour);
void stage_2_table_content(weather_data_t *data, int line_count, int month,
                           int hour);
void print_stage_2_result(weather_data_t *data, int line_count);
month_cap_t find_month_cap(weather_data_t *data, int line_count, int month);
void create_stage_3_table(weather_data_t *data, int line_count, int month);
void print_stage_3_result(weather_data_t *data, int line_count);

int main() {
  int line_count = 0;
  weather_data_t total[MAX_LINE];
  // all input data will be stored in this array
  weather_data_t *data = read_input(total, &line_count);
  max_data_t max = find_max(data, line_count);
  // print stage 1 result
  print_stage_1_result(data, line_count, max);
  // print stage 2 result
  print_stage_2_result(data, line_count);
  // print stage 3 result
  print_stage_3_result(data, line_count);
  return 0;
}
