/*
NAME: popina
TASK: dualpal
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <stack>
#define stop system("pause");
using namespace std;

int number, biggerthan;

void input() {
     ifstream f("dualpal.in");
     f >> number >> biggerthan;
     f.close();
}

void tentobase(int base, int n, int s[]) {
     int num = n, reminder;
     stack <int> mystack;
     while (n != 0) {
           reminder = n % base;
           mystack.push(reminder);
           n /= base;
     }
     s[0] = mystack.size();
     int i = 1;
     while (!mystack.empty()) {
           s[i] = mystack.top();
           mystack.pop();
           i++;
     }
}

int palindrome(int s[]) {
    for (int i = 1; i <= s[0] / 2; i++) 
        if (s[i] != s[s[0] - i +1])
           return(0);
    return(1);
}

int twopalindrome(int x) {
    int i = 0;
    for (int j = 2; j <= 10; j++) {
        int s[50];
        tentobase(j, x, s);
        i += palindrome(s);
        if (i == 2)
           return(1);
    }
    return(0);
} 
          
void loadingoutput() {
     int i = 0;
     ofstream f("dualpal.out");
     for (int j  = biggerthan + 1; i < number; j++)
           if (twopalindrome(j)) {
              f << j << endl;
              i++;
           }
     f.close();
}
           
int main() {
    input();
    loadingoutput();
    return(0);
}
