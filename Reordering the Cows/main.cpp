#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>

using namespace std;

const int MaxNum = 100, AdjacentX[4] = {-1, 1, 0, 0}, AdjacentY[4] = {0, 0, -1, 1};

int human[MaxNum][MaxNum], cow[MaxNum][MaxNum];
char x[MaxNum][MaxNum], xCow[MaxNum][MaxNum];

bool IsVaild (int i, int j, int n) {
    return ((i < n) && (i >= 0) && (j < n) && (j >= 0));
}

void Visit(int x[][MaxNum], char color[][MaxNum], int row, int column, int counter, int n, char letter) {
    if (IsVaild(row, column, n)  && x[row][column] == 0 && color[row][column] == letter) {
        x[row][column] = counter;
        for (int i = 0; i < 4; i ++)
            Visit(x, color, row + AdjacentX[i], column + AdjacentY[i], counter, n, letter);
    }
}


int main() {
    int n, counter = 0;

    freopen("cowart.in", "r", stdin);
    freopen("cowart.out", "w", stdout);
    scanf("%d\n", &n);

    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j++) {
            scanf("%c", &x[i][j]);
            xCow[i][j] = x[i][j];
            if (x[i][j] == 'G')
                xCow[i][j] = 'R';
        scanf("\n");
        }

    }

    memset(human, 0, sizeof(human));
    memset(cow, 0, sizeof(cow));


    counter = 1;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j++) {
            Visit(human, x, i, j, counter, n, x[i][j]);
            if (human[i][j] == counter)
                counter ++;
    // ako je poseceno povecaj brojac za jedan
    }
    printf("%d ", counter - 1);

    counter = 1;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j++) {
        Visit(cow, xCow, i, j, counter, n, xCow[i][j]);
        if (cow[i][j] == counter)
            counter ++;
    }
    printf("%d\n", counter - 1);

    // oprezno sa ovim uslovom za brojac




    return 0;
}
