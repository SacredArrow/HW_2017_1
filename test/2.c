#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char s1[10000];
  char s2[10000];
  scanf("%s\n", s1);
  scanf("%s", s2);
  int x = strlen(s1);
  int y = strlen(s2);
  if (x != y) {
    if (x > y) {
      printf("First > second\n");
      return 0;
    } else {
      printf("Second > first\n");
      return 0;
    }
  }
  for (int i = 0; i < x; i++) {
    if (s1[i] == s2[i])
      continue;
    else {
      if (s1[i] > s2[i]) {
        printf("First > second\n");
        return 0;
      } else {
        printf("Second > first\n");
        return 0;
      }
    }
  }
  printf("They are similar!\n");
  return 0;
}
