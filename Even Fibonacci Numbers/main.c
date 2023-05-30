#include <stdio.h>
#include <stdlib.h>

const int nMax  = 4000000;

int main() {
    int a = 1, b = 2, c, i, sum  = 0;
    freopen("izlaz.out", "w", stdout);
    c = a + b;
    while (c <= nMax) {
        if (c % 2 == 0) {
            sum += c;
        }
        printf("%d %d %d\n", a, b, c);
        a = b;
        b = c;
        c = a + b;

    }
    printf("%d", sum);
    return 0;
}
