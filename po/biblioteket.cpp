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

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define inf 2e9
#define linf 1e17

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
#define fract(a) (a-floor(a))

inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int a(vector<int> pos, vector<int> neg, int k)
{

    int ans = 0;
    int left = k;

    int d = -inf;

    repe(p, pos)
    {


        if (left == 0)
        {
            left = k;
            ans += abs(d * 2);
            d = -inf;
        }
        d = max(d, p);
        left--;
    }

    if (d != -inf)
    {
        ans += d*2;
    }

    d = inf;
    left = k;

    vector<int> ending;
    rep(i, k)
    {
        if (neg.empty())
        {
            break;
        }
        ending.push_back(neg[0]);
        neg.erase(begin(neg));
    }

    repe(p, neg)
    {


        if (left == 0)
        {
            left = k;
            ans += abs(d * 2);
            d = inf;
        }
        d = min(d, p);
        left--;
    }

    if (d != inf)
    {
        ans += abs(d*2);
    }

    ans += abs(ending[0]);

    return ans;
}


int b(vector<int> pos, vector<int> neg, int k)
{

    int ans = 0;
    int left = k;

    int d = inf;
    left = k;

    repe(p, neg)
    {


        if (left == 0)
        {
            left = k;
            ans += abs(d * 2);
            d = inf;
        }
        d = min(d, p);
        left--;
    }

    if (d != inf)
    {
        ans += abs(d*2);
    }


    d = -inf;
    left = k;


    vector<int> ending;
    rep(i, k)
    {
        if (pos.empty())
        {
            break;
        }
        ending.push_back(pos[0]);
        pos.erase(begin(pos));
    }

    repe(p, pos)
    {


        if (left == 0)
        {
            left = k;
            ans += abs(d * 2);
            d = -inf;
        }
        d = max(d, p);
        left--;
    }


    if (d != -inf)
    {
        ans += abs(d*2);
    }

    ans += abs(ending[0]);


    return ans;
}

int main()
{
    fast();

    int n;
    read(n);
    int k;
    read(k);

    vector<int> pos;
    vector<int> neg;

    rep(i, n)
    {
        int v;
        read(v);

        if (v > 0)
        {
            pos.push_back(v);
        }
        else
        {
            neg.push_back(v);
        }
    }

    sort(all(pos));
    reverse(all(pos));
    sort(all(neg));


    write(min(a(pos,neg,k),b(pos,neg,k)));


    return 0;
}
