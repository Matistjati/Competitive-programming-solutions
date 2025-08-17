#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

vi w;
vvi divisors;
unordered_map<ll, ll> dp;

ll comp_hash(set<ll>&x)
{
    ll ret = 1;
    repe(v, x)
    {
        ret = (ret + v) * 12423457;
    }

    return ret;
}

ll best(set<ll>& state)
{
    if (state.empty()||(sz(state)==1&&*begin(state)==1))
    {
        return 0;
    }

    auto it = dp.find(comp_hash(state));
    if (it != dp.end()) return it->second;

    ll ret = inf;
    ll v = *prev(end(state));

    {
        set<ll> c = state;
        c.erase(v);
        ll extra = c.count(v-1) ? 0 : w[v - 1];
        c.insert(v - 1);
        ret = min(ret, extra+best(c));
    }

    repe(d, divisors[v])
    {
        set<ll> c = state;
        c.erase(v);
        ll extra = c.count(d) ? 0 : w[d];
        if (!c.count(v / d) && v/d!=d) extra += w[v / d];
        c.insert(d);
        c.insert(v/d);
        ret = min(ret, extra + best(c));
    }

    return dp[comp_hash(state)]=ret;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    
    dp.reserve(int(1e6));

    ll n;
    cin >> n;
    w.resize(n);
    repe(v, w) cin >> v;
    w.insert(w.begin(), 0LL);
    divisors.resize(n + 1);

    repp(i, 1, n + 1)
    {
        vi divs;
        ll j = 2;
        ll v = i;
        while (v>1&&j*j<=v)
        {
            if (v % j == 0) divs.push_back(j);
            j++;
        }
        divisors[i] = divs;
    }

    repp(i, 1, n+1)
    {
        set<ll> st = { i };
        cout << best(st)+w[i] << "\n";
    }

    return 0;
}
