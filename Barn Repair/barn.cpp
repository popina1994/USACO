/*
NAME: popina
LANG: C++
TASK: barn1
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#define stop system("pause");
using namespace std;

const int boardmax = 50, stallmax = 200;
int numboard, numstall, occstall;

int x[stallmax];

void input() {
     ifstream f("barn1.in");
     f >> numboard >> numstall >> occstall;
     for (int i = 0; i < occstall; i++) 
         f >> x[i];
     f.close();
}

void ispis(int x[], int length){
     for (int i = 0; i < length; i++)
         cout << x[i] << " " << i <<endl;
     stop    
}
     

int loading() {        
    int y[stallmax];
    if (occstall == 1)
       return(occstall);                     //ako je krava 1, ne treba nista...
    int sum = 0, i ;
    sort(x, x + occstall);
    for (i = 0; i < occstall - 1 ; i++) {
        y[i] = x[i + 1] - x[i] - 1;
        sum += y[i];
    }
    --i;
    sort(y, y + i + 1 );  
    for (int boardind = 0; (boardind < numboard - 1  )  && (sum > 0);boardind++) {
          sum -= y[i  - boardind ];
          }
    return(sum + occstall);
}

void output(int exit) {
     ofstream f("barn1.out");
     f << exit << endl;
     f.close();
}

int main() {
    int result;
    input();
    result = loading();
    output(result);
}
