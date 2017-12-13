#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  FILE *file = fopen("example2", "r");
  char templ_s[256];
  for (int i = 0; i < 256; i++) {
    templ_s[i] = 0;
  }
  while (!feof(file)) {
    char s[256];
    for (int i = 0; i < 256; i++) {
      s[i] = 0;
    }
    fgets(s, 256, file);
    for (int i = strlen(s); i < 256; i++) {
      s[i] = 0;
    }
    for (int i = 0; i < 256; i++) {
      templ_s[i] = templ_s[i] ^ s[i];
    }
  }
  for (int i = 0; i < 256; i++) {
    printf("%c", templ_s[i]);
  }
  fclose(file);
}
