#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct UF
{
    vi par;
    vi size;
    UF(int n) : par(n), size(n, 1)
    {
        rep(i, n) par[i] = i;
    }

    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a), b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<set<int>> adj(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].insert(b);
        adj[b].insert(a);
        if (a < b) swap(a, b);
    }

    set<int> q;
    rep(i, n)
    {
        if (sz(adj[i])>1)
        {
            q.insert(i);
        }
    }
    
    vector<tuple<int, int, int>> ans;
    auto op = [&](int a, int b, int u)
        {
            
            adj[u].erase(a);
            adj[a].erase(u);
            
            adj[u].erase(b);
            adj[b].erase(u);

            ans.emplace_back(a, b, u);

            if (adj[a].find(b) != adj[a].end())
            {
                adj[a].erase(b);
                adj[b].erase(a);
            }
            else
            {
                adj[a].insert(b);
                adj[b].insert(a);
                
            }
        };

    while (sz(q))
    {
        int u = *begin(q);
        q.erase(q.begin());
        if (sz(adj[u])<2)
        {
            continue;
        }
        int a = *begin(adj[u]);
        int b = *next(begin(adj[u]));
        op(a, b, u);
        if (sz(adj[a]) > 1) q.insert(a);
        if (sz(adj[b]) > 1) q.insert(b);
        if (sz(adj[u]) > 1) q.insert(u);
    }

    UF uf(n);
    int p = -1;
    rep(i, n)
    {
        assert(sz(adj[i]) < 2);
        if (sz(adj[i]))
        {
            uf.merge(i, *begin(adj[i]));
            p = i;
        }
    }

    if (p!=-1)
    {
        int p1 = *begin(adj[p]);
        rep(i, n)
        {
            if (uf.find(p) != uf.find(i))
            {
                op(p, p1, i);
                uf.merge(p, i);
                p1 = i;
            }
        }
    }

    cout << sz(ans) << "\n";
    repe(t, ans)
    {
        int a, b, c;
        tie(a, b, c) = t;
        cout << a + 1 << " " << b + 1 << " " << c + 1 << "\n";
    }

}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
