/*
NAME:djordje4
TASK:sort3
LANG:C++
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int nmax = 1000;

int n, x[nmax], y[3][3];

void ispis() {
    for (int i = 0; i < 3; i++ ) {
        for (int j = 0; j < 3; j++ )
            cout << y[i][j];
        cout << endl;
    }


}

void input() {
    freopen("sort3.in", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++ )
        scanf("%d", &x[i]);
}

void output(int sol) {
    freopen("sort3.out", "w", stdout);
    printf("%d\n", sol);
}

int main() {
    int counter[3], index[4];
    int sol;
    input();
    memset(counter, 0, sizeof(counter));
    for (int i = 0; i < n; i++ )// utvrdjuje broj 1, 2, 3
        for (int j = 0; j < 3; j++ )
            if (x[i] == j + 1)
                counter[j]++;
    index[0] = 0;
    index[1] = counter[0];
    index[2] = counter[0 ]+ counter[1];
    index[3] = n;
    memset(y, 0, sizeof(y));
    for (int i = 0; i < 3; i++ )
        for (int j = index[i]; j < index[i+1]; j++ ) // (i, j) polje oznacava koliko na mestima na kojima treba da bude element i+1 ima j+1 elemenata
            y[i][x[j]-1]++;
    int countery = 0;
    y[0][0] += y[1][0];
    countery += y[1][0];
    if (y[1][0] > y[0][1]) {
        y[1][2] += y[1][0]-y[0][1];
        y[0][2] -= y[1][0]-y[0][1];
        y[1][0] = 0;
    }
    y[0][0] += y[2][0];
    countery += y[2][0];
    y[2][0] = 0;
    countery += y[1][2];
    output(countery);
    return 0;
}
