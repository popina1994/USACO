/*
NAME: popina
LANG : C++
TASK: transform
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#define stop system("pause");

using namespace std;

const int  nmax = 10;

int x[nmax][nmax], z[nmax][nmax], n;

void ispis(int x[][nmax]) {
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) 
             cout << x[i][j] <<  "  "; 
         cout << endl;
     }
     cout <<"kraj" << endl;
}
void input() {
     ifstream f("transform.in");
     f >> n;
     string s;
     for (int i = 0; i < n; i++) {
         f >> s;
         for (int j = 0; j < n; j++) 
             x[i][j] = (s[j] == '@');
     }
     for (int i = 0; i < n; i++) {
         f >> s;
         for (int j = 0; j < n; j++) 
             z[i][j] = (s[j] == '@');
     }
     f.close();
}

void ninetyrot(int x[][nmax], int y[][nmax]) {
     for (int i = 0; i < n; i++) 
         for (int j = 0; j < n; j++)
             y[i][j] = x[n - 1 - j][i];
}      

void reflection(int x[][nmax], int y[][nmax]) {
     for (int i = 0; i < n; i++) 
         for (int j = 0; j < n; j++) 
             y[i][j] = x[i][n  - j - 1];
}

int equal(int x[][nmax], int y[][nmax]) {
     for (int i = 0; i < n; i++) 
         for (int j = 0; j < n; j++)
             if (x[i][j] != y[i][j])
                return(0);
     return(1);
} 

int loading() {
     int currentmin = 7;
     for (int i = 0; i < 2; i++) {
         int y[nmax][nmax] ;
         memcpy(y, x, sizeof(x));
         if (i) reflection(x, y);
         for (int  j = 0; j < 4; j++) {
             int t[nmax][nmax];
             memcpy(t,y,sizeof(y));
             cout << i << " " << j<<endl;
             ninetyrot(y, t);
             memcpy(y,t,sizeof(t));
             if (equal(y, z)) {
                if (i == 0) 
                   currentmin = min(currentmin, j + 1 + (j == 3) * 2);
                else currentmin = min(currentmin, 5 - (j == 3));
                
             }
         }
     }
     return (currentmin);
}

void output(int x) {
     ofstream f("transform.out");
     f << x << endl;
}

int main(){
    int exit;
    input();
    exit = loading();
    output(exit);
    return(0);
}
