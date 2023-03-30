// find max value in four input
/* #include <stdio.h>
int max_4_ints(int a, int b, int c, int d) {
  int max = a;
  if (b > max) {
    max = b;
  }
  if (c > max) {
    max = c;
  }
  if (d > max) {
    max = d;
  }
  return max;
}


int main(int argc, char *argv[]) {
  printf("Enter four integers: ");
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  printf("max_4_ints(%d, %d, %d, %d) = %d\n", a, b, c, d, max_4_ints(a, b, c,
d));
} */
// find median in three input
/* #include <stdio.h>
int median_3_ints(int a, int b, int c) {
  int arr[3] = {a, b, c};
  int max = a,min = a,mid = 0;
  for (int i = 0; i < 3; i++) {
    if (arr[i] > max) {
      max = arr[i];
    } else if (arr[i] < min) {
      min = arr[i];
    }
  }
  mid = a + b + c - max - min;
  return mid;
}

int main() {
  printf("Enter three integers: ");
  int a, b, c;
  scanf("%d %d %d", &a, &b, &c);
  printf("median_3_ints(%d, %d, %d) = %d\n", a, b, c, median_3_ints(a, b, c));
} */
// find power of something
/* #include <stdio.h>
#include <stdlib.h>
int int_pow(int base, int exp) {
  int result = 1;
  for (int i = 0; i < exp; i++) {
    result *= base;
  }
  return result;
}

int main() {
  printf("Enter the base and the exponent: ");
  int base, exp;
  scanf("%d %d", &base, &exp);
  if (exp > 32 && base > 1) {
    printf("Error: Integer overflow when attempting multiplication\n");
    exit(1);
  }
  printf("%d^%d = %d\n", base, exp, int_pow(base, exp));
}
*/
// combinations
/* #include <stdio.h>
#include <stdlib.h>

long long int factorial(double n) {
  long long int result = 1;
  if (n < 170) {
    for (long long int i = 1; i <= n; i++) {
      result *= i;
    }
    return result;
  } else {
    n = n / 10000.0;
    for (double i = 0.0001; i <= n; i += 0.0001) {
      result *= i;
    }
    return result;
  }
}

int main() {
  printf("Enter n and k: ");
  double n, k;
  scanf("%lf %lf", &n, &k);
  if (n < 0 || k < 0) {
    printf("Error: n and r must be non-negative\n");
    exit(1);
  }
  if (n < k) {
    printf("Error: n must be greater than or equal to r\n");
    exit(1);
  }
  double result = factorial(n) / (factorial(k) * factorial(n - k));
  printf("%.0lf choose %.0lf = %.0lf\n", n, k, result);
} */

// find perfect number
/* #include <stdio.h>
#include <stdlib.h>
int is_perfect(int n) {
  int sum = 0;
  for (int i = 1; i < n; i++) {
    if (n % i == 0) {
      sum += i;
    }
  }
  if (sum == n) {
    return 1;
  } else {
    return 0;
  }
}
int main() {
  printf("Enter a number: ");
  int n;
  scanf("%d", &n);
  if (n < 0) {
    printf("Error: n must be non-negative\n");
    exit(1);
  }
  if (is_perfect(n)) {
    printf("%d is a perfect number\n", n);
  } else {
    printf("%d is not a perfect number\n", n);
  }
  int next = n + 1;
  while (!is_perfect(next)) {
    next++;
  }
  printf("The next perfect is %d\n",next);
} */

// find amicable pair
/* #include <stdio.h>
int amicalbe_pair(int n1, int n2) {
  // Two numbers are an amicable pair if their factors (excluding themselves)
  // add up to each other
  int sum1 = 0, sum2 = 0;
  for (int i = 1; i < n1; i++) {
    if (n1 % i == 0) {
      sum1 += i;
    }
  }
  for (int i = 1; i < n2; i++) {
    if (n2 % i == 0) {
      sum2 += i;
    }
  }
  if (sum1 == n2 && sum2 == n1) {
    // number whose sum of factors equals itself, so is not amicable
    if (sum1 == n1 || sum2 == n2) {
      return 0;
    }
    return 1;
  } else {
    return 0;
  }
}

int main() {
  printf("Enter two integers: ");
  int a, b;
  scanf("%d %d", &a, &b);
  if (amicalbe_pair(a, b)) {
    printf("%d and %d are an amicable pair\n", a, b);
  } else {
    printf("%d and %d are not an amicable pair\n", a, b);
  }
} */

