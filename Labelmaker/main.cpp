#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

const int t_max = 20, l_max = 25, n_max = 55;

int t, sn[n_max], length;
long long n;
char s[n_max + 1];

void input(char s[],long long &n) {
    scanf("%s%lld", s, &n);
}

void conv(long long n, int x[], int brsl, int &length) {
    int i = 0, counter;
    unsigned long long brpr;
    if (brsl == 1) {
        for (i = 0; i < brsl; i ++) x[i] = 0;
        length = i;
    }
    else {
        brpr = 1ll;
        counter = 0;
        while (n > brpr * brsl && brpr != 0ll && n > 0ll) {
            counter ++;
            n -= brpr * brsl;
            brpr *= brsl;
        }
        n --;
        for (i = 0; i < counter + 1; i ++) {
            x[i] = (int)(n % brsl);
            n /= brsl;
        }
        length = counter + 1;
    }
}

void write(int x[], int length, char s[], int t) {
    int i;
    printf("Case #%d: ", t);
    for (i = length - 1; i >= 0; i --)
        printf("%c", s[x[i]]);
    printf("\n");
}


int main() {
    freopen("main.in", "r", stdin);
    scanf("%d", &t);
    for (int i = 0; i < t; i ++) {
        input(s, n);
        conv(n, sn, strlen(s), length);
        write(sn, length, s, i + 1);
    }
    return 0;
}
