// 03
// #include <stdio.h>
// #include <stdlib.h>
//
// int fibonacci(int n) {
//   if (n == 0) {
//     return 0;
//   } else if (n == 1) {
//     return 1;
//   } else {
//     return fibonacci(n - 1) + fibonacci(n - 2);
//   }
// }
//
// int main() {
//   //fibonacci
//   // Write a program that prints out the number of spores present at the end
//   of each day, stopping when the number of spores exceeds ten million. int
//   days = 0; int spores = 2; while (spores < 10000000) {
//       days++;
//     if (days < 3) {
//     } else {
//       spores = fibonacci(days);
//       printf("After %d days, %d spores\n", days, spores);
//     }
//   }
// }

// 05
// #include <stdio.h>
//
// int main() {
//     int i, j;
//
//     printf("           +0  +1  +2  +3  +4  +5  +6  +7\n");
//     printf("        +--------------------------------\n");
//     for (i = 32; i <= 126; i += 8) {
//         printf("%7d |", i);
//         for (j = 0; j < 8; j++) {
//             int c = i + j;
//             if (c <= 126) {
//                 printf("%4c", c);
//             }
//         }
//         printf("\n");
//     }
//
//     return 0;
// }
//

// 06
// #include <stdio.h>
// #include <stdlib.h>
//
// int main() {
//   int max = 70, input;
//   printf("Enter numbers: ");
//
//   int arr_index = 0;
//   //create a dynamic array
  // int *arr = malloc(sizeof(int) * 1);
//   if (arr == NULL) {
//     printf("Error: malloc failed\n");
//     exit(1);
//   }
//   //add the inputs to the array
//   while (scanf("%d", &input) == 1) {
//     if (input > max) {
//       printf("Invalid input\n");
//       exit(1);
//     }
//     arr[arr_index] = input;
//     arr_index++;
//   }
//
//   //print the result
//   for (int i = 0; i < arr_index; i++) {
//     printf("%2d |", arr[i]); // print the numbers
//     for (int j = 0; j < arr[i]; j++) {
//       printf("*");
//       // when the stars is the same as arr[i], print a new line
//       if (j == arr[i] - 1) {
//         printf("\n");
//       }
//     }
//   }
//
//   free(arr); // free the memory
// }
//
// 07
// #include <stdio.h>
//
// int main() {
//   int input;
//   printf("Enter numbers: ");
//   while (scanf("%d", &input) == 1) {
//     printf("%2d |", input);
//     for (int i = 0; i < input; i++){
//       printf("*");
//     }
//     printf("\n");
//   }
// }
// 08
// #include <stdio.h>
//
// int main(int argc, char *argv[]) {
// 	int ch, char_number = 0, line_number = 0;
//   printf("Enter text:\n");
// 	while ((ch = getchar()) != EOF) {
// 		if (ch != '\n') {
// 			char_number++;
// 		}
// 		if (ch == '\n') {
//       char_number++;
// 			line_number++;
// 		}
//   }
//
//   printf("Lines:%7d\n",line_number);
//   printf("Chars:%7d\n",char_number);
// 	return 0;
// }
// 09
// #include <stdio.h>
//
// int main(int argc, char *argv[]) {
//   int ch, char_number = 0, line_number = 0;
//   /*    words are set of characters that ending with space/,/;/\n */
//   int word_number = 0;
//   int is_word = 0;
//
//   printf("Enter text:\n");
//   while ((ch = getchar()) != EOF) {
//     if ((ch == ' ') || (ch == ',') || (ch == ';')) {
//       is_word = 1;
//     }
//     if (is_word && ch != ' ') {
//       word_number++;
//       is_word = 0;
//     }
//     if (ch != '\n') {
//       char_number++;
//     } else if (ch == '\n') {
//       char_number++;
//       line_number++;
//     }
//   }
//
//   printf("Lines:%7d\n", line_number);
//   printf("Words:%7d\n", word_number);
//   printf("Chars:%7d\n", char_number);
//   return 0;
// }
//

