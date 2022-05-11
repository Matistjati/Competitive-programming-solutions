#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <iterator>
#include <queue>

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) set.find(x) != set.end()
#define notsetcontains(set, x) set.find(x) == set.end()

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto const& i : container)
#define inf 1e9

int digitmul(int x)
{
    int s = 1;
    while (x != 0) {
        s *= x % 10;
        x = x / 10;
    }
    return s;
}


int digitsum(int x)
{
    int s = 0;
    while (x != 0) {
        s += x % 10;
        x = x / 10;
    }
    return s;
}

int digitalroot(int n)
{
    while (n > 9)
    {
        n = digitsum(n);
    }
    return n;
}

int digitalmul(int n)
{
    while (n > 9)
    {
        n = digitmul(n);
    }
    return n;
}

int main()
{
    int low;
    int high;
    read(low);
    read(high);

    int n_same = 0;

    for (int i = low; i <= high; i++)
    {
        if (digitalroot(i) == digitalmul(i))
        {
            n_same += 1;
        }
    }
    write(n_same);
}