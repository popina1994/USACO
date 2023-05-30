/*
TASK : comehome
LANG : C++
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define DEBUG false
#define TEST false

const int MAX_LEN = 5;
const int MAX_PASTURE = 52, LETTERS = 26, MAX = 52000;

struct DebugOutput {
    template <typename T>
    friend DebugOutput& operator<<(DebugOutput& d, const T& val) {
        if (DEBUG && !TEST)
            cerr << val;
        return d;
    }
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;

    typedef CoutType& (*StandardEndLine)(CoutType&);

    // define an operator<< to take in std::endl
    friend DebugOutput& operator<<(DebugOutput& d, const StandardEndLine& manip) {
        if (DEBUG && !TEST)
            cerr << manip;
        return d;
    }
} dbgOut;

typedef vector < vector <int> > Matrix;


Matrix graph(MAX_PASTURE, vector<int>(MAX_PASTURE, MAX));
Matrix floyd(MAX_PASTURE, vector<int>(MAX_PASTURE, MAX));

int Convert(char c) {
    return c <= 'Z' ? c - 'A' : c - 'a' + LETTERS;
}

char ReverseConvert(int idx) {
    return idx <= 25 ? idx + 'A'  : idx - LETTERS + 'a';
}

void Floyd(Matrix& floyd, Matrix& graph) {
    for (int row = 0; row < MAX_PASTURE; row ++)
        for (int col = 0; col < MAX_PASTURE; col ++)
            if (graph[row][col] != MAX)
                floyd[row][col] = floyd[col][row] = graph[row][col];

    for (int idx = 0; idx < MAX_LEN; idx ++)
        floyd[idx][idx] = 0;

    for (int over = 0; over < MAX_PASTURE; over ++)
        for (int i = 0; i < MAX_PASTURE; i ++)
            for (int j = 0; j < MAX_PASTURE; j ++) {
                floyd[i][j] = min(floyd[i][j], floyd[i][over] + floyd[over][j]);
                dbgOut << ReverseConvert(i)<< " over " << ReverseConvert(over) << " to " << ReverseConvert(j) << " " << \
                floyd[i][over] + floyd[over][j] << "Cur" << floyd[i][j] << endl;
            }

}



void FindAndOutput(Matrix& floyd) {
    int barn = Convert('Z'), beginPasture = Convert('A'), endPasture = Convert('Z' - 1);
    int minDist = INT_MAX, minIdx = -1;

    for (int idx = beginPasture; idx <= endPasture; idx ++) {
        dbgOut << "Cur" << minDist << " " << floyd[idx][barn] << endl;
        if (floyd[idx][barn] < minDist) {
            minDist = floyd[idx][barn];
            minIdx = idx;
        }
    }
    printf("%c %d\n", minIdx + 'A', minDist);
}

int main() {
    if (!TEST) {
            freopen("comehome.in", "r", stdin);
            freopen("comehome.out", "w", stdout);
            if (DEBUG)
                freopen("comehome.err", "w", stderr);
    }
    int n;
    scanf("%d\n", &n);

    for (int cnt = 0; cnt < n; cnt ++) {
        char c1, c2;
        int weight;
        scanf("%c %c %d\n", &c1, &c2, &weight);
        int first = Convert(c1),
            second = Convert(c2);
        dbgOut << "Here" <<  first << " " << second << " " << weight << endl;

        graph[second][first] = graph[first][second] = min(graph[first][second], weight);
    }



    Floyd(floyd, graph);
    for (int row = 0; row < MAX_PASTURE; row ++) {
        dbgOut << ReverseConvert(row) << " ";
        for (int col = 0; col < MAX_PASTURE; col ++)
            dbgOut << floyd[row][col] << " ";
        dbgOut << endl;
    }
    FindAndOutput(floyd);
	return 0;
}
