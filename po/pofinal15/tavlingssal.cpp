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

using namespace std;

#define ll long long
#define p2 pair<ll, ll>
#define vi vector<ll>
#define vvi vector<vi>
#define inf 2e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define deb __debugbreak();

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)


inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

inline ll isGreater(ll a, ll b, ll n)
{
    return (a + 1) * (b + 1) - n;
}

int main()
{
    fast();

    ll n;
    read(n);

    ll max = (ll)(ceil(sqrt(n)))*2;

    ll minArea = inf;
    for (int j = 1; j < max; j++)
    {
        ll k = ceildiv(n,j);
        minArea = min(minArea, (j + 1) * (k + 1));
    }

    write(minArea);

    return 0;
}