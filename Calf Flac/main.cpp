/*
NAME: popina
TASK:calfflac
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
#define stop system("pause");
using namespace std;

const int nmax = 20000;

string sreal;char s[nmax];
int n, y[nmax], x[nmax], z[nmax];

void input() {
    ifstream f("calfflac.in");
    string cur;
    sreal ="";
    getline(f,cur);
    while (! f.eof()) {
        sreal += cur + '\n';
        getline(f,cur);
    }
    f.close();
}

void srealtos(){
    int j = 0;
    for (int i = 0; i < sreal.length(); i++)
        if (sreal[i] <= 'z' && sreal[i] >= 'a' || sreal[i] <= 'Z' && sreal[i] >= 'A'){
            s[j] = tolower(sreal[i]);

            z[j] =  i;
            ++j;
        }
    s[j] ='\0';
    n = j;
}

void formx(){
    x[0] = 1;
    for (int i = 1; i < n; i++){
            if ((i - x[ i - 1] - 1 >= 0) && (s[i] == s[i-x[i-1]-1]))
                x[i] = x[i-1] + 2;
            else  if (y[i-1] == x[i-1] && s[i] == s[i-1])
                        x[i] = x[i-1] + 1;
                    else x[i] = 1;
        }
}

void equalarray() {
    y[0] = 1;
    for (int i = 1; i < n; i++)
            if (s[i] == s[i - 1])
                y[i] = y[i-1] + 1;
            else y[i] = 1;
}
void print(int x[]){
    for (int i = 0; i < n; i++)
        cout << x[i] << " ";
}
void loading(char sout[], int &length){
    int max = 0, indexmax = -1;
    srealtos();
    equalarray();
    formx();
    cout << s;
    for (int i = 0; i < n; i++)
        if (x[i] > max){
            max = x[i];
            indexmax = i;
        }
    int j = 0;
    for (int i = z[indexmax - max + 1]; i <= z[indexmax] ; i++){
        sout[j++] = sreal[i];
    }
    sout[j] = '\0';
    length = max;
}

void output(int exit, char exits[]){
    ofstream f("calfflac.out");
    f << exit << endl << exits << endl;
    f.close();
}

int main(){
    char s[2000]; int length;
    input();
    loading(s, length);
    output(length, s);
    return(0);
}

