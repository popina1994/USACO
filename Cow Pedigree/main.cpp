/*
NAME:djordje4
TASK:nocows
LANG:C++
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#define HEIGHT_MAX 200
#define NODES_MAX 200

using namespace std;

int height, // visina
    numNode, x[HEIGHT_MAX + 1][NODES_MAX + 1] = {0}; // broj cvorova


void PrintMatrix(int x[][NODES_MAX + 1]) {
    printf("%7d", 0);
    for (int cntCol = 0; cntCol <= numNode; cntCol++)
        printf("%7d", cntCol);
    printf("\n\n");

    for (int cntRow = 0; cntRow <= height; cntRow++) {
        printf("%7d", cntRow);
        for (int cntCol = 0; cntCol <= numNode; cntCol++)
            printf("%7d", x[cntRow][cntCol]);
        printf("\n\n");
    }
}

int main() {
    freopen("nocows.in","r", stdin);
    freopen("nocows.out", "w", stdout);
    scanf("%d%d", &numNode, &height);

    for (int cnt = 1; cnt <= height; cnt++)
        x[cnt][1] = 1;

    // Broj stabala sa visinom 1 je 1, a broj stabala sa visinom 0 (nema stabla) je isto 1

    for (int cntHeight = 1; cntHeight <= height; cntHeight++)
        for (int cntNode = 1; cntNode <= numNode; cntNode ++)
            for (int nodeLeft = 1; nodeLeft < numNode; nodeLeft += 2) {
                /* Чињеница да се nodeLeft увећава за 2, следи из услова задатка да сваки
                 чвор мора имати 0 или 2 потомака. Дакле укупан број чворова је 2 * k + 1
                 (корен стабла), стога у левом подстаблу може бити 2 * k + 1 чворова.
                */
                x[cntHeight][cntNode] +=  x[cntHeight -1][nodeLeft] * x[cntHeight - 1][cntNode - nodeLeft- 1];
                x[cntHeight][cntNode] %= 9901;
            }

    PrintMatrix(x);
    printf("%d\n", (9901 + x[height][numNode] - x[height - 1][numNode]) % 9901);
    return 0;
}
