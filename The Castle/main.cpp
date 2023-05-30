/*
NAME:djordje4
LANG:C++
TASK:castle
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int nmax=101, mmax=101;

int n, m;
int x[nmax][mmax], z[nmax][mmax];
int y[4]= {1, 2, 4, 8};
int xind[4] = {0, -1, 0, 1};
int yind[4] = {-1, 0, 1, 0};
int xind2[2] = {-1, 0};
int yind2[2] = {0, 1};

void ispis() {
    for (int i = 0; i <= 2*n; i++) {
        for (int j = 0; j <= 2*m; j++)
            printf("%d ", x[i][j]);
        printf("\n");
    }
    printf("\n");
}

void ispis2() {
    for (int i = 0; i <= 2*n; i++) {
        for (int j = 0; j <= 2*m; j++)
            printf("%d ", z[i][j]);
        printf("\n");
    }
    printf("\n");
}

void divide(int i, int j, int t) {
    int xi, xj, curt = t;
    //oduzimam t elemente niza t redom, dok t != 0
    xi = 2 * i - 1;
    xj = 2 * j - 1;
    x[xi][xj] = 0;

    for (int counter = 3; counter >= 0; counter--) {
        if (curt - y[counter] >= 0)
            curt -= y[counter];
        //ako je broj veci oduzima ga i dodaje u matricu zidove
        else
            x[xi+xind[counter]][xj+yind[counter]] = 0;
    }
}

bool kraj(int i, int j) {
    return(!((i > 0) &&  (i < 2 *n) && (j > 0) && (j < 2*m)));
}

void input() {
    memset(z, 0, sizeof(z));
    freopen("castle.in", "r", stdin);
    scanf("%d %d", &m, &n);
    for (int i = 0; i <= 2*n; i++)
        for (int j = 0; j <= 2*m; j++)
            x[i][j] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int t;
            scanf("%d", &t);
            divide(i, j, t);
            //pravi matricu od ucitanog clana
        }
    for (int i = 0; i <= 2*n; i++)
        x[i][0] = x[i][2*m] = 1;
    for (int i = 0; i <= 2*m; i++)
        x[0][i] = x[2*n][i] = 1;
}

int dfs(int i, int j, int counter) {
    int sum = 0;
    if (!kraj(i, j) && x[i][j] == 0 ) {
        x[i][j] = counter;
        sum++;
        for (int k = 0; k < 4; k++) {
            int tempi = i+xind[k], tempj = j+yind[k];
            if (x[tempi][tempj] == 0)
                sum += dfs(i+2*xind[k], j+2*yind[k], counter);
        }
    }
    return sum;
}

void dfssize(int i, int j, int size, int counter) {
    if ((x[i][j] == counter) && (z[i][j] == 0) && !kraj(i, j)) {
        z[i][j] = size;
        for (int k = 0; k < 4; k++)
            dfssize(i+2*xind[k], j+2*yind[k], size, counter);
    }
}

void numroom(int &numroom, int &maxsize) {
    int counter = 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (x[2*i+1][2*j+1] == 0) {
                int tempsize;
                counter++;
                tempsize = dfs(2*i+1, 2*j+1, counter);
                if (counter != tempsize)
                    dfssize(2*i+1, 2*j+1, tempsize, counter);
                if (tempsize > maxsize)
                    maxsize = tempsize;
            }
    numroom = counter-1;
}

bool wall(int i, int j) {
    return (!(kraj(i,j) && (x[i][j] == 1)));
}

void dfsroom(int &posi, int &posj, int &module, char &dir) {
    int maxroom = 0, posx, posy, it, jt;
    char ksol;
    for (int j = 0; j < m; j++)
        for (int i = n-1; i >= 0; i--)
            for (int k = 0; k < 2; k++) {
                int tempi, tempj, it = 2 *i+1, jt = 2*j+1;
                tempi = it +2*xind2[k];
                tempj = jt + 2*yind2[k];
                if ((x[it+xind2[k]][jt+yind2[k]]== 1)&& !kraj(tempi, tempj)&&!(kraj(it,jt))&& x[it][jt] != x[tempi][tempj] &&((z[it][jt]+z[tempi][tempj])> maxroom)) {
                    posx = i+1;
                    posy = j+1;
                    maxroom = z[it][jt]+z[tempi][tempj];
                    if (k == 0)
                        ksol = 'N';
                    else ksol = 'E';

                }
            }
    module = maxroom;
    posi = posx;
    posj = posy;
    dir = ksol;
}

int main() {
    int numberroom, maxsize = 0, i, j, maxi = 0;
    char dir;
    input();
    numroom(numberroom, maxsize);
    dfsroom(i, j, maxi, dir);
    freopen("castle.out", "w", stdout);

    printf("%d\n%d\n%d\n%d %d %c\n", numberroom, maxsize, maxi, i, j, dir);
    return 0;
}
