/*
NAME:djordje4
TASK:holstein
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int vmax = 25, vreq  = 1000, gmax = 15, greq = 1000;

int numvit, vit[vmax], numg, feed[gmax][vmax], feedsol[gmax], x[gmax], xsol[gmax];

// i  oznacava koja je smesa, j oznacava koji vitamin


void input() {
    freopen("holstein.in", "r", stdin);
    scanf("%d", &numvit);
    for (int i = 0; i < numvit; i++)
        scanf("%d", &vit[i]);
    scanf("%d", &numg);
    for (int i = 0; i < numg; i++ )
        for(int j  =0; j < numvit; j++)
            scanf("%d", &feed[i][j]);
}

double factorial(int n) {
    if (n == 0)
        return  1;
    double tempfact = 1;
    for (int i = 1; i <= n; i++ )
        tempfact *= i;
    return tempfact;
}

int binomial(int n, int k) {
    return (int(factorial(n)/(factorial(k)*factorial(n-k))));
}

void ispis() {
    for (int i = 0; i  < numg; i++ )
        cout << x[i] << " ";
    cout << endl;
}

void ispis2() {
    for (int i = 0; i < numg; i++)
        cout << xsol[i] << " ";
    cout << endl;
}

int sumvitamin(int n) { // oznacava koji po redu se vitamin uzima
    int sum = 0;
    for (int i = 0; i < numg; i++)
        sum += x[i]*feed[i][n];
    return (sum >= vit[n]);
}

bool holstein() {
    for (int i = 0; i < numvit; i++ )
        if (!sumvitamin(i))
            return false;
    return true;
}

int solution() {
    for (int i = 1; i <= numg; i++ ) {
        x[i-1] = 1;
        bool found = false;
        for (int j = 0; j < binomial(numg, i); j++) {
            if (holstein()) {
                found = true;
                if (!lexicographical_compare(x, x+numg,xsol,xsol+numg))
                    memcpy(xsol, x, sizeof(x));
            }
            next_permutation(x, x + numg);
        }
        if (found)
            return i;

    }
}

void output(int sol) {
    freopen("holstein.out", "w", stdout);
    printf("%d", sol);
    for (int i = 0; i < numg; i++ )
        if (xsol[i] == 1 )
                printf("% d", i+1);
    printf ("\n");


}

int main() {
    int sol;
    memset(x, 0, sizeof(x));
    memset(xsol, 0, sizeof(xsol));
    input();
    sol = solution();
    output(sol);
    return 0;
}
