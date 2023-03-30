// 01
/* #include <stdio.h>
#include <stdlib.h>
int main() {
  int res;
  res = !11 > (7 >= 8 != 9 / 10 && (-4 + (-2 * -3) < 5) && (6 <= 8));
  printf("%d",res);
} */
// 02
/* #include <stdio.h>
#include <stdlib.h>
int main() {
    int x = 1, y = 2;
    if (x > y); {
        printf("x = %d, y = %d\n", x, y);
        x = x + 1;
    }
    if (x < y); {
        printf("x = %d, y = %d\n", x, y);
        y = y + 2;
    }
    printf("x = %d, y = %d\n", x, y);
} */
// 03
/* #include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NUM_PARAMETERS 3

int main() {
  double a,b,c,d;
  // Get input first
  printf("Enter a b c: ");
  // exit when get non-numerical character DONE
  if (scanf("%lf %lf %lf", &a, &b, &c) != NUM_PARAMETERS) {
    printf("Error in input\n");
    exit(EXIT_FAILURE);
  };


  // Determine situation
  d = (b * b) - (4.*a*c);
  if (a == 0 ) {
    printf("Equation %.1lfx^2 + %.1lfx + %.1lf = 0 has\n    an infinite number
of roots\n", a, b, c); } else if (d == 0) { double root; root = (-b +
sqrt(d))/(2.*a); printf("Equation %.1lfx^2 + %.1lfx + %.1lf = 0 has\n    one
real root: x = %.1lf\n", a, b, c, root); } else if (d > 0) { double root1,root2;
    root1 = (-b + sqrt(d))/(2.*a);
    root2 = (-b - sqrt(d))/(2.*a);
    printf("Equation %.1lfx^2 + %.1lfx + %.1lf = 0 has\n    two real roots: x1 =
%.1lf, x2 = %.1lf\n", a, b, c, root1, root2); } else if (d < 0) {
    printf("Equation %.1lfx^2 + %.1lfx + %.1lf = 0 has\n    no real roots\n", a,
b, c);
  }
} */
// 04
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int main() {
  int year, month, date, month_date, leap_year;
  printf("Enter a date in dd/mm/yyyy format: ");

  // error handling
  if (scanf("%2d/%2d/%4d", &date, &month, &year) != 3){
    printf("Wrong Input!\n");
    exit(EXIT_FAILURE);
  }

  /* if ((month < 1) || (month > 12)) {
    exit(EXIT_FAILURE);
  } */

  leap_year = FALSE;
  // HACK: check if this year is leap year
  // source: https://stackoverflow.com/a/11595914/21301572
  if ((year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0)) {
    leap_year = TRUE;
  }

  switch(month) {

    // month with 31 days
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      month_date = 31;

    // month with 30 days
    case 4:
    case 6:
    case 9:
    case 11:
      month_date = 30;

    // feb is special
    case 2:
      if (leap_year == TRUE) {
        month_date = 29;
      } else {
        month_date = 28;
      }

  }

  // another input check
  /* if (date > month_date) {
    exit(EXIT_FAILURE);
  } */


  // output begins
  printf("The date today is: %02d/%02d/%4d\n", date, month, year);

  // cal tommorow begins
  // check if new year is coming
  if ((month == 12) && (date++ > month_date)) {
    year ++;
    date = 01;
    month = 01;
  } else if (date+1 > month_date) {
    month ++;
    date = 01;
  } else {
    date ++;
  }

  // following code doesnt work, whats the differnece between date++ and
  date+1 in clang? TODO
  /* if ((month == 12) && (date++ > month_date)) {

    year ++;
    date = 01;
    month = 01;
  } else if (date++ > month_date) {
    month ++;
    date = 01;
  } */

  printf("The date tomorrow is: %02d/%02d/%4d\n", date, month, year);
}

