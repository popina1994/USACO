/*
NAME: popina
TASK:crypt1
LANG: C++
*/
#include <iostream>
#include <fstream>
#define stop system("pause");
using namespace std;

int x[9], n;

void input() {
    ifstream f("crypt1.in");
    f >> n;
    for (int i = 0; i < n; i++) {
        f >> x[i];
;    }
}

int threedigit(int a, int b, int c){
    return(100 * a + 10 * b + c);
}

int exist(int dig){
    for (int i = 0; i < n; i++)
        if (x[i] == dig)
            return(1);
    return (0);
}

int corectdigit(int x){
    int currx = x;
    while (currx != 0)
        if(exist(currx % 10))
            currx /= 10;
        else return(0);
    return(1);
}

int correct(int i, int j, int k, int l, int m){
    int abc ;
    abc = threedigit(i, j, k);

    int x, y;
    x = abc * l;
    if (!corectdigit(x) || x > 999)
        return(0);
    y = abc * m;
    if (!corectdigit(y) || y > 999)
        return(0);
    int z = x * 10 + y;
    if (!corectdigit(z) || z > 9999)
        return(0);
    return(1);
    }
int loading() {
    int result = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                for (int l = 0; l < n; l++)
                    for (int m = 0; m < n; m++)
                        result += correct(x[i], x[j], x[k], x[l], x[m]);
    return(result);
}

void output(int exit){
    ofstream f("crypt1.out");
    f  << exit << endl;
    f.close();
}

int main() {
    int result;
    input();
    result = loading();
    output(result);
    return(0);
}
