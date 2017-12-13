#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char s[10000];
  char ch;
  scanf("%s\n", s);
  scanf("%c", &ch);
  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    if (s[i] != ch) {
      printf("%c", s[i]);
    }
  }
  printf("\n");
  return 0;
}
