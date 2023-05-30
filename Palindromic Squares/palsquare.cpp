/*
NAME: popina
LANG: C++
TASK: palsquare
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#define stop system("pause");

using namespace std;

int base ;

void input() {
ifstream f("palsquare.in");
f >> base;
f.close();
}

void basetoten(int s[], int &number) {
     int current = 1, num = 0;
     for (int i = s[0]; i > 0; i--) {
          num += s[i] * current;
     current *= base;
     }
     number = num;
}

void tentobase(int s[], int number) {
     int num , remain = 0;
     stack <int> mystack;
     num = number;
     for (int i = 1; num != 0; i++) {
         remain = num % base;
         mystack.push(remain);
         num /= base;
     }
     s[0] = mystack.size();
     int i = 1;
     while (!mystack.empty()) {
           s[i] = mystack.top();
           mystack.pop();
           i++;
     }

}

int palindrom(int s[]) {
    for (int i = 1; i <= (s[0] / 2); i++) {
        if (s[i] != s[s[0] - i + 1]) 
        return(0); 
    }

    return(1); 
}

char inttochar(int x) {
     if (x <= 9){
        return(static_cast<char>('0' + x));}
     return(static_cast<char>('A' + x - 10));
}

void loadingoutput() {
ofstream f("palsquare.out"); 
    for (int i = 1; i <= 300; i++) {
        int x;
        int s[50], s1[50] ;
        tentobase(s, i * i);
        if (palindrom(s)) {
           tentobase(s1, i);
        for (int j = 1; j <= s1[0]; j++)
        f << inttochar(s1[j]);
        f << " ";
        for (int j = 1; j<= s[0]; j++)
            f << inttochar(s[j]);
        f << endl;
        }
    }
    f.close();
}

int main() {
input();
loadingoutput();
return(0);
}
