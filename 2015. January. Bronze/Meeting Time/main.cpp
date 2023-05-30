#include <iostream>
#include <cstdio>
#include <queue>
#include <set>

using namespace std;

const int MAX_FIELDS = 100;

int x[MAX_FIELDS][MAX_FIELDS] = {0}, y[MAX_FIELDS][MAX_FIELDS] = {0};

int n, numEdge;


void DFS(int x[][MAX_FIELDS], int n, int field, set <int>& s, int sum) {
    for (int idx = 0; idx < n; idx ++) {
        if (field == n - 1)
            s.insert(sum);
        if (x[field][idx] > 0)
            DFS(x, n, idx, s, sum + x[field][idx]);
    }
}

int main() {
    freopen("meeting.in", "r", stdin);
    freopen("meeting.out", "w", stdout);

    cin >> n >> numEdge;

    for (int i = 0; i < numEdge; i ++) {
        int row, col;
        cin >> row >> col;
        cin >> x[row - 1][col - 1] >> y[row - 1][col - 1];
    }

    set <int> s1, s2;
    DFS(x, n, 0, s1, 0);
    DFS(y, n, 0, s2, 0);

    bool exist = false;

    for (auto it = s2.begin(); it != s2.end(); it++)
        if (s1.find(*it) != s1.end()) {
            cout << *it << endl;
            exist = true;
            break;
        }

    if (!exist)
        cout << "IMPOSSIBLE" << endl;

    return 0;
}
