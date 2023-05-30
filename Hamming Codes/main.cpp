/*
NAME:djordje4
TASK:hamming
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <bitset>
#include <vector>

using namespace std;

const int nmax = 64, bmax = 8, dmax = 7;

int n, b, d;
vector<int> x;

bool hamiltonian(int n, int m) {
    bitset<bmax> x(n), y(m), z;
    z = x ^ y;
    if (int(z.count()) >= d)
        return true;
    return false;
}

int main() {
    freopen("hamming.in", "r", stdin);
    scanf("%d%d%d", &n, &b, &d);
    x.push_back(0);
    for (int i = 0; (i < (1 << bmax)) && (x.size() < n); i++ ) { //prolazi po svim brojevima
        int j;
        for (j = 0; j < x.size(); j++) // da li je i
            if (!hamiltonian(x[j], i))
                break;
        if (j >= x.size())
                x.push_back(i);
    }
    freopen("hamming.out", "w", stdout);
    for (int i = 0; i < x.size(); i++)
        if ((i >= 9) && (i % 10 == 9))
            printf("%d\n", x[i]);
        else
            if (i == x.size()-1)
                printf("%d\n", x[i]);
            else printf("%d ", x[i]);
    return 0;
}
