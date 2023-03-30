// 01
/* #include <stdio.h>

int main() {
  int a,b,c,d,e,f,g;
    a = 6;
    b = a + 3 * 4;
    c = b - b % 4;
    d = b / 3;
    e = a + b / 2;
    f = (a + b / 2 + c) / 3;
    g = a - b + c - d + e - f;
    printf("%d\n",c);
    printf("%d\n",f);
    printf("%d\n",g);
} */

// 02
// #include <math.h>
// #include <stdio.h>
//
// #define FL_FMT "%.2lf"
// #define TIME_FMT "%02d:%02d:%02d"
// #define M_PI 3.1415926 // Just for grok, somehow it cant import <math.h> even
// with exampe command
//
// int main(int argc, char *argv[]) {
//   /* the declarations you need to define */
//   double r, area_square, perimeter_square, area_circle, perimeter_circle,
//       elapsed_hours;
//   int start_hour, start_min, start_sec, finish_hour, finish_min, finish_sec;
//
//   /* read in length/radius r, start time and finish time
//    * assuming that they are nice numbers (no error checking) */
//   printf("Enter a length/radius r: ");
//   scanf("%lf", &r);
//
//   printf("Enter event start time (hh:mm:ss): ");
//   scanf("%d:%d:%d", &start_hour, &start_min, &start_sec);
//
//   printf("Enter event finish time (hh:mm:ss): ");
//   scanf("%d:%d:%d", &finish_hour, &finish_min, &finish_sec);
//
//   /* *************************************************************** */
//   /* Hey! Listen! Change these assignment statements! */
//
//   /* 1. The area of a square of edge length r */
//   area_square = pow(r, 2);
//
//   /* 2. The perimeter of a square of edge length `r` */
//   perimeter_square = r * 4;
//
//   /* 3. The area of a circle of radius `r` */
//   area_circle = M_PI * pow(r, 2);
//
//   /* 4. The perimeter of a circle of radius `r` */
//   perimeter_circle = M_PI * 2 * r;
//
//   /* 5. Time in elapsed hours between the start time
//    * (`start_hour`:`start_min`:`start_sec`) and finishing time
//    * (`finish_hour`:`finish_min`:`finish_sec`) of some event, assuming those
//    * two times are within the same day. */
//   // Things after decimals places are calculated with secs
//
//   int diff_sec;
//   diff_sec = (finish_hour * 3600 + finish_min * 60 + finish_sec) -
//              (start_hour * 3600 + start_min * 60 + start_sec);
//
//   if (diff_sec < 0) {
//     elapsed_hours = (diff_sec / -3600.);
//   }
//   elapsed_hours = diff_sec / 3600.;
//
//   /* *************************************************************** */
//   /* and now we print out the results to be checked */
//   printf("1. The area of a square of edge length " FL_FMT "        = " FL_FMT
//          "\n",
//          r, area_square);
//   printf("2. The perimeter of a square of edge length " FL_FMT "   = " FL_FMT
//          "\n",
//          r, perimeter_square);
//   printf("3. The area of a circle of radius " FL_FMT "             = " FL_FMT
//          "\n",
//          r, area_circle);
//   printf("4. The perimeter of a circle of radius " FL_FMT "        = " FL_FMT
//          "\n",
//          r, perimeter_circle);
//   printf("5. The time in elapsed hours between start time\n     " TIME_FMT
//          " and finish time " TIME_FMT " of an event  = " FL_FMT "\n",
//          start_hour, start_min, start_sec, finish_hour, finish_min,
//          finish_sec, elapsed_hours);
// }

// 03
// #include <float.h>
// #include <limits.h>
// #include <stdio.h>
//
//
// int main() {
//   printf("ints    : %13d to %13d\n", INT_MIN, INT_MAX);
//   printf("floats  : %13.6e to %13.6e\n", FLT_MIN, FLT_MAX);
//   printf("doubles : %.6e to %13.6e\n", DBL_MIN, DBL_MAX);
// }
//

// 04
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 123;
  double x = 123.4567;
  char *m = "hello, hello";
  printf("n = %3d, x = %8.4f, m = \"%-15s\"\n", n, x, m);
}

// 05
// #include <stdio.h>
// #include <stdlib.h>
//
// int main() {
//   int user_input;
//   printf("Enter degrees F: ");
//   if (scanf("%d",&user_input) == 0) {
//     exit(EXIT_FAILURE);
//   };
//   double degree_in_c;
//   degree_in_c = (double) (user_input - 32.00) * (5./9);
//   printf("In degrees C is: %.1lf\n", degree_in_c);
// }
//
