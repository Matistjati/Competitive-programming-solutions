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


inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int main()
{
    fast();

    int n;
    read(n);
    vi an;
    vi be;
    rep(i, n)
    {
        readpush(ll, an);
    }
    rep(i, n)
    {
        readpush(ll, be);
    }

    ll sumAn = accumulate(all(an), 0LL);
    ll sumBe = accumulate(all(be), 0LL);
    sort(all(an));
    sort(all(be));

    ll ans = linf;

    rep(i, n)
    {
        ll outer = -(sumAn - sumBe - 2 * an[i]) / 2;
        auto bestMatch = lower_bound(all(be), outer);
        if (bestMatch != be.end())
        {
            ans = min(ans, abs(sumAn - sumBe - 2 * an[i] + 2 * (*bestMatch)));
        }
        else
        {
            ans = min(ans, abs(sumAn - sumBe - 2 * an[i] + 2 * *prev(bestMatch)));
        }
    }

    write(ans);

    return 0;
}