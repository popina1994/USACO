/*
NAME:djordje4
TASK:prefix
LANG:C++
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;

const int LEN_MAX = 10, PRIM_MAX = 200, SEQ_MAX = 200000, LETTER_NUM = 26, HASH_MAX = 1000001;

char x[PRIM_MAX + 1][LEN_MAX + 1]; // bahatimo se sa memorijom

char s[SEQ_MAX + 1];

bool hashLess[HASH_MAX], mark[SEQ_MAX + 1];
// hash

int Hash(char *str, int len) {
     long long tmpHash = 0;

    for (int idx = 0; idx < len && str[idx] != '\0'; idx++)
            tmpHash = tmpHash * (LETTER_NUM + 1) + str[idx] - 'A' + 1;
    return static_cast<int>(tmpHash % HASH_MAX);
}

int PrintHash(char *str, int len) {
     long long tmpHash = 0;
     printf("\nHash\n");

    for (int idx = 0; idx < len && str[idx] != '\0'; idx++)  {
            printf("%c ", str[idx]);
            tmpHash = tmpHash * (LETTER_NUM + 1) + str[idx] - 'A' + 1;
    }
    printf("tmpHash%lld", tmpHash);
    printf("\nHash\n");

    return static_cast<int>(tmpHash % HASH_MAX);
}

void ReadSeq(char *s) {
    int idx = 0;
    char c;

    while (scanf("%c", &c) == 1)
        if (c >= 'A' && c <= 'Z')
            s[idx++] = c;
    s[idx] = '\0';
 }

int main() {
    freopen ("prefix.in", "r", stdin);
    freopen ("prefix.out", "w", stdout);

    // ucitavanje
    int idx = 0;
    scanf ("%s", x[idx]);
    while (strcmp (x[idx++], ".") != 0)
        scanf("%s", x[idx]);
    int cnt = idx;

    // hesiranje
    // hashLess sadrzi da li postoji string ili ne u listi stringova
    memset (hashLess, 0, sizeof(hashLess));
    for  (int idx = 0; idx < cnt; idx++) {
        int tmpHash = Hash (x[idx], LEN_MAX);
        hashLess[tmpHash] = true;
    }

    ReadSeq(s);
    memset (mark, 0, sizeof(mark));
    mark[0] = true;
    int len = strlen(s);
    for (int idxIt = 1; idxIt <= len; idxIt++)
        for (int idxLen = 1; idxLen <= 10; idxLen++)
            if (hashLess[Hash (s + idxIt - 1, idxLen)] && mark[idxIt - 1]) {
                if (idxIt + idxLen - 1 >= len)
                    mark[len] = true;
                else  {
                    //printf("%d %c %d ", idxIt, s[idxIt - 1], idxLen );
                    mark[idxIt + idxLen - 1] = true;
                    //printf("%d\n", PrintHash (s + idxIt - 1, idxLen));
                    }
            }
    /*for (int idx = 0; idx < len; idx++)
        printf("%d %d\n", idx, mark[idx]);
    printf("\n");*/

    for (int idx = len; idx >= 0; idx--)
        if (mark[idx]) {
            printf("%d\n", idx);
            break;
        }

    return 0;
}
