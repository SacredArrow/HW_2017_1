#include <stdio.h>

int bitAnd(int x, int y){
        return ~(~x | ~y);
}

int bitXor(int x, int y){
        int x1 = ~(x & y);
        int y1 = ~(~x & ~y);
        return x1 & y1;
}

int thirdBits(void){
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

int fitsBits(int x, int n){
  int power = ( 1 << n - 1) - 1;
  int neg_power = ~power;
  return x <= power & x >= ~power;
}

int sign(int x){
  return (x > 0) - (x < 0);
}

int getByte(int x, int n){
        int one = 255;
        one = one << n*8;
        x = x & one;
        return x >> n*8;

}

int logicalShift(int x, int n){
        x = x >> n;
        x= x & (~(((1 << 31) >> n) << 1));
        return x;

}

int addOK(int x, int y){
  int n = 31;
  x = x >> n;
  int logicalX= x & (~(((1 << 31) >> n) << 1));
  x = y;
  x = x >> n;
  int logicalY= x & (~(((1 << 31) >> n) << 1));
  return !(logicalX & logicalY);
  }

int bang(int x){
        return x == 0;
}

int conditional(int x, int y, int z){
        int y_con = ((((x != 0) << 31) >> 31) & y);
        int x_con=((((x == 0) << 31) >> 31) & z);
        return (y_con + x_con);
}

int isPower2(int x){
  return (!(x & (x-1))) & (x != 0);
}

int main(int argc, char const *argv[]) {
        // for (int i = 0; i<=100; i++)
        printf("%d\n",isPower2(0));
        return 0;
}


// x y x^y   x y x&y ~(x&y) x|y
// 0 0 0     0 0 0    1     0
// 1 0 1     1 0 0    1     1
// 0 1 1     0 1 0    1     1
// 1 1 0     1 1 1    0     1
