/*
LANG : C++
TASK : maze1
*/
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

const int WIDTH_MAX = 38, HEIGHT_MAX = 100, EXITS = 2, WAYS = 4;

int x[2 * HEIGHT_MAX + 1][2 * WIDTH_MAX + 1] = {0};

struct Position {
    int row, col;

    Position(int _row = -1, int _col = -1) : row(_row), col(_col) {}

    friend ostream& operator<<(ostream& out, const Position& p) {
        return out << "(" << p.row << " ," << p.col << ")";
    }
};

Position exits[EXITS];

void FindExit(int x[][2 * WIDTH_MAX + 1], int numRow, int numCol, Position exits[]) {
    int cnt = 0;
    for (int row = 0; row < 2 * numRow + 1; row ++) {
        if (x[row][0] == 0)
            exits[cnt++] = Position(row, 1);
        if (x[row][2 * numCol] == 0)
            exits[cnt++] = Position(row, 2 * numCol - 1);
    }

    for (int col = 0; col < 2 * numCol + 1; col ++) {
        if (x[0][col] == 0)
            exits[cnt++] = Position(1, col);
        if (x[2 * numRow][col] == 0)
            exits[cnt++] = Position(2 * numRow - 1, col);
    }
}

bool CanJump(int fromRow, int fromCol, int row, int col, int x[][2*WIDTH_MAX + 1], int numRow, int numCol) {
    if ( (row < 0) || (row > 2 * numRow) || (col < 0) || (col > 2 * numCol) || (x[row][col] != 0 ) || (
    x[ (fromRow + row ) / 2][ (fromCol + col) / 2] == -1) )
        return false;
    return true;
}

void OutputMatrix(int x[][2 * WIDTH_MAX + 1], int numRow, int numCol) {
    for (int row = 0; row <= 2 * numRow; row ++) {
        for (int col = 0; col <= 2 * numCol; col ++)
            printf("%2d", x[row][col]);
        printf("\n");
    }
}

int ParalelBFS(int x[][2 * WIDTH_MAX + 1], int numRow, int numCol, Position exits[]) {
    static int rowInc[WAYS] = {-2, 2, 0, 0},
             colInc[WAYS] = {0, 0, 2, -2};
    queue <Position> jmpPos;

    int jmp = 1, posToCheck = 2;

    for (int idxExit = 0; idxExit < EXITS; idxExit ++) {
        jmpPos.push(exits[idxExit]);
        x[exits[idxExit].row][exits[idxExit].col] = 1;
    }


    while (!jmpPos.empty()) {
        int tmpPosToCheck = 0;
        jmp++;

        //OutputMatrix(x, numRow, numCol);

        //cout << endl;
        for (int cnt = 0; cnt < posToCheck; cnt ++ ) {
            Position curPos = jmpPos.front();
            jmpPos.pop();
            for (int idxInc = 0; idxInc < WAYS; idxInc++) {
                int row = curPos.row + rowInc[idxInc],
                    col = curPos.col + colInc[idxInc];

                if (CanJump(curPos.row, curPos.col, row, col, x, numRow, numCol)) {
                    jmpPos.push(Position(row, col));
                    x[row][col] = jmp;

                    tmpPosToCheck++;
                }
                }
        }
        posToCheck = tmpPosToCheck;
    }
    return jmp - 1;
}

int main() {
    freopen("maze1.in", "r", stdin);
    freopen("maze1.out", "w", stdout);
    int numRow, numCol;

    scanf("%d%d\n", &numCol, &numRow);

    for (int row = 0; row < 2 * numRow + 1; row ++) {
        string s;
        getline(cin, s);
        for (int col = 0; col < 2 * numCol + 1; col ++) {
            char c = s[col];
            if ( (c == '+' ) || (c == '-') || (c == '|') )
                x[row][col] = -1;
        }

    }
    FindExit(x, numRow, numCol, exits);
    cout << ParalelBFS(x, numRow, numCol, exits) << endl;


    return 0;
}
