#include <stdio.h>
#include <stdlib.h>

int is_subset(int A[], int B[], int nA, int nB);

int is_subset(int A[], int B[], int nA, int nB) {
  int res = 0;

  for (int i = 0; i < nA; i++) {
    // initialize res to 0 for each loop to avoid false positives
    res = 0;
    for (int j = 0; j < nB; j++) {
      // if found a match, break immediately and set res to 1
      if (A[i] == B[j]) {
        res = 1;
        break;
      }
    }

    // if not found a match, than A is not a subset of B and exit immediately
    if (!res) {
      return 0;
    }
  }

  return res;
}

int main() {
  /* int A[] = {3,4,3,8,5};
  int B[] = {3,8,4,9,6,7};
  printf("%d\n", is_subset(A, B, 4, 4));
  printf("%d\n", is_subset(A, B, 5, 6)); */
  int n = 44;
  char c = 'a';
  double z = 2.5;
  int *pn = &n;
  char *pc = &c;
  double *pz = &z;
  *pc = n+1;
  printf("%c\n", *pc);
}
