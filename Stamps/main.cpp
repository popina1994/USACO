/*
TASK: stamps
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
#include <cfloat>
#include <set>
#include <utility>

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

    template <typename T>
    friend DebugOutput& operator<<(DebugOutput& d, const vector<T>& v) {
        if (DEBUG && !TEST) {
            for (unsigned idx = 0; idx < v.size(); idx ++)
                cerr << "idx:" << idx << " val: " << v[idx] << endl;
        }
        return d;
    }

    template <typename T>
    friend DebugOutput& operator<<(DebugOutput& d, const deque<T>& dq) {
        if (DEBUG && !TEST) {
            for (unsigned idx = 0; idx < dq.size(); idx ++)
                cerr << "idx:" << idx << " val: " << dq[idx] << endl;
        }
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

struct Stamps {
    // val - how much money is in envelope, cnt - how much bills
    int val, cnt;

    Stamps(int _val = -1, int _cnt = INT_MAX) : val(_val), cnt(_cnt) {}

    friend ostream& operator<<(ostream& out, const Stamps& s) {
        return out << "(" << s.val << " " << s.cnt << ")";
    }
};

const int MAX_STAMPS = 200, MAX_DIFF_STAMPS = 50, MAX_DIFFERENCE = 10000;
vector <int> vDiff(MAX_DIFF_STAMPS);
int main() {
    if (!TEST) {
            freopen("stamps.in", "r", stdin);
            freopen("stamps.out", "w", stdout);
            if (DEBUG)
                freopen("stamps.err", "w", stderr);
        }

    int maxStamps, n;
    scanf("%d%d", &maxStamps, &n);

    vDiff.resize(n);
    for (int idx = 0; idx < vDiff.size(); idx ++)
        scanf("%d", &vDiff[idx]);
    sort(vDiff.begin(), vDiff.end());

    dbgOut << vDiff << endl;



    deque <Stamps> dqVals;
    int curVal = 1;

    dqVals.push_back(Stamps(0, 0));
    while (true) {
        bool found = false;
        dqVals.push_back(Stamps(curVal));
        for (vector<int>::reverse_iterator it = vDiff.rbegin(); it != vDiff.rend(); it ++)
            if ( (curVal- *it >= 0) && (dqVals[curVal - *it- dqVals.front().val].cnt < maxStamps ) ){
                dqVals[curVal-dqVals.front().val] = \
                Stamps(curVal, min(dqVals[curVal - *it- dqVals.front().val].cnt + 1, dqVals[curVal-dqVals.front().val].cnt));
                found = true;
        }

        if (!found) break;
        if (dqVals.size() == MAX_DIFFERENCE + 1)
            dqVals.pop_front();
        curVal++;
    }
    printf("%d\n", dqVals.back().val - 1);

    dbgOut << dqVals << endl;
	return 0;
}
