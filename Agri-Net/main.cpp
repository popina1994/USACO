/*
TASK: agrinet
LANG: C++
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define DEBUG false
#define TEST false

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

struct Edge {
    int first, second, weight;

    Edge(int _first = -1, int _second = -1, int _weight = -1) : first(_first), second(_second), weight(_weight) {}

    bool operator<(const Edge& p) const {
        return (weight < p.weight);
    }

    bool operator==(const Edge& p) const {
        return weight == p.weight;
    }

    friend ostream& operator<<(ostream& out, const Edge& e) {
        return out << "(" << e.first << ", " << e.second << ", " << e.weight << ")";
    }
};

const int MAX_FARMS = 100;

typedef vector < vector <int> > Matrix;

//Matrix graph(MAX_FARMS, vector <int>(MAX_FARMS, 0));
vector <Edge> edge;
vector <bool> mark;
deque < set<int> > comp;

int FindSet(deque < set<int> >& comp, int searchIdx) {
    int idx = 0;
    for (deque< set<int> >::iterator it = comp.begin(); it != comp.end(); it++, idx ++)
        if ( (it->find(searchIdx)) != it->end())
            return idx;
}

void JoinSets(deque <set<int> >& comp, int first, int second) {
    set<int>& sSecond = comp.at(second), & sFirst = comp.at(first);

    while (!sSecond.empty()) {
        set<int>::iterator it = sSecond.begin();
        sFirst.insert(*it);
        sSecond.erase(*it);
    }
    comp.erase(comp.begin()+second);
}

int main() {
    if (!TEST) {
            freopen("agrinet.in", "r", stdin);
            freopen("agrinet.out", "w", stdout);
            if (DEBUG)
                freopen("agrinet.err", "w", stderr);
        }

    int n;
    scanf("%d", &n);
    mark.resize(n, false);

    for (int row = 0; row < n; row ++)
        for (int col = 0; col < n; col ++) {
            int weight;
            scanf("%d", &weight);
            edge.push_back(Edge(row, col, weight));
        }
    sort(edge.begin(), edge.end());


    for (int idx = 0; idx < n; idx ++) {
        comp.push_back(set<int>());
        comp[idx].insert(idx);
    }

    int sum = 0, cnt = 0;

    for (vector<Edge>::iterator e = edge.begin(); e != edge.end(); e ++) {
        int first = FindSet(comp, e->first), second = FindSet(comp, e->second);

        if (first != second) {
            sum += e->weight;
            JoinSets(comp, first, second);
            if (++cnt ==  n - 1)
                break;
        }
    }
    printf("%d\n", sum);

	return 0;
}
