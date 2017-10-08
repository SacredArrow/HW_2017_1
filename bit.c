#include <stdio.h>

int bitAnd(int x, int y) { return ~(~x | ~y); }

int bitXor(int x, int y) {
  int x1 = ~(x & y);
  int y1 = ~(~x & ~y);
  return x1 & y1;
}

int thirdBits(void) {
  int x = 0;
  x = x | 36;
  x = x << 8;
  x = x | 146;
  x = x << 8;
  x = x | 73;
  x = x << 8;
  x = x | 36;
  return x;
}

int fitsBits(int x, int n) {
  int max = (1 << n - 1) - 1;
  int min = ~max;
  printf("%d\n", max);
  printf("%d\n", min);
  int x1 = (max - x + 1) >> 31;
  printf("%d\n", x1);
  int x2 = (x - min + 1) >> 31;
  printf("%d\n", x2);
  return (!x1 & !x2);
}

int sign(int x) {
  int inverted = ~x + 1;
  inverted = (inverted >> 31);
  x = x >> 31;
  x = x & 1;
  int temp = x & inverted;
  x = x + inverted + temp;
  x = x ^ (~0);
  x += 1;
  return x;
}

int getByte(int x, int n) {
  int one = 255;
  x = x >> (n * 8);
  return x & one;
}

int logicalShift(int x, int n) {
  x = x >> n;
  x = x & (~(((1 << 31) >> n) << 1));
  return x;
}

int addOK(int x, int y) {
  int sum = x + y;
  int sub1 = sum - x;
  int sub2 = sum - y;
  return !(sub1 >> 31) & !(sub2 >> 31);
}

int bang(int x) {
  int inverted = ~(x) + 1;
  int goal = inverted | x;
  goal = goal >> 31;
  return (~goal + 1) ^ 1;
}

int conditional(int x, int y, int z) {
  int inverted = ~(x) + 1;
  int goal = inverted | x;
  goal = goal >> 31;
  goal = (~goal + 1);
  int y1 = goal;
  int x1 = goal ^ 1;
  int y_con = ((((y1) << 31) >> 31) & y);
  int x_con = ((((x1) << 31) >> 31) & z);

  return (y_con + x_con);
}

int isPower2(int x) { return (!(x & (x - 1))) & !!x & !(x >> 31); }

int main(int argc, char const *argv[]) {
  // for (int i = -200; i <= 100; i++)
  printf("%d\n", fitsBits(1 << 31, 32));
  return 0;
}

// x y x^y   x y x&y ~(x&y) x|y
// 0 0 0     0 0 0    1     0
// 1 0 1     1 0 0    1     1
// 0 1 1     0 1 0    1     1
// 1 1 0     1 1 1    0     1
