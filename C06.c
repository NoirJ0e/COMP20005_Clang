/* Read an array, sort it, write it out again.
 * Figure 7.3 PPSAA, insertionsort.c - Alistair Moffat
*/
#include <stdio.h>
#include "arrayops.h"

#define MAXVALS 1000

/* function prototypes */
void sort_int_array_decreasing(int A[], int n);
// functions read_int_array, print_int_array and int_swap are in arrayops.h

int
main(int argc, char *argv[]) {
	int numbers[MAXVALS], nnumbs;
	nnumbs = read_int_array(numbers, MAXVALS);
    
	printf("Before: ");
	print_int_array(numbers, nnumbs);
	sort_int_array_decreasing(numbers, nnumbs);
    
	printf("After : ");
	print_int_array(numbers, nnumbs);
    
	return 0;
}

void
sort_int_array_decreasing(int A[], int n) {
    /* assume that A[0] to A[n-1] have valid values */

    for (int i = 1; i < n; i++) {
        /* swap A[i] left into correct position (increasing order). */
        for (int j = i - 1; j >= 0 && A[j] > A[j + 1]; j--) {
            /* not there yet */
            int_swap(&A[j], &A[j + 1]);
        }
    }
}
