#include <vector>
#include <cstdio>

int factorial(int n) {
    int ret = 1;
//#pragma omp parallel for
    for (int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

int main(void) {
//#pragma omp parallel for
    for (int i = 0; i < 1455; ++i) {
        int z = factorial(2305167);
        //printf("%d, %d\n", i, z);
    }
    return 0;
}