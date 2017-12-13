#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  FILE *file = fopen("example", "r");
  while (!feof(file)) {
    char s[256];
    fgets(s, 256, file);
    char *x = strstr(s, "//");
    if (x) {
      printf("%s", x);
    }
  }
  fclose(file);
}
