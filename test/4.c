#include <stdio.h>

int main(int argc, char const *argv[]) {
  int sum = 0;
  int sum_of_squares = 0;
  for (int i = 1; i <= 100; i++) {
    sum += i;
    sum_of_squares += i * i;
  }
  sum = sum * sum;
  printf("%d\n", sum - sum_of_squares);
  return 0;
}
