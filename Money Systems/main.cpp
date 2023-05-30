/*
NAME:popina
TASK:money
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const int nmax = 10000, numcoinmax = 25;

ll x[nmax], y[numcoinmax];

int numcoin, n;

int main(){
    memset(x, 0, sizeof(x));
    freopen("money.in", "r", stdin);
    scanf("%d %d\n", &numcoin, &n);
    for (int i = 0; i < numcoin; i++)
        scanf("%ld", &y[i]);
    x[0] = 1;
    for (int i = 0; i < numcoin; i++)
        for (int j = 0; j < n; j++)
            if (x[j] > 0 && y[i] + j <= n)
                x[y[i] + j] ++;
    freopen("money.out", "w", stdout);
    printf("%ll", x[n]);
    return 0;
}