// 05
// #include <stdio.h>
// #include <stdlib.h>
//
// // A function used to caclculate how many days has been passed in a year,
// with
// // recurrsion
// int days_passed(int month, int date, int leap_year) {
//   int month_date;
//   switch (month) {
//
//   // month with 31 days
//   case 1:
//   case 3:
//   case 5:
//   case 7:
//   case 8:
//   case 10:
//   case 12:
//     month_date = 31;
//     break;
//
//   // month with 30 days
//   case 4:
//   case 6:
//   case 9:
//   case 11:
//     month_date = 30;
//     break;
//
//   // feb is special
//   case 2:
//     if (leap_year == 1) {
//       month_date = 29;
//     } else {
//       month_date = 28;
//     }
//     break;
//   }
//
//   if (month == 1) {
//     return date;
//   } else {
//     return month_date + days_passed(month - 1, date, leap_year);
//   }
// }
//
// int main() {
//   int year, month, date, leap_year;
//   printf("Enter date in dd/mm/yyyy format: ");
//
//   // error handling
//   if (scanf("%2d/%2d/%4d", &date, &month, &year) != 3) {
//     printf("Wrong Input!\n");
//     exit(EXIT_FAILURE);
//   }
//
//   leap_year = 0;
//   // check if this year is leap year
//   // source: https://stackoverflow.com/a/11595914/21301572
//   if ((year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0)) {
//     leap_year = 1;
//   }
//
//   // cal days passed
//   printf("%02d/%02d/%4d is day number %d in the year\n", date, month, year,
//          days_passed(month, date, leap_year));
// }

// 06
/* #include <stdio.h>
#include <stdlib.h>

int main() {
  int user_input;
  printf("Enter amount in cents: ");
  scanf("%d", &user_input);

  if ((user_input < 0) || (user_input > 99)) {
    printf("WRONG INPUT!\n");
    exit(EXIT_FAILURE);
  }

  int fifty_cents, twenty_cents, ten_cents, five_cents, two_cents, one_cent,
      amount_remaining;

  one_cent = 0;
  two_cents = 0;
  five_cents = 0;
  ten_cents = 0;
  twenty_cents = 0;
  fifty_cents = 0;
  amount_remaining = user_input;

  // maximum 50 cents can give can only be one
  if (user_input >= 50) {
    amount_remaining = user_input - 50;
    fifty_cents++;
    // printf("Current amount_remaining: %d, and 50c amount is %d\n",
    // amount_remaining, fifty_cents);
  }
  if (amount_remaining / 20 >= 1) {
    twenty_cents = amount_remaining / 20;
    amount_remaining = amount_remaining % 20;
    // printf("Current amount_remaining: %d, and 20c amount is %d\n",
    // amount_remaining, twenty_cents);
  }
  if (amount_remaining / 10 >= 1) {
    ten_cents = amount_remaining / 10;
    amount_remaining = amount_remaining % 10;
    // printf("Current amount_remaining: %d, and 10c amount is %d\n",
    // amount_remaining, ten_cents);
  }
  if (amount_remaining / 5 >= 1) {
    five_cents = amount_remaining / 5;
    amount_remaining = amount_remaining % 5;
    // printf("Current amount_remaining: %d, and 5c amount is %d\n",
    // amount_remaining, five_cents);
  }
  if (amount_remaining / 2 >= 1) {
    two_cents = amount_remaining / 2;
    amount_remaining = amount_remaining % 2;
    // printf("Current amount_remaining: %d, and 2c amount is %d\n",
    // amount_remaining, two_cents);
  }
  if (amount_remaining / 1 >= 1) {
    one_cent = amount_remaining / 1;
    amount_remaining = amount_remaining % 1;
    // printf("Current amount_remaining: %d, and 1c amount is %d\n",
    // amount_remaining, one_cent);
  }

  printf("The coins required to make %d cents are:\n", user_input);
  while (fifty_cents != 0) {
    printf("give a 50c coin\n");
    fifty_cents--;
  }

  while (twenty_cents != 0) {
    printf("give a 20c coin\n");
    twenty_cents--;
  }

  while (ten_cents != 0) {
    printf("give a 10c coin\n");
    ten_cents--;
  }

  while (five_cents != 0) {
    printf("give a  5c coin\n");
    five_cents--;
  }

  while (two_cents != 0) {
    printf("give a  2c coin\n");
    two_cents--;
  }

  while (one_cent != 0) {
    printf("give a  1c coin\n");
    one_cent--;
  }

  printf("amount remaining: %dc\n", amount_remaining);
} */
// 07
// #include <stdio.h>
// #include <stdlib.h>
//
// int main() {
//   char identifier;
//   double user_input;
//   double ans;
//   printf("Enter a quantity: ");
//   scanf("%lf%c", &user_input, &identifier);
//
//   if (identifier == 'F') {
//     ans = (double)(user_input - 32.00) * (5. / 9);
//     printf("The temperature %.1lfF converts to %.1lfC\n", user_input, ans);
//   } else if (identifier == 'C') {
//     ans = user_input * 9 / 5 + 32;
//     printf("The temperature %.1lfC converts to %.1lfF\n", user_input, ans);
//   } else if (identifier == 'M') {
//     ans = user_input * 1.609;
//     printf("The distance %.1lf miles converts to %.1lf kilometers\n",
//            user_input, ans);
//   } else if (identifier == 'K') {
//     ans = user_input / 1.609;
//     printf("The distance %.1lf kilometers converts to %.1lf miles\n",
//            user_input, ans);
//   } else if (identifier == 'P') {
//     ans = user_input * 0.454;
//     printf("The mass %.1lf pounds converts to %.1lf kilograms\n",
//            user_input, ans);
//   } else if (identifier == 'G') {
//     ans = user_input / 0.454;
//     printf("The mass %.1lf kilograms converts to %.1lf pounds\n",
//            user_input, ans);
//   } else {
//     printf("Wrong input");
//     exit(EXIT_FAILURE);
//   }
// }
// 08
/* Calculate Australian tax and Medicare levy, 2012 scales.
 * Figure 3.5, PPSAA page 37. Alistair Moffat, December 2012
 */
