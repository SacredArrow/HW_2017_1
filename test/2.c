#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char s1_1[256];
  char s2_1[256];
  scanf("%s\n", s1_1);
  scanf("%s", s2_1);
  int x = strlen(s1_1);
  int y = strlen(s2_1);
  unsigned int s1[256];
  unsigned int s2[256];
  for (int i = 0; i < 256; i++) {
    s1[i] = 0;
    s2[i] = 0;
  }
  for (int i = 0; i < x; i++)
    s1[i] = (int)s1_1[i];
  for (int i = 0; i < y; i++)
    s2[i] = (int)s2_1[i];
  for (int i = 0; i < 256; i++) {
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
