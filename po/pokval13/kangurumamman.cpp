#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>
#include <string>
#include <iterator>
#include <queue>
#include <tuple>
#include <numeric>
#include <random>
#include <time.h>


using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)
#define inf 1e9
#define ceildiv(x,y) ((x + y - 1) / y)

inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int main()
{
    fast();

    vector<int> fib;
    int a = 1;
    int b = 0;
    int prev = 0;
    while (a+b<1000000)
    {
        fib.push_back(a + b);
        int temp = a;
        a = a + b;
        b = temp;
    }
    fib.insert(fib.begin(),1);

    int capacity;
    read(capacity);
    capacity *= 1000;
    int n = 0;
    int weight = 0;
    while (true)
    {
        if (weight+fib[n] > capacity)
        {
            break;
        }
        weight += fib[n];
        n++;
    }
    write(n);

    return 0;
}