/* #include <stdio.h>
#include <stdlib.h>

int amicalbe_pair(int n1, int n2) {
  // Two numbers are an amicable pair if their factors (excluding themselves)
  // add up to each other
  int sum1 = 0, sum2 = 0;
  for (int i = 1; i < n1; i++) {
    if (n1 % i == 0) {
      sum1 += i;
    }
  }
  for (int i = 1; i < n2; i++) {
    if (n2 % i == 0) {
      sum2 += i;
    }
  }
  if (sum1 == n2 && sum2 == n1) {
    // number whose sum of factors equals itself, so is not amicable
    if (sum1 == n1 || sum2 == n2) {
      return 0;
    }
    return 1;
  } else {
    return 0;
  }
}

int main() {
  int input;
  if ((scanf("%d", &input)) != 1) {
    printf("Error: invalid input\n");
    exit(1);
  }

  while ((int n = input) != 1) {

  }

} */

// issuper() and tolower()
/* #include <stdio.h>
#include <stdlib.h>

int my_isupper(int n) {
  if (65 <= n && n <= 90) {
    return 1;
  }
  return 0;
}

int my_tolower(int n) {
  return n + 32;
}

int main() {
  printf("Enter text, ^D to end:\n");
  char input = getchar();
  while (input != EOF) {
    if (my_isupper(input)) {
      putchar(my_tolower(input));
    } else {
      putchar(input);
    }
    input = getchar();
  }
} */

// near-equality for doubles
/* #include <stdio.h>
#include <stdlib.h>

int near_equal(double x1, double x2) {
  double diff = x1 - x2;
  if (diff < 0) {
    diff = -diff;
  }
  if (diff == 0.0) {
    return 1;
  } else if ((diff/x1) < 0.0001 && (diff/x2) < 0.0001) {
    return 1;
  }
  return 0;
}

int main() {
  double x1,x2;
  printf("Enter two numbers: ");
  if (scanf("%lf %lf", &x1, &x2) != 2) {
    printf("Error: invalid input\n");
    exit(1);
  }
  if (near_equal(x1, x2)) {
    printf("Deemed near equal\n");
  } else {
    printf("Deemed different\n");
  }
}
*/

// Sum a real-valued sequence

/* #include <stdio.h>
#include <stdlib.h>

double factorial(int n) {
  double result = 1;
  for (int i = 1; i <= n; i++) {
    result = result * i;
  }
  return result;
}




double sum_of_n(int n) {
  int result = n;
  while (n > 0) {
    result += n-1;
    n--;
  }
  return result;
}

double sum_sequence(int n) {
  double result = 0;
  int loop_count = 1;
  while (loop_count <= n) {
    result += sum_of_n(loop_count)/factorial(loop_count);
    loop_count++;
  }
  return result;
}

int main() {
  int input;
  printf("Enter n: ");
  scanf("%d", &input);
  printf("%d gives sequence sum of %.10lf\n", input, sum_sequence(input));
} */

// Integer power with recursion

/* #include <stdio.h>
int power_of_n(int base, int exponent) {
  if (exponent == 0) {
    return 1;
  } else {
    return base * power_of_n(base, exponent - 1);
  }
}

int main() {
  int base, exponent;
  printf("Enter the base and the exponent: ");
  scanf("%d %d",&base, &exponent);
  printf("%d^%d = %d\n",base,exponent,power_of_n(base,exponent));
} */

// longstar, recursively
/* #include <stdio.h>
#include <math.h>
int longstar(double n) {
  if (n < 1 ) {
    return 0;
  } else {
    return 1 + longstar(log2(n));
  }
}
int main() {
  double n;
  printf("Enter a number: ");
  scanf("%lf", &n);
  if (n <= 0) {
    printf("Error: Invalid input\n");
    return 1;
  }
  printf("log base 2 of %.1lf is %.3lf\n",n,log2(n));
  printf("logstar    of %.1lf is %d\n",n,longstar(n));
} */

