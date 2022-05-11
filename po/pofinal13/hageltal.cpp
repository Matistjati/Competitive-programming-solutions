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
#include <stack>
#include <chrono>
#include <unordered_map>
#include <iomanip>
#include <thread>

using namespace std;

#define ll long long
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define p4 tuple<ll, ll, ll, ll>
#define vi vector<ll>
#define vii vector<vi>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define deb nothing();

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)

inline void nothing() {}

inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int main()
{
    fast();

    int a;
    int b;
    read(a);
    read(b);
    if (a > b)
    {
        swap(a, b);
    }


    int n = 0;
    map<int, int> arrows;
    while (a != 1)
    {
        arrows[a] = n;
        if (a % 2 == 0)
        {
            a /= 2;
        }
        else
        {
            a = a * 3 + 1;
        }
        n++;
    }
    n = 0;
    while (b != 1)
    {
        if (setcontains(arrows, b))
        {
            write(arrows[b] + n);
            return 0;
        }
        if (b % 2 == 0)
        {
            b /= 2;
        }
        else
        {
            b = b * 3 + 1;
        }
        n++;
    }
    write(n);

    return 0;
}