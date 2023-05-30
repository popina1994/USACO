#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

const int n_max = 100000;


int x[n_max], y[n_max], z[n_max], n = n_max;
long long MergeInversions( int begin, int end)
{
    long long counter = 0ll, mid = (begin + end) / 2;
    if (begin >= end)
        return 0;
    counter = MergeInversions(begin, (begin + end) / 2) + MergeInversions((begin + end) / 2 + 1, end);
    for (long long i = begin; i <= mid; i++)
        y[i - begin] = x[i];
    for (long long i = mid + 1; i <= end; i++)
        z[i - mid - 1] = x[i];
    long long i = 0, j = 0;
    for (long long k = begin; k <= end; k++)
    {
        if (j == end - mid || i < mid - begin + 1 && y[i] <= z[j])
        {
            x[k] = y[i];
            i ++;
        }
        else
        {
            x[k] = z[j];
            j ++;
            counter += mid - begin + 1 - i;
        }
    }
    printf("%d\n", counter);
    return counter;
}

int main()
{
    freopen("IntegerArray.in", "r", stdin);
    for (int i = 0; i < n; i ++)
        scanf("%d", &x[i]);
    freopen("IntegerArray.out", "w", stdout);

    printf("%lld",MergeInversions(0, n - 1));

    return 0;
}
