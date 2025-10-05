#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    set<p2> seen;
    int n, m;
    cin >> n >> m;
    vi indeg(n), outdeg(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        indeg[b]++;
        if (seen.count(p2(b, a))) indeg[a]--, indeg[b]--;
        seen.insert(p2(a, b));
    }

    p2 best = p2(-1, 0);
    rep(i, n)
    {
        best = max(best, p2(indeg[i], -i));
    }
    cout << -best.second+1 << " " << best.first << '\n';

    return 0;
}
