/*
NAME:popina
TASK:combo
LANG:C++
*/

#include <iostream>
#include <cstdio>
#include <set>

#define DEBUG 0

using namespace std;

const int NUM_TUPLE = 3;
const int PRECALC[5] = { -2, -1, 0, 1, 2};

struct Triplet {
    int x[NUM_TUPLE];

    explicit Triplet() {}
    explicit Triplet(int a, int b, int c) {
        x[0] = a;
        x[1] = b;
        x[2] = c;
    }

    friend bool operator<(const Triplet& t1, const Triplet& t2) {
        for (int idx = 0; idx < NUM_TUPLE; idx ++)
            if (t1.x[idx] < t2.x[idx])
                return true;
            else if (t1.x[idx] > t2.x[idx])
                return false; // appropriate number is bigger

        return false; // equal
    }

    Triplet& operator--() {
        for (int idx = 0; idx < NUM_TUPLE; idx ++)
            x[idx]--;
        return *this;
    }

    friend bool operator==(const Triplet& t1, const Triplet& t2) {
        for (int idx = 0; idx < NUM_TUPLE; idx ++)
            if (t1.x[idx] != t2.x[idx])
                return false;

        return true; // everything is equal
    }

    friend istream& operator>>(istream& in, Triplet& t) {
        for (int idx = 0; idx < NUM_TUPLE; idx ++)
            in >> t.x[idx];
        return in;
    }

    friend ostream& operator<< (ostream& out, const Triplet& t) {
        for (int idx = 0; idx < NUM_TUPLE; idx ++)
            out << t.x[idx] << " ";
        return out;
    }

    bool Near(const Triplet& t, int n) const {
        for (int idx = 0; idx < 3; idx ++) {
            int cur = false;

            for (unsigned int i = 0; i < sizeof(PRECALC) / sizeof(PRECALC[0]); i ++)
                if ( ( (t.x[idx] + PRECALC[i] + n) % n) == x[idx])
                    cur = true;

            if (!cur)
                return false;
        }
        return true;
    }
};


int n;

Triplet lockJohns, masterLock;

int main() {
    set <Triplet> s;
    freopen("combo.in", "r", stdin);
    freopen("combo.out", "w", stdout);

    scanf ("%d", &n);
    cin >> lockJohns;
    cin >> masterLock;
    --lockJohns;
    --masterLock;

    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            for (int k = 0; k < n; k ++) {
                if (lockJohns.Near(Triplet(i, j, k), n)) {
                    if (DEBUG)
                        cout << Triplet(i, j, k) << endl;
                    s.insert(Triplet(i, j, k));
                }
                if (masterLock.Near(Triplet(i, j, k), n)) {
                    if (DEBUG)
                        cout << Triplet(i, j, k) << endl;
                    s.insert(Triplet(i, j, k));
                }
            }
    /*if (DEBUG) {
        cout << DEBUG << endl;
        for (auto it = s.begin(); it != s.end(); it++)
            cout << *it << endl;
    }*/
    cout << s.size() << endl;


    return 0;
}
