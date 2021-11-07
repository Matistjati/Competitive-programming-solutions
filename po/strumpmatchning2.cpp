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
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
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

ll possible(vector<ll>& socks, ll& k, ll d)
{
    int n = 0;
    rep(i, socks.size()-1)
    {
        if (socks[i+1]-socks[i] < d)
        {
            n++;
            i++;
        }
    }


    return n >= k;
}

int main()
{
    fast();

    ll n;
    ll k;
    read(n);
    read(k);

    vector<ll> socks;
    rep(i, n)
    {
        readpush(ll, socks);
    }
    sort(all(socks));





    ll high = linf;
    ll low = 0;
    while (true)
    {
        ll mid = (high + low) / 2;

        ll p = possible(socks, k, mid);
        if (p)
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }

        if (low == high)
        {
            write(high);
            return 0;
        }
    }

    return 0;
}