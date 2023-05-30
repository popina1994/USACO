#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_NUM = 50000;

struct Interval {
    int x, y, r, beginTime, endTime;

    void CalculateTime() {
        beginTime = (0 - x) * r;
        endTime = (1 - x) * r;

    }

    bool operator<(const Interval& i) const {
        return y < i.y;
    }

    bool operator==(const Interval& i) const {
        return y == i.y;
    }

    friend istream& operator>>(istream& in, Interval& i) {
        return in >> i.x >> i.y >> i.r;
    }

};



Interval timeInterval[MAX_NUM];

int n;

bool CompBegin(const Interval& i1, const Interval& i2) {
    return i1.beginTime < i2.beginTime;
}

bool CompEnd(const Interval& i1, const Interval& i2) {
    return i1.endTime < i2.endTime;
}

int main() {
    freopen("stampede.in", "r", stdin);
    freopen("stampede.out", "w", stdout);

    cin >> n;

    for (int idx = 0; idx < n; idx ++) {
        cin >> timeInterval[idx];
        timeInterval[idx].CalculateTime();

    }
    sort(timeInterval, timeInterval + n, CompBegin0);



    return 0;
}
