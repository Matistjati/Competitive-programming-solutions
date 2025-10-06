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

void toposort(int u, vi& vis, vi& order, vvi& adj)
{
    if (vis[u]) return;
    vis[u] = 1;

    repe(e, adj[u]) toposort(e, vis, order, adj);
    order.push_back(u);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll b, n;
    cin >> b >> n;
    vvi adj(n+1);
    vector<char> state(n+1);
    rep(i, n)
    {
        char d;
        int l, r;
        cin >> d >> l >> r;
        adj[i+1].push_back(l);
        adj[i+1].push_back(r);
        state[i+1] = d;
    }
    
    auto invert = [](char c)
    {
        if (c == 'R') return 'L';
        return 'R';
    };

    vi vis(n+1), order;
    rep(i, n+1)toposort(i, vis, order, adj);
    
    vi numballs(n + 1);
    numballs[1] = b;
    reverse(all(order));
    repe(u, order)
    {
        if (!u) continue;
        ll myballs = numballs[u];
        numballs[adj[u][0]] += myballs / 2;
        numballs[adj[u][1]] += myballs / 2;
        if (myballs%2==1)
        {
            if (state[u] == 'L') numballs[adj[u][0]]++;
            else numballs[adj[u][1]]++;
            state[u] = invert(state[u]);
        }
    }
    repp(i, 1, n+1)
    {
        cout << state[i];
    }

    return 0;
}
