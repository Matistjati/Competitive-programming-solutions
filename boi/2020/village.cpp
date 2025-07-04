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

const int maxn = int(1e5) + 10;
int subtree_sz[maxn];

int calc_sz(int u, int p, vvi& adj)
{
    subtree_sz[u] = 1;
    repe(e, adj[u]) if (e != p) subtree_sz[u] += calc_sz(e, u, adj);
    return subtree_sz[u];
}

int get_centroid(int u, int p, vvi& adj)
{
    repe(e, adj[u]) if (e!=p&& subtree_sz[e] > sz(adj) / 2) return get_centroid(e, u, adj);
    return u;
}

int get_dist(int u, int p, int d, vvi& adj)
{
    int ret = d;
    repe(e, adj[u]) if (e != p) ret += get_dist(e, u, d + 1, adj);
    return ret;
}

void gather(int u, int p, vi& comp, vvi& adj)
{
    comp.push_back(u);
    repe(e, adj[u]) if (e != p) gather(e, u, comp, adj);
}

int minans = 0;
p2 solvemin(int u, int p, vi& ans, vvi& adj)
{
    vector<p2> children;
    repe(e, adj[u]) if (e != p)
    {
        p2 c = solvemin(e, u, ans, adj);
        c.second++;
        if (c.first != -1) children.push_back(c);
    }

    if (sz(children)==0) // leaf
    {
        return {u,0};
    }
    if (sz(children)%2==1)
    {
        minans += 2*children[0].second;
        ans[u] = children[0].first;
        ans[children[0].first] = u;
        for (int i = 1; i < sz(children); i += 2)
        {
            minans += 2*(children[i].second+children[i+1].second);
            ans[children[i].first] = children[i + 1].first;
            ans[children[i + 1].first] = children[i].first;
        }

        return { -1,-1 };
    }
    if (sz(children)%2==0)
    {
        minans += 1;
        ans[u] = children[0].first;
        for (int i = 0; i+1 < sz(children); i++)
        {
            minans += 2;
            ans[children[i].first] = children[i + 1].first;
        }
        ans[children.back().first] = u;
        minans += 1;

        return { -1,-1 };
    }
}

signed main()
{
    fast();

    memset(subtree_sz, 0, sizeof(subtree_sz));
    int n;
    cin >> n;
    vvi adj(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    calc_sz(0, 0, adj);
    int c = get_centroid(0, 0, adj);

    int ans = 0;
    repe(e, adj[c]) ans += get_dist(e, c, 1, adj);

    vvi components;
    repe(e, adj[c])
    {
        components.push_back({});
        gather(e, c, components.back(), adj);
    }
    sort(all(components), [](vi& a, vi& b)
        {
            return sz(a) < sz(b);
        });

    vi ansmin(n, -1);
    vi ansmax(n, -1);
    if (n%2==0)
    {
        ansmax[c] = components.back().back();
        ansmax[components.back().back()] = c;
        components.back().pop_back();
    }
    else
    {
        int a = components[sz(components) - 1].back();
        components[sz(components) - 1].pop_back();
        int b = components[sz(components) - 2].back();
        components[sz(components) - 2].pop_back();
        ansmax[c] = a;
        ansmax[a] = b;
        ansmax[b] = c;
    }

    priority_queue<p2> pq;
    rep(i, sz(components)) if (sz(components[i])) pq.emplace(sz(components[i]), i);
    while (sz(pq))
    {
        auto [_, i] = pq.top();
        pq.pop();
        auto [__, j] = pq.top();
        pq.pop();

        int a = components[i].back();
        components[i].pop_back();
        int b = components[j].back();
        components[j].pop_back();

        ansmax[a] = b;
        ansmax[b] = a;
        if (sz(components[i])) pq.emplace(sz(components[i]), i);
        if (sz(components[j])) pq.emplace(sz(components[j]), j);
    }

    p2 r = solvemin(0, 0, ansmin, adj);
    if (r.first!=-1)
    {
        int a = r.first;
        int intou;
        int u = adj[a][0];
        rep(i, n) if (ansmin[i] == u) intou = i;
        int fromu = ansmin[u];
        if (find(all(adj[a]),fromu)==adj[a].end())
        {
            minans += 2;
        }
        ansmin[a] = fromu;
        ansmin[u] = a;

    }

    cout << minans << " " << ans * 2 << "\n";
    repe(u, ansmin) cout << u+1 << " ";
    cout << "\n";
    repe(u, ansmax) cout << u+1 << " ";

    return 0;
}
