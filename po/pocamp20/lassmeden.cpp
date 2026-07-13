#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, q;
    cin >> n >> q;
    vi marked(n + 1);

    ll cutoff = 450;
    vector<multiset<ll>> small(cutoff + 1);
    rep(i, q)
    {
        ll t;
        cin >> t;
        if (t == 1)
        {
            ll x;
            cin >> x;
            bool any = 0;
            if (marked[x])
            {
                any = 1;
            }

            if (!any)
            {
                repp(i, 1, cutoff)
                {
                    if (small[i].count(x % i))
                    {
                        any = 1;
                        break;
                    }
                }
            }

            cout << (any ? "ja" : "nej") << "\n";
        }
        else if (t == 2)
        {
            ll a, b;
            cin >> a >> b;
            if (b < cutoff)
            {
                small[b].insert(a);
            }
            else
            {
                for (ll i = a; i < marked.size(); i += b)
                {
                    marked[i]++;
                }
            }
        }
        else
        {
            ll a, b;
            cin >> a >> b;
            if (b < cutoff)
            {
                small[b].erase(small[b].find(a));
            }
            else
            {
                for (ll i = a; i < marked.size(); i += b)
                {
                    marked[i]--;
                }
            }
        }
    }

    return 0;
}
