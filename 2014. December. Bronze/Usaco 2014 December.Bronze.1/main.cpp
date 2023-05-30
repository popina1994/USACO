#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

struct Pos {
    int x, y;

public:
    Pos(int _x = 0, int _y = 0) : x(_x), y(_y) {}

    void SetX(int _x) {
        x = _x;
    }
    void SetY(int _y) {
        y = _y;
    }

};


int ManhatanDis(const Pos& p1, const Pos& p2)  {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

constexpr int MAX_CHECK = 100000;

int meme[MAX_CHECK] = { 0 };

Pos pos[MAX_CHECK];

int n;

int main() {
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);
    // reading of table
    scanf("%d", &n);

    for (int idx = 0; idx < n; idx ++)
    scanf("%d%d", &pos[idx].x, &pos[idx].y);

    meme[0] = 0;

    for (int idx = 1; idx < n; idx ++)
        meme[idx] =  meme[idx - 1] + ManhatanDis(pos[idx], pos[idx-1]);

    int minVal = meme[n - 1];

    for (int idx = 1; idx < n - 1; idx ++)
        minVal = min(minVal, meme[n - 1] - (ManhatanDis(pos[idx], pos[idx -1]) + ManhatanDis(pos[idx], pos[idx + 1]) ) + ManhatanDis(pos[idx -1], pos[idx +1]) );

    printf("%d\n", minVal);
    return 0;
}
