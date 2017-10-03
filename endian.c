#include <stdio.h>
union Data {
    int  i;
    char c[sizeof(int)];
};

int main(int argc, char const * argv[])
{
    union Data data;

    data.i = 0x01020304;

    printf("%s\n", data.c[0] == 4 ? "little-endian" : "big-endian");
    return 0;
}

// #include <stdio.h>
// unsigned short x = 1; /* 0x0001 */
// int main(void)
// {
//   printf("%s\n", *((unsigned char *) &x) == 0 ? "big-endian" : "little-endian");
//   return 0;
// }
