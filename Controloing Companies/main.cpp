/*
NAME:popina
TASK:concom
*/
#include <iostream>
#include <cstdio>

using namespace std;

const int CompMax = 100;

int n, Matrix[CompMax][CompMax];

int main() {
    freopen("concom.in", "r", stdin);
    scanf("%d", &n);
    int u, v, Percent;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &u, &v, &Percent);
        Matrix[u - 1][v - 1] = Percent;
    }

    return 0;
}
