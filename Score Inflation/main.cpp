/*
TASK:inflate
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
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;

    typedef CoutType& (*StandardEndLine)(CoutType&);

    // define an operator<< to take in std::endl
    friend DebugOutput& operator<<(DebugOutput& d, const StandardEndLine& manip) {
        if (DEBUG && !TEST)
            cerr << manip;
        return d;
    }
} dbgOut;


const int MAX_POINT = 10000;

struct Problem {
    int time, points;

    Problem(int _time = -1, int _points = -1) : time(_time), points(_points) {}

    friend ostream& operator<<(ostream& out, const Problem& p) {
        return out << "(" << p.time << ", " << p.points << ")";
    }
};

// max number of points which is possible to have in time limit v[t]
vector <int> vMax(MAX_POINT);
vector <Problem> vProblem(MAX_POINT);

int main() {
    if (!TEST) {
            freopen("inflate.in", "r", stdin);
            freopen("inflate.out", "w", stdout);
            if (DEBUG)
                freopen("inflate.err", "w", stderr);
        }

    int timeLimit, problems;

    scanf("%d%d", &timeLimit, &problems);
    vMax.resize(timeLimit + 1);
    vProblem.resize(problems);

    for (int idx = 0; idx < problems; idx ++) {
        scanf("%d%d", &vProblem[idx].points, &vProblem[idx].time);
        dbgOut << vProblem[idx] << endl;
    }
    vMax[0] = 1;

    for (int idxProb = 0; idxProb < vProblem.size(); idxProb++)
        for (int time = 0; time < vMax.size() - 1; time ++) {

            if (((time + vProblem[idxProb].time) <= vMax.size() )&& (vMax[time] != 0) &&
                (vMax[time] + vProblem[idxProb].points) > vMax[time + vProblem[idxProb].time])
                vMax[time + vProblem[idxProb].time] = vMax[time] + vProblem[idxProb].points;
        }

    int maxPoints = -1;
    for (int idx = 1; idx < vMax.size(); idx ++)
        maxPoints = max(maxPoints, vMax[idx]);

    printf("%d\n", maxPoints - 1);

	return 0;
}
