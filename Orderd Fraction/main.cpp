/*
ID:djordje4
PROG: frac1
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int nmax = 160;

int n;

int gcd(int a, int b){
    int d, x = a, y = b;
    while (x % y != 0){
        d = x % y;
        x = y;
        y = d;
    }
    return y;
}

struct fraction{
    int n, d;
    fraction (){}
    fraction(int x, int y){
        n = x;
        d = y;
    }
    fraction(const fraction &f){
        d = f.d;
        n = f.n;
    }

    void set(int x, int y){
        n = x;
        d = y;
    }


    void print(){
    printf("%d/%d\n", n, d);
    }

    bool operator < (const fraction &f)const{
        return (f.d*n-d*f.n < 0);
    }
    void skrati();
    bool operator== (const fraction &f)const {
            return (f.d*n-d*f.n == 0);
    }
};

void fraction::skrati(){
    int c;
    c = gcd(n, d);
    n /= c;
    d /= c;
}
int main(){
    vector <fraction> x;
    set <fraction> s;
    fraction t;
    freopen("frac1.in", "r", stdin);
    freopen("frac1.out", "w", stdout);
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++ ){
        for (int j = 0; j <= i; j++){
            t.set(j, i);
            t.skrati();
            if (s.count(t) == 0){
                s.insert(t);
                x.push_back(t);
            }
        }
    }
    sort(x.begin(), x.end());
    for (int i = 0; i < x.size(); i++ ){
        x[i].print();
    }
    scanf("%d", &n);
    return 0;
}
