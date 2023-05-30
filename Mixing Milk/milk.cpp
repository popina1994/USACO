/*
NAME: popina
TASK: milk
LANG: C++
*/
#include <iostream>
#include <fstream>
#define stop system("pause");

using namespace std;

struct farmer
{
    int price, amount;
};

const int nmax = 2000000, mmax = 5001;
farmer x[mmax];
int amount, numfarmer;

void ispis()
{
    for (int i = 0; i < numfarmer; i++)
        cout << x[i].price << "  " << x[i].amount << endl;
    stop;
}

void input()
{
    ifstream f("milk.in");
    f >> amount >> numfarmer;
    for (int i = 0; i < numfarmer; i++)
        f >> x[i].price >> x[i].amount;
    f.close();
}

void swap(farmer &x, farmer &y)
{
    farmer c;
    c.price = x.price;
    c.amount = x.amount;
    x.price = y.price;
    x.amount = y.amount;
    y.price = c.price;
    y.amount = c.amount;
    }

void sort()
{
    for (int i = 0; i < numfarmer - 1; i++)
        for (int j = i + 1; j < numfarmer; j++)
            if (x[i].price > x[j].price)
                swap(x[i], x[j]);
}

int loading()
{
    sort();
    int curprice = 0, i = 0, curamount;
    curamount = amount;
    for (; curamount > x[i].amount; i++)
    {   
        curprice += x[i].price * x[i].amount;
        curamount -= x[i].amount;

    } 
    curprice += curamount * x[i].price;
    return(curprice);

}

void output(int result)
{
    ofstream f("milk.out");
    f << result << endl;
    f.close();
}

int main()
{
    int result;
    input();
    result = loading();
    output(result);
    return(0);
}



 
