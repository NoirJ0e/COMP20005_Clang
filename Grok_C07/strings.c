// /* Exercise 7.12: Determine if a string is a palindrome
//  * Scaffold by Alistair Moffat, October 2013.
//  * (c) University of Melbourne */
//
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// #define MAXSTR 100
//
// /* function prototypes */
//
// int is_palindrome(char s[]);
// int read_line(char str[], int max);
//
// /* scaffolding to test the required function */
// int main(int argc, char *argv[]) {
//   char str[MAXSTR];
//   printf("Enter strings, one per line:\n");
//   while (read_line(str, MAXSTR) == 1) {
//     printf("The string \"%s\" is ", str);
//     if (!is_palindrome(str)) {
//       printf("**not** ");
//     }
//     printf("a palindrome\n");
//   }
//   return 0;
// }
//
// // TODO: implement is_palindrome
//
// int is_palindrome(char *str) {
//   int strlenghth = strlen(str);
//
//   for (int i = 0; i < strlenghth; i++) {
//     if (str[i] == str[strlenghth - i - 1]) {
//       return 1;
//     } else {
//       return 0;
//     }
//   }
//
//   return 0;
// }
//
// /* *** Helper functions *** */
//
// /* read one line of input into a string of maximum length.
//  * returns 1 if there still is text to be read (no EOF sent), 0 otherwise */
// int read_line(char str[], int max) {
//   int n = 0, c;
//   while ((c = getchar()) != EOF && c != '\n') {
//     str[n++] = c;
//     if (n == max - 1) {
//       str[n++] = '\0';
//       return 1;
//     }
//   }
//   if (c == EOF && n == 0) {
//     return 0;
//   }
//   str[n++] = '\0';
//   return 1;
// }
//
// /* Exercise 7.13: Implement your own strlen
//    Scaffold by Liam Saliba, September 2021,
//    based on Alistair Moffat, October 2013.
// */

// #include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>
//
// #define MAXSTR 10000
//
// /* function prototypes */
//
// int my_strlen(char str[]);
// int read_text(char str[], int max);
//
// /* scaffolding to test the required function */
// int
// main(int argc, char *argv[]) {
//     char str[MAXSTR];
//     printf("Enter text, press CTRL-D (EOF) to finish:\n");
//     read_text(str, MAXSTR);
//     printf("Length of string is %d\n", my_strlen(str));
// }
//
// /* determines the length of a string (null terminated) */
// int
// my_strlen(char str[]) {
// 	// TODO: Implement this function; do not use strlen
//   int count = 0;
//   while (str[count] != '\0') {
//     count++;
//   }
//   return count;
// }
//
//
// /* read one input into a string */
// int
// read_text(char str[], int max) {
// 	int n = 0, c;
// 	while (n < max - 1 && (c = getchar()) != EOF) {
// 		str[n++] = c;
// 	}
// 	if (c == EOF && n == 0) {
// 		return 0; // nothing read in
// 	}
// 	str[n++] = '\0';
// 	return 1;
// }

/* Exercise 7.14: Read a string, then convert to an integer
 * Scaffold by Alistair Moffat, October 2013.
 * (c) University of Melbourne */

// #include <ctype.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// #define MAXSTR 100
//
// /* function prototypes */
//
// int my_atoi(char str[]);
// int read_line(char str[], int max);
//
// /* scaffolding to test the required function */
// int main(int argc, char *argv[]) {
//   char str[MAXSTR];
//   printf("Enter an integer, then return: ");
//   while (read_line(str, MAXSTR) == 1) {
//     printf("The string \"%s\" ", str);
//     int n = my_atoi(str);
//     printf(" corresponds to integer %d\n", n);
//   }
// }
//
// /* converts a string to an integer
//  */
// int my_atoi(char str[]) {
//   // TODO: Implement this function all ignore leading or ending whitespace
//   int num = 0;
//   int sign = 1;
//   char *p = str;
//
//   // Skip leading white space
//   while (isspace(*p)) {
//     p++;
//   }
//
//   // Check for optional sign
//   if (*p == '-') {
//     sign = -1;
//     p++;
//   } else if (*p == '+') {
//     p++;
//   }
//
//   // Process digits
//   while (isdigit(*p)) {
//     num = num * 10 + (*p - '0');
//     p++;
//   }
//
//   return sign * num;
// }
//
// /* read one line of input into a string of maximum length.  (ex7-12 soln.)
//  * returns 1 if there still is text to be read (no EOF sent), 0 otherwise */
// int read_line(char str[], int max) {
//   int n = 0, c;
//   while ((c = getchar()) != EOF && c != '\n') {
//     str[n++] = c;
//     if (n == max - 1) {
//       str[n++] = '\0';
//       return 1;
//     }
//   }
//   if (c == EOF && n == 0) {
//     return 0;
//   }
//   str[n++] = '\0';
//   return 1;
// }

/* Exercise 7.15: Determine if two strings are anagrams
 * Scaffold by Alistair Moffat, October 2013.
 * (c) University of Melbourne */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 100

/* function prototypes */

int is_anagram(char s1[], char s2[]);
int read_line(char str[], int max);

/* scaffolding to test the required function */
int
main(int argc, char *argv[]) {
    char s1[MAXSTR], s2[MAXSTR];
    printf("Enter two strings, one string per line:\n");
    while ((read_line(s1, MAXSTR) == 1) && (read_line(s2, MAXSTR) == 1)) {
        printf("The strings \"%s\" and \"%s\" are ", s1, s2);
        if (!is_anagram(s1, s2)) {
            printf("**not** ");
        }
        printf("anagrams\n");
    }
    return 0;
}

/* returns 1 if s1 and s2 are anagrams: strings with the same character
 * frequencies, in linear time and constant space */
#include <ctype.h>
int
is_anagram(char s1[], char s2[]) {
    // TODO: Implement this function.
  int s1total = atoi(s1), s2total = atoi(s2);
  if (s1total != s2total) {
    return 0;
  }
  int freq1[26], freq2[26], s1len = strlen(s1), s2len = strlen(s2);
  for (int i = 0; i < 26; i++) {
    freq1[i] = 0;
    freq2[i] = 0;
  }
  for (int i = 0; i < s1len; i++) {
    s1[i] = tolower(s1[i]);
  }
  for (int i = 0; i < s2len; i++) {
    s2[i] = tolower(s2[i]);
  }
  for (int i = 0; i < s1len; i++) {
    freq1[s1[i] - 'a']++;
  }
  for (int i = 0; i < s2len; i++) {
    freq2[s2[i] - 'a']++;
  }
  for (int i = 0; i < 26; i++) {
    if (freq1[i] != freq2[i]) {
      return 0;
    }
  }

  return 1;
}


/* read one line of input into a string of maximum length.
 * returns 1 if there still is text to be read (no EOF sent), 0 otherwise */
int
read_line(char str[], int max) {
    int n = 0, c;
    while ((c = getchar()) != EOF && c != '\n') {
        str[n++] = c;
        if (n == max - 1) {
            str[n++] = '\0';
            return 1;
        }
    }
    if (c == EOF && n == 0) {
        return 0;
    }
    str[n++] = '\0';
    return 1;
}

