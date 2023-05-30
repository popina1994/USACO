/*
NAME:popina
TASK:skidesign
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <climits>

using namespace std;

const int NUM_MAX = 1000, HEIGHT_MAX = 100, HEIGHT_MIN = 0, DIFF_ALLOWED = 17;

int height[NUM_MAX], n;

inline int Abs(int x) {
    return x > 0 ? x : -x;
}

int main() {
    freopen("skidesign.in", "r", stdin);
    freopen("skidesign.out", "w", stdout);

    scanf("%d", &n);
    for (int idx = 0; idx < n; idx++)
        scanf("%d", &height[idx]);

    int minCost = INT_MAX;
    for (int heightMin = HEIGHT_MIN; heightMin <= HEIGHT_MAX - DIFF_ALLOWED; heightMin ++) {
        int cost = 0, heightMax = heightMin + DIFF_ALLOWED;

        for (int idx = 0; idx < n; idx ++) {
            int difference = 0;
            if (height[idx] > heightMax)
                difference = height[idx] - heightMax;
            else if (height[idx] < heightMin)
                difference = heightMin - height[idx];

            if (difference > 0)
                cost += difference * difference;
        }
        minCost = min(minCost, cost);
    }

    printf("%d\n", minCost);
    return 0;
}
