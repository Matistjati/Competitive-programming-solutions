using namespace std;
#include <bits/stdc++.h>
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;

#define rep(i,n) for (int i = 0; i < (n); i++)
#define repe(i,a) for (auto& i : a)

void dfs(int u, vi& vis, vvi& adj)
{
    if (vis[u]) return;
    vis[u]=1;
    repe(e,adj[u]) dfs(e,vis,adj);

}

int main()
{
    int n,m;
    cin >> n >> m;

    vvi adj(n);
    rep(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    vi va(n);
    vi vb(n);
    int x,y;
    cin >> x >> y;
    x--; y--;
    dfs(x,va,adj);
    dfs(y,vb,adj);

    rep(i,n)
    {
        if (va[i]&&vb[i])
        {
            cout << "yes\n";
            cout << i+1 << '\n';
            return 0;
        }
    }
    cout << "no\n";
    return 0;
}

