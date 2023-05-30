/*
TASK: cowtour
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>
#include <cmath>
#include <queue>
#include <deque>
#include <cfloat>
#include <algorithm>

#define DEBUG false
#define TEST false

const int MAX_PASTURE = 150;

using namespace std;

struct Position {
    int x, y;

    Position(int _x = -1, int _y = -1) : x(_x), y(_y) {}

    friend ostream& operator<<(ostream& out, const Position& n) {
        return out << "(" << n.x << ", " << n.y << ")";
    }
};

struct DebugOutput {
    template <typename T>
    friend DebugOutput& operator<<(DebugOutput& d, const T& val) {
        if (DEBUG && !TEST)
            cerr << val;
        return d;
    }
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;

    typedef CoutType& (*StandardEndLine)(CoutType&);

    friend DebugOutput& operator<<(DebugOutput& d, const StandardEndLine& manip) {
        if (DEBUG && !TEST)
            cerr << manip;
        return d;
    }
} dbgOut;

typedef vector < vector <int> > Graph;
typedef vector < vector <int> > Conjecture;
typedef vector < vector <double> > Matrix;

vector<Position> vPos(MAX_PASTURE);
Graph graph(MAX_PASTURE);
Matrix floyd;
vector <double> diamter, distMax;


enum VISIT {VISITED = 0, VISITING, NOTVISITED};

Conjecture conjecture;

double Distance(const Position& p1, const Position& p2) {
    return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
}

void Visit(Graph& g, vector<VISIT>& visited, Conjecture& conjecture, int curNode) {
    queue <int> visiting;

    visiting.push(curNode);

    conjecture.push_back(vector <int>());
    while (!visiting.empty()) {
        int visitNode = visiting.front(); // removes element as we visited it
        visiting.pop();

        visited[visitNode] = VISITED;
        conjecture.back().push_back(visitNode); // pushing in current conjecture

        // iterate through all unvisited neighbours of visitNode
        for (vector<int>::iterator it = g[visitNode].begin(); it != g[visitNode].end(); it ++) {
            if ( (visited[*it] != VISITED) && (visited[*it] != VISITING) ) {
                visiting.push(*it);
                visited[*it] = VISITING;
            }
        }
    }
    dbgOut << endl;
}

void BFS(Graph& g, Conjecture& conjecture) {
    vector <VISIT> visited(g.size(), NOTVISITED); // init list of visited nodes to false

    for (int idx = 0; idx < visited.size(); idx ++)
        if (visited[idx] != VISITED)
            Visit(g, visited, conjecture, idx);
}

void Floyd(Graph& graph, vector <Position>& vPos, Matrix& floyd) {
    floyd.resize(graph.size());

    for (int idx = 0; idx < graph.size(); idx ++) {
        floyd[idx].resize(graph.size(), DBL_MAX / 4 - 1);
        floyd[idx][idx] = 0;
    }

    for (int node = 0; node < graph.size(); node ++)
        for (int adj = 0; adj < graph[node].size(); adj++) {
            floyd[node][graph[node][adj]] = Distance(vPos[node], vPos[graph[node][adj]]);
            dbgOut << node << " " << graph[node][adj] << " " << floyd[node][graph[node][adj]] << endl;
        }


    for (int over = 0; over < graph.size(); over ++)
        for (int i = 0; i < graph.size(); i ++)
            for (int j = 0; j < graph.size(); j ++)
                floyd[i][j] = min(floyd[i][over] + floyd[over][j], floyd[i][j]);

    for (int row = 0; row < floyd.size(); row ++) {
        for (int col = 0; col < floyd.size(); col ++)
            dbgOut << floyd[row][col] << " ";
        dbgOut << endl;
    }
}

void DiameterConj(vector <double>& diameter, vector <double>& distMax, Conjecture& conjecutre, Matrix& floyd) {
    diameter.resize(conjecture.size(), 0);
    distMax.resize(floyd.size(), 0);
    // for all nodes calculate dimater
    for (int idx = 0; idx < diameter.size(); idx++ ) {
        // node denotes current node for which diamter is calculated
        for (vector<int>::iterator node = conjecture[idx].begin(); node != conjecture[idx].end(); node ++) {
            for (vector<int>::iterator check = conjecture[idx].begin(); check != conjecture[idx].end(); check ++) {
                dbgOut << "Checking"  << *node << " "<< *check <<  endl;
                distMax[*node] = max(distMax[*node], floyd[*node][*check]);
                diameter[idx] = max(diameter[idx], distMax[*node]);
            }
            dbgOut << "DstMax " << *node << " " << distMax[*node] << endl;
        }

        dbgOut << "Diamter" << idx << " " << diameter[idx] << endl;

    }
}

double Connect(vector <double>& diameter, vector <double>& distMax, Conjecture& conjecture, vector <Position>& vPos) {
    double curMin = DBL_MAX;
    bool changed = false;
    for (int con1 = 0; con1 < conjecture.size() - 1; con1++)
        for (int con2 = con1 + 1; con2 < conjecture.size(); con2++) {
            double tmpMin = DBL_MAX;

            for (vector<int>::iterator node1 = conjecture[con1].begin(); node1 != conjecture[con1].end(); node1 ++)
                for (vector<int>::iterator node2 = conjecture[con2].begin(); node2 != conjecture[con2].end(); node2 ++) {
                    dbgOut << "Node connecting " << *node1 << " " << *node2 << " " \
                    << distMax[*node1] + distMax[*node2] + Distance(vPos[*node1], vPos[*node2]) << endl;
                    tmpMin = min(tmpMin, distMax[*node1] + distMax[*node2] + Distance(vPos[*node1], vPos[*node2]));
                }
            dbgOut << "Min for components is " << curMin << endl;
            dbgOut << "Diameter is" << diameter[con1] << " " << diameter[con2] << endl;
            curMin = min(max(max(diameter[con1], diameter[con2]), tmpMin), curMin);
        }
    return curMin;
}

int main() {

    if (!TEST) {
        freopen("cowtour.in", "r", stdin);
        freopen("cowtour.out", "w", stdout);
        if (DEBUG)
            freopen("cowtour.err", "w", stderr);
    }

    int n;
    scanf("%d", &n);

    for (int idx = 0; idx < n; idx ++) {
        Position p;
        scanf("%d%d", &p.x, &p.y);
        vPos[idx] = p;
    }
    graph.resize(n);

    for (int row = 0; row < n; row ++) {
        char s[MAX_PASTURE];
        scanf("%s", s);
        for (int col = 0; col < n; col ++) {
            if (s[col] == '1')
                graph[row].push_back(col);
            dbgOut << s[col];
        }
        dbgOut << "Size of adjacent is" << graph[row].size() << endl;
    }

    BFS(graph, conjecture);
    Floyd(graph, vPos, floyd);
    DiameterConj(diamter, distMax, conjecture, floyd);
    printf("%lf\n", Connect(diamter, distMax, conjecture, vPos));



    return 0;
}
