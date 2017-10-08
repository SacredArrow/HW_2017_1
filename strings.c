#include <stdio.h>
int strlen(char *str) {
  char i = str[0];
  int cnt = 0;

  while (i != 0) {
    cnt++;
    i = str[cnt];
  }
  return cnt;
}

void strcpy(char *dst, char *src) {
  int i = 0;

  while (1) {
    dst[i] = src[i];
    if (dst[i] == 0) {
      break;
    }
    i++;
  }
}

void ctrcat(char *dst, char *src) {
  int i, j;

  for (i = 0; dst[i] != 0; i++)
    ;
  for (j = 0; src[j] != 0; j++) {
    dst[i + j] = src[j];
  }
  dst[i + j] = 0;
}

int strcmp(char *s1, char *s2) {
  if (strlen(s1) < strlen(s2)) {
    return -1;
  } else if (strlen(s1) > strlen(s2)) {
    return 1;
  }
  for (int i = 0; i < strlen(s1); i++) {
    if (s1[i] - s2[i] != 0) {
      return s1[i] - s2[i];
    }
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  char a[9] = "abcd";
  char b[5] = "abcd";

  printf("%d\n", strcmp(a, b));
  return 0;
}
