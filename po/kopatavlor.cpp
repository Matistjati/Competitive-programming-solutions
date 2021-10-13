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
#define p3 tuple<ll, ll, ll>
#define vi vector<ll>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

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

int min_cost(vi& paintings, vector<int>& memo, int place, int bought, int cost, int& n, int& k)
{
    if (bought == k)
    {
        return cost;
    }
    else if (place == n)
    {
        return inf;
    }
    else if (bought > k)
    {
        return inf;
    }
    else if ((n - place) < (k - bought))
    {
        return inf;
    }

    int ret = inf;
    ll hashV = place*2001+(bought)+4004000;

    if (memo[hashV] != -1)
    {
        ret = min(ret, memo[hashV] + cost);
    }
    else
    {
        int d = min_cost(paintings, memo, place + 1, bought + 1, cost + paintings[place] + 1, n, k);

        memo[hashV] = d - cost;
        ret = min(d, ret);

    }
    hashV -= 4004000;

    if (memo[hashV] != -1)
    {
        ret = min(ret, memo[hashV] + cost);
    }
    else
    {
        int d = min_cost(paintings, memo, place + 1, bought, cost + 1, n, k);

        memo[hashV] = d - cost;
        ret = min(d, ret);

    }


    return ret;
}

int main()
{
    fast();

    int n;
    int k;
    read(n);
    read(k);

    vi paintings(n);
    repe(painting, paintings)
    {
        read(painting);
    }


    int ans = inf;
    vector<int> memo(2002*2000*2,-1);
    rep(i, n)
    {
        ans = min(ans, min_cost(paintings, memo, i, 0, 0, n, k));
    }
    write(ans - 1);


    return 0;
}