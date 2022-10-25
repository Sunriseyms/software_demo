#include <stdio.h>
#include "a.h"

int main() {
  int i = 2;
  int j = 5;

  int result = test::add(i, j);

  printf("result=%d\n", result);

  return 2;
}
