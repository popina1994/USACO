#include <iostream>
#include <climits>
#include <set>

using namespace std;

const int MAX_CITIES = 10000, NUM_DEST = 500, CITIES_ON_ROUTE = 500;

int cityA, cityB, n;

int curRoute[MAX_CITIES];

int city[NUM_DEST][CITIES_ON_ROUTE];
int cost[NUM_DEST];

int AOnRoute[NUM_DEST], BOnRoute[NUM_DEST], numCitiesOnRoute[NUM_DEST];

int main() {
    freopen("cowroute.in", "r", stdin);
    freopen("cowroute.out", "w", stdout);

    cin >> cityA >> cityB >> n;


    for (int idx = 0; idx < n; idx ++ ) {
        cin >> cost[idx] >> numCitiesOnRoute[idx];
        AOnRoute[idx] = -1;
        BOnRoute[idx] = -1;

        for (int i = 0; i < numCitiesOnRoute[idx]; i++) {
            cin >> city[idx][i];
            if (city[idx][i] == cityA)
                AOnRoute[idx] = i;
            if (city[idx][i] == cityB)
                BOnRoute[idx] = i;
        }
    }
    int costMin = INT_MAX;

    for (int i = 0; i < n; i++)
        if (AOnRoute[i] != -1) {
            for (int j = 0; j < n; j ++)
                if ( (i != j) && BOnRoute[j]) {
                    set <int> s;
                    for (int k = AOnRoute[i] + 1; k < numCitiesOnRoute[i]; k ++)
                        s.insert(city[i][k]);
                    for (int k = 0; k < BOnRoute[j]; k ++)
                        if (s.find(city[j][k]) != s.end())
                            costMin = min(costMin, cost[i] + cost[j]);
                    }
                else if ( (i == j) && (AOnRoute[i] < BOnRoute[j]))
                    costMin = min(costMin, cost[i]);
                }
    if (costMin == INT_MAX)
        cout << -1;
    else
        cout << costMin;

    cout << endl;


    return 0;
}
