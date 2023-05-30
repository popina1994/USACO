/*
PROB:  ttwo
NAME: popina
LANG: C++
*/

#include <iostream>
#include <cstdio>

using namespace std;

const int SIZE = 10, WAYS = 4;
const bool DEBUG = false;
const int rowMove[WAYS] = {-1, 0, 1, 0}, colMove[WAYS] = {0, 1, 0, -1};

int x[SIZE][SIZE];



struct Position {
    enum DIR  {NORTH = 0, EAST, SOUTH, WEST};

    int row, col;
    DIR dir = NORTH;

    Position(int _row = -1, int _col = -1) : row(_row), col(_col) {}

    bool operator==(const Position& p) const {
        return row == p.row && col == p.col;
    }

    void Advance() {
        int newRow = row + rowMove[dir], newCol = col + colMove[dir];

        if ( (newRow < SIZE) && (newRow >= 0) && (newCol < SIZE) && (newCol >= 0)
            && (x[newRow][newCol] != '*') ) {
            row = newRow;
            col = newCol;
        }
        else
            dir = (DIR)( (dir + 1) % WAYS);
    }

    friend ostream& operator<<(ostream& out, const Position& p) {
        static string x[WAYS] = {"NORTH", "EAST", "SOUTH", "WEST"};
        return out << "( " << p.row << " ," << p.col << ") " << x[p.dir] << endl;
    }
};

int main() {
    freopen("ttwo.in", "r", stdin);
    freopen("ttwo.out", "w", stdout);

    Position posFarmer, posCows;

    for (int row = 0; row < SIZE; row ++) {
        for (int col = 0; col < SIZE; col ++) {
            scanf("%c", &x[row][col]);
            if (x[row][col] == 'F')
                posFarmer = Position(row, col);
            if (x[row][col] == 'C')
                posCows = Position(row, col);
        }
        scanf("\n");
    }

    for (int idx = 0; idx < 1000000; idx ++) {
        if (posCows == posFarmer) {
            printf("%d\n", idx);
            return 0;
        }
        if (DEBUG) {
            cout << "Farmer:" << posCows;
            cout << "Cows:" << posCows;
        }
        posCows.Advance();
        posFarmer.Advance();
    }
    printf("0\n");

    return 0;
}
