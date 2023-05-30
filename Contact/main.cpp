/*
TASK:contact
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

struct Position {
    int val, pos, len;

    Position(int _val = 0) : val(_val) {  }

    Position& operator++() {
        val++;
        return *this;
    }

    Position operator++(int) {
        Position p = *this;
        val++;
        return p;
    }

    bool operator<(const Position& p) const {
        return (val < p.val) || ((val == p.val) && (pos > p.pos) );
    }


    friend ostream& operator<<(ostream& out, const Position& p) {
        return out << "(" << p.pos << ", " << p.val << ", " << p.len <<  ")";
    }
};

const int MAX_LEN_LINE = 80, MAX_LEN = 200000, MAX_PATTERN = 12, MAX_CNT = (1 << (MAX_PATTERN + 1) ) - 2;
vector <int> vMes;
vector <Position> vCnt(MAX_CNT);

void PrintBinary(Position& p) {
    int n = p.pos - (1 << p.len) + 2, bits;

    int nSave = n;
    for (bits = 0; n > 0; n >>= 1)  bits++;

    for (int cnt = 0; cnt < p.len - bits; cnt ++)    printf("0");

    n = nSave;
    int mask = 1 << (bits - 1);
    for (int cnt = bits; cnt > 0; cnt --) {
        printf("%d",( (n & mask) > 0 ));
        mask >>= 1;
    }
}

void InitCnt(vector<Position>& vCnt) {
    for (int idx = 0; idx < vCnt.size(); idx ++)
        vCnt[idx].pos = idx;

    for (int len = 1; len <= MAX_PATTERN; len ++)
            for (int idx = 0; idx < 1 << len; idx ++)
                vCnt[(1 << len) - 2 + idx].len = len;
}

int main() {
    if (!TEST) {
            freopen("contact.in", "r", stdin);
            freopen("contact.out", "w", stdout);
            if (DEBUG)
                freopen("contact.err", "w", stderr);
        }

    InitCnt(vCnt);
    int begin, end, freq;
    scanf("%d%d%d", &begin, &end, &freq);

    char s[MAX_LEN_LINE+1];

    while (scanf("%s", s) == 1) {
        for (int idx = 0; idx < strlen(s); idx ++)
            vMes.push_back(s[idx] == '1');
    }

    for (int idx = 0; idx < vMes.size(); idx ++)
        dbgOut << vMes[idx] << " ";
    dbgOut << endl;

    for (int len = begin; len <= end; len++) {
        int idx, curNum = 0;

        for (idx = 0; idx < len - 1; idx ++)
            curNum = (curNum << 1) | vMes[idx];

        for (; idx < vMes.size(); idx++) {
            dbgOut << idx - len + 1 << " " << idx << " ";
            curNum = ( (curNum << 1) & ~(1 << len) ) | vMes[idx];
            dbgOut << curNum << " ";
            dbgOut << ++vCnt[curNum + (1 << len)- 2]; // some shift in addition
            dbgOut << endl;
        }
    }
    sort(vCnt.begin(), vCnt.end());

    int last = INT_MAX, cntLine = 0, cnt;
    bool first = true;
    cnt = 0;

    for (vector<Position>::reverse_iterator it = vCnt.rbegin(); it != vCnt.rend(); it ++) {

        if (it->val == 0) {
            break;
        }
        if (it->val == last) {
            if (cntLine == 6) {
                cntLine = 0;
                printf("\n");
            }
            else
                printf(" ");
            PrintBinary(*it);
            cntLine++;

        }
        else {
            cnt ++;
            if (cnt == freq + 1)
                break;
            last = it->val;
            if (!first)
                printf("\n");
            else
                first = false;
            printf("%d\n", it->val);
            PrintBinary(*it);
            cntLine = 1;
        }
    }
    printf("\n");
    return 0;
}
