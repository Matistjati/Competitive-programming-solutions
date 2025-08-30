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

    int t;
    cin >> t;
    repp(tc, 1, t+1)
    {
        ll ans = 0;
        int n;
        cin >> n;
        vi a(n), b(n);
        repe(v, a) cin >> v;
        repe(v, b) cin >> v;
        sort(all(a));
        sort(all(b));
        reverse(all(b));
        rep(i, n) ans += a[i] * b[i];

        cout << "Case #" << tc << ": " << ans << '\n';
    }

    return 0;
}
