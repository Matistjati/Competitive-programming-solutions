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

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vvi adj(n);
    vi indeg(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indeg[b]++;
    }
    int num_elim = 0;
    vi leaf;
    rep(i, n) if (indeg[i] == 0) leaf.push_back(i);

    while (sz(leaf))
    {
        if (sz(leaf)>1)
        {
            cout << "NO\n";
            return 0;
        }
        num_elim++;
        int u = leaf.back();
        leaf.pop_back();

        repe(e, adj[u])
        {
            indeg[e]--;
            if (indeg[e] == 0) leaf.push_back(e);
        }
    }
    if (num_elim<n)
    {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";


    return 0;
}
