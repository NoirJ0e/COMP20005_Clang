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

void stage_1(void) {
  // Stage 1
  // initialize variables
  int year, month, day, hour, minute, count = 0, max_solar;
  double solar, wind, temp, max_wind, max_temp;
  // initialize variables for the first row of data
  int year_t, month_t, day_t, hour_t, minute_t, count_t;
  double solar_t, wind_t, temp_t;
  // bypass the first line of data as it is the title;
  // HACK: use scanf("%*[^\n]%*c") to bypass the first line of data, it will
  // skip all characters until it meets a newline character, then it will skip
  // the newline character;
  scanf("%*[^\n]%*c");
  // read data from file with "<" operator with while loop, break with read EOF;
  while (scanf("%d%d%d%d%d%lf%lf%lf", &year, &month, &day, &hour, &minute,
               &solar, &wind, &temp) != EOF) {
    // store the first row of data
    if (count == 0) {
      count_t = count;
      year_t = year;
      month_t = month;
      day_t = day;
      hour_t = hour;
      minute_t = minute;
      solar_t = solar;
      wind_t = wind;
      temp_t = temp;
      max_solar = solar;
      max_wind = wind;
      max_temp = temp;
    }
    // count total lines of data, with getchar() and check if ending with \n;
    if (getchar() == '\n') {
      count++;
    }
    if (solar > max_solar) {
      max_solar = solar;
    }
    if (wind > max_wind) {
      max_wind = wind;
    }
    if (temp > max_temp) {
      max_temp = temp;
    }
    //
  }
  // print out the result of stage 1
  printf("S1, %d data rows in total\n", count);
  printf("S1, row %5d: at %2d:%2d on %02d/%02d/%4d, solar = %3.0lf, wind = "
         "%2.2lf, temp = %4.1lf\n",
         count_t, hour_t, minute_t, day_t, month_t, year_t, solar_t, wind_t,
         temp_t);
  printf("S1, row %5d: at %2d:%2d on %02d/%02d/%4d, solar = %3.0lf, wind = "
         "%2.2lf, temp = %2.1lf\n",
         count - 1, hour, minute, day, month, year, solar, wind, temp);
  printf("S1, max solar = %4d\n", max_solar);
  printf("S1, max wind  = %4.1lf\n", max_wind);
  printf("S1, max temp  = %2.1lf\n", max_temp);
}

void stage_2(void) {
  printf("S2,              Average Solar Energy by Month and Time of Day");
  printf("S2,        Jan  Feb  Mar  Apr  May  Jun  Jul  Aug  Sep  Oct  Nov  Dec");
  printf("S2,       +----+----+----+----+----+----+----+----+----+----+----+----+");

}

int main(int argc, char *argv[]) { 
  stage_1();
  return 0; 
}
