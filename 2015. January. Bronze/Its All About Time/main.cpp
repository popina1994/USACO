#include <iostream>
#include <map>

using namespace std;

const int MAX_BASE = 15000, MIN_BASE = 10, MAX_NUM = 999, MIN_NUM = 100;

int Base(int base, int number) {
    int pow = 1, num = 0;
    while (number > 0) {
        num += pow * (number % 10);
        pow *= base;
        number /= 10;
    }
    return num;
}

int numTest;

int x[MAX_NUM + 1][MAX_BASE+1] = {0};

void Generate() {
    for (int row = MIN_NUM; row <= MAX_NUM; row++ )
        for (int col = MIN_BASE; col <= MAX_BASE; col++)
            x[row][col] = Base(col, row);
}

void BaseSearch(int n1, int n2) {

}

int main() {
    freopen("whatbase.in", "r", stdin);
    freopen("whatbase.out", "w", stdout);
    Generate();

    cin >> numTest;

    for (int i = 0; i < numTest; i ++) {
        int n1, n2, cnt1 = MIN_BASE, cnt2 = MIN_BASE;
        cin >> n1 >> n2;

        while (true) {
            if (x[n1][cnt1] == x[n2][cnt2]) {
                cout << cnt1 << " " << cnt2 << endl;
                break;
            }
            else if (x[n1][cnt1] < x[n2][cnt2])
                cnt1++;
            else
                cnt2++;
            if ( (cnt1 > MAX_BASE) || (cnt2 > MAX_BASE))
                break; // it won't be needed
        }
    }
    return 0;
}
