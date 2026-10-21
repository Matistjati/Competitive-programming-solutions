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

void topsort(int u, vi& vis, vi& order, vvi& edges) {
    if (vis[u]) return;
    vis[u] = 1;

    repe(e, edges[u]) topsort(e, vis, order, edges);

    order.push_back(u);
}

int main() {
    int n,m,t;
    cin >> n >> m >> t;
    vvi edges(n);
    vvi redges(n);
    rep(i, m) {
        int a,b;
        cin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
        redges[b].push_back(a);
    }
    bitset<1001> special;
    rep(i, t) {
        int u;
        cin >> u;
        u--;
        special[u] = 1;
    }

    vi order;
    vi vis(n);
    rep(i, n) {
        topsort(i, vis, order, edges);
    }

    vector<bitset<1001>> bsets(n);

    repe(u, order)
    {
        bsets[u][u] = 1;
        repe(e, redges[u])
        {
            bsets[e] |= bsets[u];
        }
    }

    reverse(all(order));
    repe(u, order)
    {
        if (!special[u]) continue;
        repe(e, edges[u])
        {
            special[e] = 1;
        }
    }

    bitset<1001> ans;
    rep(i, n)
    {
        if (!special[i])
        {
            bitset<1001> vis;
            rep(j, n)
            {
                if (!bsets[j][i]&&j!=i&&redges[j].empty())
                {
                    vis |= bsets[j];
                }
            }
            if ((special|vis).count()>vis.count())
            {
                ans[i] = 1;
            }
        }
        else ans[i] = 1;
    }

    rep(i, n)
    {
        if (ans[i]) cout << i + 1 << " ";
    }

    return 0;
}
