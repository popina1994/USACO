/*
NAME:popina
TASK:subset
LANG:C++
*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long ll;

const int nmax = 39*20;

ll x[nmax+1], y[nmax+1];

int n, sol = 0;

int main()
{
    freopen("subset.in", "r", stdin);
    scanf("%d", &n);
    memset(x, 0, sizeof(x));
    x[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = n*(n+1)/2; j >= 0; j--)
            if (x[j] > 0 )
                    x[j+i] += x[j];
    freopen("subset.out", "w", stdout);

    if (n % 4 == 3 || n % 4 == 0)
        printf("%d\n", x[n*(n+1)/4]/2);
    else printf("0\n");
    return 0;
}
