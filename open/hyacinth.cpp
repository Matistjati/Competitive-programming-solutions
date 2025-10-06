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

int ind = 1;
void dfs(int u, int p, int forced, vector<p2>& color, vvi& adj)
{
    color[u].first = forced;
    color[u].second = ind++;
    int its = 0;
    repe(e, adj[u])
    {
        if (e == p) continue;
        int c = color[u].second;
        if (forced==0)
        {
            if (its > 0) c = color[u].first;
        }
        dfs(e, u, c, color, adj);
        its++;
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    if (n==2)
    {
        cout << "0 1\n0 1";
        return 0;
    }
    vvi adj(n);
	vector<p2> edg;
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
		edg.emplace_back(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<p2> label(n,p2(-1,-1));
    dfs(0, 0, 0, label, adj);
    for (auto [a, b] : label)
    {
        cout << a << " " << b << "\n";
    }

    return 0;
}
