/*
NAME:popina
TASK:fracdec
LANG:C++
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int numerator, denominator, n, d;

const int DENOMINATOR_MAX = 100000;

struct DecimalPart {
    int num, idx;
    DecimalPart(int _num) : num(_num), idx(-1) {}

    friend bool operator<(const DecimalPart& dp1, const DecimalPart& dp2) {
        return dp1.num < dp2.num;
    }

    friend bool operator==(const DecimalPart& dp1, const DecimalPart& dp2) {
        return dp1.num == dp2.num;
    }
};

vector <int> v; // contains number of decimal representation
set <DecimalPart> memeMap;

inline int FracPart(int n, int d) {
    return n - d * (n / d);
}

int charLine = 0;



int NumDigits(int n) {
    if (n == 0)
        return 1;
    int cnt = 0;
    while (n > 0) {
        n /= 10;
        cnt++;
    }
    return cnt;
}

bool NonRepeat(int n) {
    while ( (n > 1) && ( (n % 2) == 0))
        n /= 2;
    while ( (n > 1) && ( (n % 5) == 0) )
        n /= 5;

    return n == 1;
}

void PrintChar(char c) {
    if ( (charLine % 76) == 0)
        printf("\n");
    printf("%c", c);
    charLine++;
}

int main() {
    freopen("fracdec.in", "r", stdin);
    freopen("fracdec.out", "w", stdout);

    scanf("%d%d", &numerator, &denominator);

    n = numerator;
    d = denominator;

    printf ("%d.", n / d);
    charLine += NumDigits(n / d) + 1; // .
    n = 10 * (n - d * (n / d) );
    if ( (numerator % denominator) == 0)
        printf ("%d", 0);
    else {
        DecimalPart dp(n);
        dp.idx = 0;
        while (memeMap.find(dp) == memeMap.end()) {
            memeMap.insert(dp);
            v.push_back(n / d);
            n = 10 * (n - d * (n / d) );
            dp.idx++;
            dp.num = n;
        }
        // last modulos are the same
        // lastIdx is the one who repeats

        int seqBegin = memeMap.find(DecimalPart(n))->idx;
        for (int idx = 0; idx != seqBegin; idx++) {
            printf ("%d", v[idx]);
            charLine++;
        }

        if (!NonRepeat(denominator))  { // exist nonzero repeating
            PrintChar('(');
            for (int idx = seqBegin; idx < v.size(); idx++) {
                PrintChar(v[idx] + '0');

            }
            PrintChar(')');
        }
    }
    printf("\n");
    return 0;
}
