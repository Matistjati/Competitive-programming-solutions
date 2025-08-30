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

    int n, lph;
    cin >> n >> lph;
    vi problems(n);
    repe(p, problems) cin >> p;
    sort(all(problems));
    int pref = 0;
    int ans = 0;
    rep(i, n)
    {
        if (pref + problems[i] > lph * 5) break;
        pref += problems[i];
        ans++;
    }
    cout << ans << '\n';

    return 0;
}
