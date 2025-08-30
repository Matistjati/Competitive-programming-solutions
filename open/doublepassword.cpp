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


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    string a, b;
    cin >> a >> b;
    int ans = 0;
    rep(p, 10000)
    {
        string pass = to_string(p);
        while (sz(pass) < 4) pass.insert(pass.begin(), '0');
        bool good = 1;
        rep(i, 4) good &= (pass[i] == a[i] || pass[i] == b[i]);
        ans += good;
    }
    cout << ans << '\n';

    return 0;
}
