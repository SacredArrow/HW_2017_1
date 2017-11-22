#include <math.h>
#include <stdio.h>
#include <string.h>

union {
  float fl;
  int dw;
} f;

union {
  float fl;
  struct Number {
    unsigned int mant : 23;
    unsigned int exp : 8;
    unsigned int sign : 1;
  } number;
} f1;

struct Method {
  char *descr;
  void (*functionPtr)(float);
};

struct Answer {
  int s;
  int e;
  float sum;
} answer;

float bin_to_dec(int m) {
  float sum = 1;
  float two = 1;
  for (int i = 1; i <= 23; i++) {
    int curr = m & (1 << 22);
    curr = (curr >> 22) & 1;
    m = m << 1;
    two = two / 2;
    sum += two * curr;
  }
  return sum;
}

void union_bit(float x) {
  f.fl = x;
  int s = (f.dw >> 31) ? 1 : 0; /* Знак */
  int e = (f.dw >> 23) & 0xFF;  /* Порядок */
  int m =                       /* Мантисса */
      e ? (f.dw & 0x7FFFFF) | 0x800000 : (f.dw & 0x7FFFFF) << 1;
  e = e - 127;
  float sum = bin_to_dec(m);
  answer.s = s;
  answer.e = e;
  answer.sum = sum;
}

void union_fields(float x) {
  f1.fl = x;
  answer.s = f1.number.sign;
  answer.e = f1.number.exp - 127;
  answer.sum = bin_to_dec(f1.number.mant);
}

void ptr(float x) {
  float *pointer = &x;
  int f = *(int *)pointer;
  int s = (f >> 31) ? 1 : 0; /* Знак */
  int e = (f >> 23) & 0xFF;  /* Порядок */
  int m =                    /* Мантисса */
      e ? (f & 0x7FFFFF) | 0x800000 : (f & 0x7FFFFF) << 1;
  e = e - 127;
  float sum = bin_to_dec(m);
  answer.s = s;
  answer.e = e;
  answer.sum = sum;
}

void beatufier(int s, int e, float sum) {
  printf("    %d  %d\n", s, e);
  printf("(-1) * 2 * ");
  printf("%g\n", sum);
}

int main(int argc, char const *argv[]) {
  f.fl = 0.15625;
  struct Method methods[] = {
      {.descr = "1 - Union with bit operations", .functionPtr = union_bit},
      {.descr = "2 - Union with bit fields", .functionPtr = union_fields},
      {.descr = "3 - Pointer and bit operations", .functionPtr = ptr}};
  for (int i = 0; i < 3; i++) {
    printf("%s\n", methods[i].descr);
  }
  int number;
  float a, b;
  printf("Please, choose a method:");
  scanf("%d", &number);
  if (number >= 1 && number <= sizeof(methods) / sizeof(methods[0])) {
    printf("Please, enter 2 values:");
    scanf("%f %f", &a, &b);
    float goal = a / b;
    if (isnan(goal) || isinf(goal)) {
      printf("%f\n", goal);
      return 0;
    }
    methods[number - 1].functionPtr(goal);
  } else {
    printf("You entered unacceptable value!\n");
    return 0;
  }

  beatufier(answer.s, answer.e, answer.sum);
  // printf("%d %d %d\n", s, e, m);
  // printf("%f\n", s * m * pow(2, -23) * pow(2, e - 127));
  return 0;
}
