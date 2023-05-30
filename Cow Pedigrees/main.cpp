/*
NAME:djordje4
TASK:nocows
LANG:C++
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#define HEIGHT_MAX 199
#define NODES_MAX 99

using namespace std;

int height, // visina
    numNode, x[HEIGHT_MAX + 1][NODES_MAX + 1]; // broj cvorova


void PrintMatrix(int x[][NODES_MAX + 1]) {
    for (int cntRow = 0; cntRow <= height; cntRow++) {
        for (int cntCol = 0; cntCol <= numNode; cntCol++)
            printf("%d\t", x[cntRow][cntCol]);
        printf("\n");
    }
}

int main() {
    freopen("nocows.in","r", stdin);
    freopen("nocows.out", "w", stdout);
    scanf("%d%d", &numNode, &height);


    memset(x, 0, sizeof(x)); // cela dinamicka matrica je 0

    x[0][0] = 1;
    x[1][1] = 1;
    x[2][3] = 1;
    x[2][2] = 0;

    for (int cntHeight = 3; cntHeight <= height; cntHeight++)
        for (int cntNodes = 3; cntNodes <= numNode; cntNodes += 2)
            for (int nodeLeft = 0; nodeLeft <= cntNodes / 2; nodeLeft++) // broj cvorova levo
                for (int heightLeft = 1; heightLeft <= cntHeight - 1; heightLeft++) { // visina levo
                   /* if (cntHeight == 4 && cntNodes == 13)
                        printf("%d %d %d %d\n",heightLeft, nodeLeft, x[heightLeft][nodeLeft] , x[cntHeight-1][cntNodes-1-nodeLeft] );;*/
                    x[cntHeight][cntNodes] +=  (1 + (nodeLeft != (cntNodes-1-nodeLeft))) * x[heightLeft][nodeLeft] * x[cntHeight-1][cntNodes-1-nodeLeft];
                    x[cntHeight][cntNodes]  %= 9901;
                }

    PrintMatrix(x);
    printf("%d\n", x[height][numNode]);
    return 0;
}
