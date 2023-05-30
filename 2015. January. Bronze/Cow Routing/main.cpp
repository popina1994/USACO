#include <iostream>
#include <cstdio>
#include <climits>

using namespace std;

int cityA, cityB, n, minCost = INT_MAX;

int main() {
    freopen("cowroute.in", "r", stdin);
    freopen("cowroute.out", "w", stdout);

    cin >> cityA >> cityB >> n;

    for (int i = 0; i < n; i ++) {
        int cost, numCitiesOnRoute, tmp;
        bool ABeforeB = false, exist = false;

        cin >> cost >> numCitiesOnRoute;
        for (int idx = 0; idx < numCitiesOnRoute; idx++) {
            cin >> tmp;
            if (cityA == tmp)
                ABeforeB = true;
            else {
                if ( (cityB == tmp) && ABeforeB) {
                    exist = true;

                }
            }
        }

        if (exist)
            minCost = min(minCost, cost);
    }
    if (minCost == INT_MAX)
        cout << -1;
    else
        cout << minCost;
    cout << endl;

    return 0;
}