// 07
// #include <stdio.h>
//
// int main(int argc, char const *argv[]) {
//   int ch, char_count = 0, line_count = 0;
//   int is_word = 0;
//   int word_count = 0;
//
//   printf("Enter text:");
//
//   while ((ch = getchar()) != EOF) {
//     if ((97 <= ch && ch <= 122) || (65 <= ch && ch <= 90)) {
//       if (is_word == 0) {
//         word_count++;
//       }
//       is_word = 1;
//     } else {
//       is_word = 0;
//     }
//     if (ch != '\n') {
//       char_count++;
//     } else if (ch == '\n') {
//       line_count++;
//       char_count++;
//     }
//   }
//
//   printf("\nLines:%7d\n", line_count);
//   printf("Words:%7d\n", word_count);
//   printf("Chars:%7d\n", char_count);
//   return 0;
// }
//
// 08
// #include <stdio.h>
// #include <stdlib.h>
//
// int main(int argc, char *argv[]) {
//   int nmax; // TODO what is this?
//   int max_value = 0, max_cycle = 0, start_from;
//
//   printf("Enter value for nmax: ");
//   if ((scanf("%d", &nmax) != 1)) {
//     printf("Wrong input\n");
//     exit(EXIT_FAILURE);
//   }
//   if (nmax == 1) {
//     printf("start = %7d, cycles = %5d, max = %10d\n", start_from = 1,
//     max_cycle = 0,
//          max_value = 1);
//     exit(0);
//   }
//
//   for (int n_start = 1; n_start <= nmax; n_start++) {
//     int n = n_start;
//     int cycle_count = 0;
//     int temp_max_value = 0;
//     while (n > 1) {
//       if (n % 2 == 0) {
//         n = n / 2;
//       } else {
//         n = n * 3 + 1;
//       }
//       if (n > temp_max_value) {
//         temp_max_value = n;
//       }
//       cycle_count++;
//       if (cycle_count > max_cycle) {
//         max_cycle = cycle_count;
//         start_from = n_start;
//         max_value = temp_max_value;
//       }
//     }
//   }
//
//   printf("start = %7d, cycles = %5d, max = %10d\n", start_from, max_cycle,
//          max_value);
// }
//
// 09
// #include <stdio.h>
// #include <stdbool.h>
//
// bool is_prime(int i) {
//   if (i <= 1) {
//     return false;
//   }
//   for (int j = 2; j * j <= i; j++) {
//     if (i % j == 0) {
//       return false;
//     }
//   }
//   return true;
// }
//
// int next_prime(int i) {
//   int next_prime = i + 1;
//   while (!is_prime(next_prime)) {
//     next_prime++;
//   }
//   return next_prime;
// }
//
// int main() {
//   int input;
//   printf("Enter an integer value: ");
//   scanf("%d", &input);
//   printf("The next prime is     : %d\n", next_prime(input));
// }

// 10/11
// convert C99 standard comment to ANSI C standard


// 12 calculate sum of prime number
/* #include <stdbool.h>
#include <stdio.h>

bool is_prime(int i) {
  if (i <= 1) {
    return false;
  }
  for (int j = 2; j * j <= i; j++) {
    if (i % j == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int max;
  while (scanf("%d", &max) == 1) {
    int prime_sum = 0;
    for (int i = 0; i <= max; i++) {
      if (is_prime(i)) {
        prime_sum += i;
      }
    }
    if (is_prime(prime_sum)) {
      printf("Sum of primes <= %d is %d, which is prime\n",max,prime_sum);
    } else {
      printf("Sum of primes <= %d is %d, which is not prime\n",max,prime_sum);
    }
  }
} */

// 13 calculate $log_2{x}$
/* #include <stdio.h>
#include <stdlib.h>
#include <math.h>

int powers(int i) {
  for (double x = 0.0; x < i; x++) {
    if ((pow(2.0,x)) >= i) {
      return x;
    }
  }
  return 0;
}

int main() {
  printf("Enter a number: ");
  double input;
  if (scanf("%2lf", &input) != 1) {
    printf("Wrong input");
    exit(1);
  }

  printf("ceil log2(%.2lf) = %d\n", input,powers(input));
} */
