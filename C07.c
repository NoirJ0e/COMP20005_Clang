/* array operations
 * Alistair Moffat, PPSAA, Chapter 7, December 2012
 * (c) University of Melbourne */
#include <stdio.h>
#define MAXVALS 1000
#include "arrayops.h"

/* ****
 * These functions are very slightly modified from insertionsort.c in Figure 7.4
 * Fig 7.4 on pg107 in PPSAA by Alistair Moffat, updating style and comments.
 * **** */

/* sorts n elements of array A in increasing order (2, 3, 4, 5)
 * using insertion sort (insertionsort.c, Figure 7.4 PPSAA) */
void
sort_int_array(int A[], int n) {
    /* assume that A[0] to A[n-1] have valid values */

    for (int i = 1; i < n; i++) {
        /* swap A[i] left into correct position (increasing order). */
        for (int j = i - 1; j >= 0 && A[j] > A[j + 1]; j--) {
            /* not there yet */
            int_swap(&A[j], &A[j + 1]);
        }
    }
}

/* exchange the values of the two variables indicated
 * by the arguments (insertionsort.c, Figure 7.4 PPSAA) */
void
int_swap(int *p1, int *p2) {
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

/* read integers from input and store them in an array.
 * maxvals is the maximum number of elements that can be read in to the array,
 * all other values are discarded
 * returns the number of elements successfully read in
 * (insertionsort.c, Figure 7.4 PPSAA) */
int
read_int_array(int A[], int maxvals) {
    int n = 0, excess = 0, next;

    printf("Enter as many as %d values, ^D to end\n", maxvals);
    while (scanf("%d", &next) == 1) {
        if (n == maxvals) {
            excess += 1;
        } else {
            A[n] = next;
            n += 1;
        }
    }

    printf("%d values read into array", n);
    if (excess) {
        printf(", %d excess values discarded", excess);
    }
    printf("\n");
    return n;
}

/* print the elements of an array on one line
 * (insertionsort.c, Figure 7.4 PPSAA) */
void
print_int_array(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf(" %3d", A[i]);
    }
    printf("\n");
}


int sort_reduce_int_array(int A[], int n) {
    // TODO: understand this function
  for (int i = 1; i < n; i++) {
    for (int j = i -1; j >= 0 && A[j] > A[j+1]; j--) {
      int_swap(&A[j], &A[j+1]);
    }
  } 
  // now the array has been sort in ascending order
  // we need to remove the duplicates
  // we can do this by using a for loop to compare the current element with the next elements
  for (int i = 0; i < n; i++) {
    if (A[i] == A[i+1]) {
      for (int j = i; j < n; j++) {
        A[j] = A[j+1];
      }
      n--;
      i--;
    }
  }

    return n;  // return the number of elements left in the array.
}



/* int array_frequency_count(int A[], int n) {
  // count the frequency of each element in the array 
  // read array elements 
  for (int i = 0; i < n; i++) {
    int count = 1;
    for (int j = i + 1; j < n; j++) {
      if (A[i] == A[j]) {
        count++;
        for (int k = j; k < n; k++) {
          A[k] = A[k+1];
        }
        n--;
        j--;
      }
    }
    printf("%4d    %3d\n", A[i], count);
  }
  return 0;
}

int main() {
  int A[MAXVALS], n;
  n = read_int_array(A, MAXVALS);
  sort_int_array(A, n);
  // find the length of the array
  // sort the input array
  // int n = sort_reduce_int_array(A, MAXVALS);
  printf("Value   Freq\n");
  array_frequency_count(A, n);
  // count thre frequency of elements appears in user input
  // array_frequency_count(A, 17);
  return 0;
} */

// Ex 7.05
// HACK: Better idea is to use a struct to store the studnum and mark

#include <stdio.h>
#include <stdlib.h>
#define MAXVALS 1000

int read_pair_array(int A[], int maxvals) {
    int n = 0, excess = 0, next;

    printf("Enter as many as %d \"studnum mark\" pairs, ^D to end\n", maxvals);
    while (scanf("%d", &next) == 1) {
        if (n == maxvals) {
            excess += 1;
        } else {
            A[n] = next;
            n += 1;
        }
    }

    printf("%d pairs read into array", n/2);
    if (excess) {
        printf(", %d excess values discarded", excess);
    }
    printf("\n");
    return n;
}

int main() {
  int sorted_studnum[MAXVALS],sorted_mark[MAXVALS], n;
  // as i dont actually use these array, i dont want to waste memory
  int* temp = malloc(sizeof(int) * MAXVALS);
  int* studnum = malloc(sizeof(int) * MAXVALS);
  int* mark = malloc(sizeof(int) * MAXVALS);

  n = read_pair_array(temp, MAXVALS);
  printf("studnum  mark\n");
  for (int i = 1; i < n; i+=2) {
    mark[i/2] = temp[i];
  }
  for (int i = 0; i < n; i+=2) {
    studnum[i/2] = temp[i];
  }
  // free memory
  free(temp);
  n = n/2; // update the actually length of these two arrays
  // copy the mark array to another array as index
  for (int i = 0; i < n; i++) {
    sorted_studnum[i] = studnum[i];
  }
  // sort the studnum array 
  for (int i = 1; i < n; i++) {
    for (int j = i - 1; j >= 0 && sorted_studnum[j] > sorted_studnum[j+1]; j--) {
      int_swap(&sorted_studnum[j], &sorted_studnum[j+1]);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (sorted_studnum[i] == studnum[j]) {
        sorted_mark[i] = mark[j];
      }
    }
  }
  // prevent memory leak
  free(studnum);
  free(mark);
  for (int i = 0; i < n; i++) {
    printf("%6d  %3d\n", sorted_studnum[i], sorted_mark[i]);
  }
  return 0;
}
