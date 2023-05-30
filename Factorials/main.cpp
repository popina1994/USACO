/*
TASK: fact4
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

const long long POW_5 = 10000000;

int main() {
    if (!TEST) {
            freopen("fact4.in", "r", stdin);
            freopen("fact4.out", "w", stdout);
            if (DEBUG)
                freopen("fact4.err", "w", stderr);
        }
    long long n, sol = 1;
    scanf("%lld", &n);
    for (long long mul = 1; mul <= n; mul ++)  {

        sol *= mul;
        while (sol % 10 == 0)
            sol /= 10;
        if (sol > POW_5)
            sol %= 10;
        dbgOut << sol << " " << mul << endl;
    }
    printf("%lld\n", sol % 10);
	return 0;
}
