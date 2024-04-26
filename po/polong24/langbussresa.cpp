#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({ k, m, 0 }), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

signed main()
{
    fast();

    int x, n, m, w, t;
    cin >> x >> n >> m >> w >> t;

    vi s(n);
    rep(i, n) cin >> s[i];
    s.push_back(x);

    vector<p2> people(m);
    rep(i, m) cin >> people[i].first >> people[i].second;
    sort(all(people));
    vi d(m);
    rep(i, m) d[i] = people[i].first;

    vi mint(m, inf);
    rep(i, n + 1)
    {
        auto it = upper_bound(all(d), s[i] % t);
        if (it == begin(d)) continue;
        int ind = prev(it) - begin(d);
        mint[ind] = min(mint[ind], s[i] / t);
    }
    mint.insert(mint.begin(), 0);

    vi dp(m + 1, inf);
    dp[0] = (x / t + 1) * w;
    vi pref(m);
    pref[0] = people[0].second;
    repp(i, 1, m) pref[i] = people[i].second + pref[i - 1];
    pref.insert(pref.begin(), 0);

    LineContainer lc;
    lc.add(0, -dp[0]);
    repp(i, 1, m + 1)
    {
        // never kick off person i
        dp[i] = dp[i - 1] + ((x - d[i - 1]) / t + 1) * w;

        // start a kick off interval ending at i
        int c = pref[i] + (i + 1) * w * mint[i];
        if (mint[i] != inf) dp[i] = min(dp[i], c - lc.query(-w * mint[i])),
            dp[i] = min(dp[i], dp[i - 1] + people[i - 1].second + mint[i] * w);

        lc.add(-(i), -(dp[i - 1] - pref[i - 1]));
    }

    cout << dp.back();

    return 0;
}