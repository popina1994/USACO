/*
NAME:popina
TASK:wormhole
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <algorithm>
#define DEBUG 0

using namespace std;

const int NUM_MAX = 12;

struct Position {
    int x, y, conectedWormhole;
    friend ostream& operator<<(ostream& out, const Position& pos) {
        return out << "(" << pos.x << ", " << pos.y << ")" << " " << pos.conectedWormhole;
    }
};

vector <Position> vPos;
vector <int> vIndex;

bool Comp(const Position& p1, const Position& p2) {
    return (p1.y < p2.y) || ( (p1.y == p2.y) && (p1.x < p2.x) );
}

// returns true if there is infinite cycle starting from wormhole with index idx
bool TestCycle(vector <Position>& x, int idx) {
    bool visited[NUM_MAX] = {0};

    for (unsigned int visitorWormhole = 0; visitorWormhole < x.size(); visitorWormhole++) {
        if ( (idx + 1 >= x.size()) || (x[idx + 1].y != x[idx].y) )
            return false;
        if (visited[idx +1])
            return true;
        visited[idx+1] = true;
        idx = x[idx+1].conectedWormhole;
    }
    return true;
}

// returns true if there is infinite cycle in connection of wormholes given by vPairings
bool IsInfiniteCycle(vector<Position>& x) {
    for (unsigned int idx = 0; idx < x.size(); idx ++)
        if (TestCycle(x, idx))
            return true;
    return false;
}


int CountInfinitive(vector <int> x, int idxStart, vector <Position>& vPos) {
    if ( (idxStart == static_cast<int>(x.size()) - 1)) {
        vector <Position> vPosCur(vPos);

        for (unsigned int idx = 0; idx < vPosCur.size(); idx += 2) {
            vPosCur[x[idx]].conectedWormhole = x[idx +1];
            vPosCur[x[idx+1]].conectedWormhole = x[idx];
        }
        if (DEBUG) {
            for (int idx = 0; idx < vPosCur.size(); idx ++)
                cout << idx << " " << vPosCur[idx] << endl;
            cout << endl;
        }
        if (IsInfiniteCycle(vPosCur))
            return 1;
        return 0;
    }

    int cnt = 0;
    swap(x[idxStart-1], x[idxStart]);
    for (unsigned int idx = idxStart; idx < x.size(); idx ++) {
        swap(x[idxStart], x[idx - 1]); // return to previous position
        swap(x[idxStart], x[idx]);
        cnt += CountInfinitive(x, idxStart + 2, vPos);
    }
    return cnt;
}

// returns number of pairings of wormholes which result in infinite cycle
int TestAllPairings(vector <int>& x, vector <Position> vPos) {
    return CountInfinitive(x, 1, vPos);
}

int main() {
    freopen("wormhole.in", "r", stdin);
    freopen("wormhole.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int idx = 0; idx < n; idx ++) {
        Position p;
        scanf("%d%d", &p.x, &p.y);
        vPos.push_back(p);
    }
    sort(vPos.begin(), vPos.end(), Comp);

    for (int idx = 0; idx < n; idx ++)
        vIndex.push_back(idx);

    printf("%d\n", TestAllPairings(vIndex, vPos));

    return 0;
}
