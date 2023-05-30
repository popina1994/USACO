/*
NAME:popina
TASK:preface
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int nmax = 3499, romanmax = 21;

char let[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
int x[7] = {1, 5, 10, 50, 100, 500, 1000}, temp, n, r[7];
int PowerofTen[7] = {0, 0, 1, 0, 1, 0, 1}, quotient;

int main() {
    freopen("preface.in", "r", stdin);
    scanf("%d", &n);
    memset(r, 0, sizeof(r));
    for (int i = 1; i <= n; i++) {
        temp  = i;
        for (int j = 6; j >= 0; j--) {
            while (temp / x[j] > 0 && temp > 0) {
                r[j] += temp / x[j];
                temp %= x[j];
            }
            if (PowerofTen[j] && temp >= x[j] - x[j-2]) {
                r[j]++;
                r[j-2]++;
                temp -= x[j] - x[j-2];
            }
            if (j  > 0 && temp >= x[j] - x[j-1] && !PowerofTen[j]) {
                r[j]++;
                r[j-1] ++;
                temp -= x[j] - x[j-1];
            }
        }
    }
    freopen("preface.out", "w", stdout);
    for (int i = 0; i < 7; i++)
        if (r[i] > 0)
            printf("%c %d\n", let[i], r[i]);
    return 0;
}