#include <stdio.h>
#include <stdlib.h>

#define RATE0 0.000
#define RATE1 0.190
#define RATE2 0.325
#define RATE3 0.370
#define RATE4 0.450
#define RATE5 0.475
#define RATEM 0.015
#define RATEM2 0.025

#define THRESH1 18200.00
#define THRESH2 37000.00
#define THRESH3 80000.00
#define THRESH4 180000.00
#define THRESH5 250000.00
#define THRESH6 100000.00

#define BASE0 0.00
#define BASE1 (BASE0 + RATE0 * THRESH1)
#define BASE2 (BASE1 + RATE1 * (THRESH2 - THRESH1))
#define BASE3 (BASE2 + RATE2 * (THRESH3 - THRESH2))
#define BASE4 (BASE3 + RATE3 * (THRESH4 - THRESH3))

int main(int argc, char *argv[]) {
  double gross, tax, medicare, net;
  printf("Enter gross salary: $");
  if (scanf("%lf", &gross) != 1) {
    printf("No value was entered\n");
    exit(EXIT_FAILURE);
  }
  if (gross <= THRESH1) {
    tax = BASE0 + gross * RATE0;
  } else if (gross <= THRESH2) {
    tax = BASE1 + (gross - THRESH1) * RATE1;
  } else if (gross <= THRESH3) {
    tax = BASE2 + (gross - THRESH2) * RATE2;
  } else if (gross <= THRESH4) {
    tax = BASE3 + (gross - THRESH3) * RATE3;
  } else {
    if (gross <= THRESH5)
      tax = BASE4 + (gross - THRESH4) * RATE4;
    else
      tax = BASE4 + (THRESH5 - THRESH4) * RATE4 +
            (gross - THRESH5) * RATE5;
  }

  if (gross > THRESH6) {
    medicare = RATEM2 * gross;
  } else {
    medicare = RATEM * gross;
  }
  net = gross - tax - medicare;
  printf("gross income       $%9.2f\n", gross);
  printf("less tax           $%9.2f\n", -tax);
  printf("less medicare      $%9.2f\n", -medicare);
  printf("net income         $%9.2f\n", net);
  return 0;
}

/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */
