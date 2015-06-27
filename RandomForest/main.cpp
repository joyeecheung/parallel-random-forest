int factorial(int n) {
    int ret = 1;
    for (int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

int main(void) {
    for (int i = 0; i < 50060; ++i) {
        factorial(20516);
    }
    return 0;
}