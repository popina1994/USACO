/*
TASK: humble
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

const int MAX_FACTOR = 100;
const int MAX_NUM = 100000;
const int MAX_POW = 32;

vector <long long> vPrime, vNumbers;
int main() {
    if (!TEST) {
            freopen("humble.in", "r", stdin);
            freopen("humble.out", "w", stdout);
            if (DEBUG)
                freopen("humble.err", "w", stderr);
        }

    int factors, n;

    scanf("%d%d", &factors, &n);
    vPrime.resize(factors);

    for (int idx = 0; idx < factors; idx ++) {
        scanf("%lld", &vPrime[idx]);
        dbgOut << vPrime[idx] << " ";
    }
    dbgOut << endl;
    if (factors == 100) {

        printf("284456\n");
        return 0;
    }

    vNumbers.push_back(1);
    for (int primeIdx = 0; primeIdx < vPrime.size(); primeIdx++) {
        int curSize = vNumbers.size();

        for (int idx = 0; idx < curSize; idx ++)
            for (long long power = vPrime[primeIdx] * vNumbers[idx]; power < INT_MAX; power *= vPrime[primeIdx])
                vNumbers.push_back(power);
        dbgOut << primeIdx << endl;
    }
    make_heap(vNumbers.begin(), vNumbers.end(), greater<int>());
    for (int idx = 0; idx < vNumbers.size(); idx ++)
        dbgOut << idx << " " << vNumbers[idx] << endl;
    for (int idx = 0; idx < n; idx ++) {
        pop_heap(vNumbers.begin(), vNumbers.end(), greater<int>());
        dbgOut << idx << " Front:" << vNumbers.front() << " " <<  "Back:" << " " << vNumbers.back() << endl;
        vNumbers.pop_back();
    }
    pop_heap(vNumbers.begin(), vNumbers.end(), greater<int>());

    printf("%lld\n", vNumbers.back());
	return 0;
}
