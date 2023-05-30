/*
NAME:popina
TASK:runround
LANG:C++
*/

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

unsigned int m;
int num[10];

void convert(unsigned int x, int m[], int &length) {
    unsigned int temp = x, counter = 0;
    while (temp != 0) {
        m[counter++] = temp % 10;
        temp /= 10;
    }
    for (unsigned int i = 0; i < counter / 2; i++){
        unsigned int temp, j = counter - 1 - i;
        temp = m[i];
        m[i] = m[j];
        m[j] = temp;
        m[j] = temp;
    }
    length = counter;
}

void ispis(int x[], int length){
    for (int i = 0; i < length; i++)
        cout << x[i] << " ";
    cout << endl;
}

bool unique(int x[], int length){
    memset(num, 0, sizeof(num));
    for (int i = 0; i < length; i++)
        if (++num[x[i]] > 1)
            return false;
    return true;
}

int main() {
    freopen("runround.in", "r", stdin);
    scanf("%d", &m);
    int length;
    bool found = false; // oznacava da li je nadjen runaround broj
    int x[9], y[9];
    unsigned int  i = m;
    while (!found) {
        memset(y, 0, sizeof(y));
        i++;
        convert(i, x, length); // pretvara bro j u niz cifara
        int indexed = 0, indexer = 0;
        for (int k = 0; k < length; k++){
            indexer = (indexer + x[indexer]) % length;
            if (y[indexer] != -1)
                indexed ++;
            y[indexer] = -1;
        }

        if ((indexed == length) && unique(x, length))
            found = true;
    }
    freopen("runround.out", "w", stdout);
    printf("%u\n", i);
    return 0;
}
