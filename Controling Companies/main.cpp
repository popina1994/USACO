/*
NAME:popina
TASK:concom
LANG:C++
*/
#include <iostream>
#include <cstdio>
#define DEBUG 0

using namespace std;

const int COMP_MAX = 100;

struct ControlPercent {
    int percent = 0, firstPercent = 0;
    bool passiveOwn[COMP_MAX + 1] = {0};
    friend ostream& operator << (ostream& out, const ControlPercent& cp) {
        out << cp.percent << endl;
        for (int idx = 1; idx <= COMP_MAX + 1; idx ++ )
            out << cp.passiveOwn[idx] << " ";
        return out << endl;
    }
};

ControlPercent own[COMP_MAX + 1][COMP_MAX + 1]; // procentazu

void PrintMatrix(ControlPercent x[COMP_MAX + 1][COMP_MAX + 1], int numComp) {
    for (int cntRow = 1; cntRow <= numComp; cntRow++) {
        for (int cntCol = 1; cntCol <= numComp; cntCol++)
            cout << x[cntRow][cntCol];
        printf("\n");
    }
    printf("\n");
}

int main() {
    freopen("concom.in", "r", stdin);
    freopen("concom.out", "w", stdout);

    int shit, numComp = COMP_MAX;
    scanf("%d", &shit); // shit number of triples
    for (int idx = 0; idx < shit; idx ++) {
        int u, v;
        scanf("%d%d", &u, &v);
        scanf("%d", &own[u][v].firstPercent);
    }

    for (int idx = 1; idx <= numComp; idx++) {
        own[idx][idx].percent = 51;
        own[idx][idx].firstPercent = 51;
    }

    bool change = true;
    while (change) {
        change = false;
        for (int k = 1; k <= numComp; k++)
            for (int i = 1; i <= numComp; i++)
                for (int j = 1; j <= numComp; j++)
                    if ((own[i][k].percent > 50) && (!own[i][j].passiveOwn[k]) && (own[i][j].percent < 51) ) {
                        if ( (i == 1) && (j == 37) && DEBUG)
                            printf("\n\n %d : %d %d \n\n", k, own[i][k].percent, own[k][j].percent);
                        own[i][j].percent +=  own[k][j].firstPercent;
                        own[i][j].passiveOwn[k] = true;

                        if (own[i][j].percent > 50)
                            change = true;
                        }
    }
    if (DEBUG) {
        PrintMatrix(own, numComp);
    }
    for (int row = 1; row <= numComp; row++)
        for (int col = 1; col <= numComp; col++)
            if ( (own[row][col].percent >= 51) && (row != col) )
                printf("%d %d\n", row, col);

    return 0;
}
