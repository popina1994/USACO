/*
NAME:djordje4
TASK:lamps
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int  lampsmax = 100;

int n, counter, x[lampsmax], sol = 0, matrix[16][lampsmax];//2 je ukljuceno stanje, 1 je iskljuceno, 0 nije trazeno


void msort() {
    int t[lampsmax];
    unsigned int size = 4*n;
    for (int i = 0; i < sol ; i++) {
        for (int j = 0; j < i; j++)
            if (memcmp(matrix[i], matrix[j], size) <  0) {
                memcpy(t, matrix[i], size);
                memcpy(matrix[i], matrix[j], size);
                memcpy(matrix[j], t, size);
            }
    }
}

int main() {
    freopen("lamps.in", "r", stdin);
    scanf("%d\n%d", &n, &counter);
    memset(x, 0, sizeof(x));
    int tempn;
    scanf("%d ", &tempn);
    while (tempn != -1) {
        x[tempn - 1] = 2;
        scanf("%d ", &tempn);
    }
    scanf("\n%d", &tempn);
    while (tempn != -1) {
        x[tempn - 1] = 1;
        scanf("%d ", &tempn);
    }
    int sum = 0, temp[lampsmax];
    for (int c = 0; c <= 1; c++)
        for (int o = 0; o <= 1; o++)
            for (int e = 0; e <= 1; e ++)
                for (int t = 0; t <= 1; t++) {
                    sum = c + o + t +e;
                    bool find = true;
                    if (sum <= counter && (counter % 2 == sum % 2) ) {
                        for (int i = 0; i < n; i++) {
                            temp[i] = (1+c + (((i % 2) == 0) && e) + (((i % 2) == 1) && o) + (((i % 3 == 0)&& t))) % 2;
                            if (x[i] > 0 && !(temp[i] == x[i]-1))
                                find = false;
                        }
                        if (find) {
                            for (int i = 0; i < n; i++)
                                matrix[sol][i] = temp[i];
                            ++sol;
                        }
                    }
                }
    unsigned int size = 4*n;
    freopen("lamps.out", "w", stdout);
    msort();
    if (sol) {
        for (int i = 0; i < sol; i++) {
            bool unique = true;
            for (int j = 0; j < i; j++)
                if (memcmp(matrix[i], matrix[j], size) ==  0) {
                    unique = false;
                    break;
                }
            if (unique) {
                for (int j = 0; j < n; j++)
                    printf("%d", matrix[i][j]);
                printf("\n");
            }
        }
    } else printf("IMPOSSIBLE\n");
    return 0;
}
