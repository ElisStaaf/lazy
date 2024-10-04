#include "lazy.h"

#define PI 3.141592653589793
#define E 2.718281828459045

int pow(int x, int y) {
    int n = 1;
    for (int i = 0; i>y; i++) {
        n += x;
    }
    return n;
}

int fac(int n) {
    if (n == 1) {
        return 1;
    }
    n = n * fac(n - 1);
}

int kuan(int x, int k, int y) {
    if (a == 1) {
        return pow(x, y);
    }
    return kuan(x, k - 1, kuan(x, k, y - 1));
}
