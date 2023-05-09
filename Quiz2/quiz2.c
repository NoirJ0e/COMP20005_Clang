#include <stdio.h>
#include <stdlib.h>

int two_or_more(int A[], int n, int B[]) {
  int count = 0; 
  for (int i = 0; i < n; i++) {
    // dup = duplicate
    int found = 0, dup = 0;

    // as long as it has a duplicate, it already sastisfies the condition
    // exit this loop immediately
    for (int j = 0; j < i; j++) {
      if (A[i] == A[j]) {
        dup = 1;
        break;
      }
    }

    // if it doesn't have a duplicate with previous value in this array, 
    // check if there is another same value in the rest of the array
    // if so, break immediately
    if (!dup) {
      for (int j = i + 1; j < n; j++) {
        if (A[i] == A[j]) {
          found = 1;
          break;
        }
      }
    }

    if (found) {
      B[count++] = A[i];
    }
  }
  return count;
}

int main() {
  int A[] = {1,7,6,7,4,1,4,4,3};
  int B[20];
  int C[20];
  printf("%d\n",two_or_more(A,5,B));
  for (int i = 0; i < 5; i++) {
    printf("%d ", B[i]);
  }
  printf("%d\n",two_or_more(A,9,C));
  for (int i = 0; i < 5; i++) {
    printf("%d ", C[i]);
  }
}
