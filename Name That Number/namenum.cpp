/*
NAME: popina
TASK: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#define stop system("pause");

using namespace std;

string s[5000],  t[10], number;
int ssize;;


void input1() {
     t[2] = "ABC";
     t[3] = "DEF";
     t[4] = "GHI";
     t[5] = "JKL";
     t[6] = "MNO";
     t[7] = "PRS";
     t[8] = "TUV";
     t[9] = "WXY";
     ifstream f2("dict.txt");
     string str;
     int i = 0;
     while (f2 >> str) {
         s[i] = str;
         i++;
     }
     ssize = i;
     f2.close();
}

void input2() { 
     ifstream f("namenum.in");
     f >> number;
     f.close();
}
int equal(string str) {
    if (str.length() != number.length())
       return(0);
    for (int j = 0; j < str.length(); j++) {
        int k = 0;
        for (; k < 3; k++) 
            if (str[j] == t[number[j] - '0'][k])
               break;
        if (k == 3)
           return(0);
    }
    return(1);    
}        
               
void loadingoutput() {  
     ofstream f("namenum.out");  
     int counter = 0;
     for (int i = 0; i < ssize; i++) {
         if (equal(s[i])) {
            f << s[i] <<endl;
            counter++;
         }
     }
     if (!counter)
        f << "NONE" <<endl;
     f.close();
}
 
int main() {
    input1();
    input2();
    loadingoutput();
    return(0);
}    
     
     
