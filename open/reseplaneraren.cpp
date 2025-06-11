
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define __builtin_popcountll popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

const int maxn = int(3e5);
vvi edges;
vector<p2> trams;

int tin[maxn];
int tout[maxn];
int depth[maxn];
int up[maxn][20];
int timer = 0;

void dfs(int u, int p)
{
    depth[u] = depth[p] + 1;
    tin[u] = timer++;
    up[u][0] = p;

    repp(d, 1, 20) up[u][d] = up[up[u][d-1]][d - 1];

    repe(e, edges[u]) if (e!=p) dfs(e, u);

    tout[u] = timer++;
}

bool isancestor(int a, int b)
{
    return tin[a] <= tin[b] && tin[b] <= tout[a];
}

int lca(int a, int b)
{
    if (isancestor(a, b)) return a;
    if (isancestor(b, a)) return b;
    for (int d = 19; d >= 0; d--)
    {
        if (!isancestor(up[a][d], b))
        {
            a = up[a][d];
        }
    }
    return up[a][0];
}

int maxup[maxn];
vector<vector<p2>> activate;
vector<vector<p2>> deactivate;
set<p2> dfs2(int u, int p)
{
    set<p2> ret;
    repe(e, edges[u]) if (e != p)
    {
        set<p2> o = dfs2(e, u);
        if (sz(ret) < sz(o)) swap(ret, o);
        repe(v, o) ret.insert(v);
    }
    repe(a, activate[u]) ret.insert(a);

    if (sz(ret)) maxup[u] = begin(ret)->first;
    else maxup[u] = -1;

    repe(v, deactivate[u]) ret.erase(v);
    return ret;
}


struct Tree {
    typedef int T;
    static constexpr T unit = INT_MIN;
    T f(T a, T b) { return max(a, b); } // (any associative fn)
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) { // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

signed main()
{
    fast();

    int n, k, q;
    cin >> n >> k >> q;
    edges.resize(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    rep(i, k)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        trams.emplace_back(a, b);
    }
    depth[0] = -1;
    dfs(0, 0);
    activate.resize(n);
    deactivate.resize(n);



    rep(i, sz(trams))
    {
        p2 t = trams[i];
        int l = lca(t.first, t.second);
        activate[t.first].emplace_back(depth[l],t.first);
        activate[t.second].emplace_back(depth[l], t.second);
        deactivate[l].emplace_back(depth[l], t.first);
        deactivate[l].emplace_back(depth[l], t.second);
    }
    dfs2(0, 0);

    vector<p2> times;
    repe(t, trams)
    {
        times.emplace_back(tin[t.first], tin[t.second]);
    }
    sort(all(times));
    
    typedef tuple<int, int, int, int> p4;
    vector<p4> rect_queries;

    vi answers(q);
    rep(i, q)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;

        if (isancestor(a,b)||isancestor(b,a))
        {
            if (isancestor(b, a)) swap(a, b);
            assert(isancestor(a, b));

            if (maxup[b]!=-1&& maxup[b] <= depth[a])
            {
                answers[i] = 1;
            }
            continue;
        }

        rect_queries.emplace_back(tout[a], a, b, i);
        rect_queries.emplace_back(tout[b], b, a, i);
    }
    sort(all(rect_queries));
    Tree tree(timer);

    int p = 0;
    repe(q, rect_queries)
    {
        int t, a, b, ind;
        tie(t, a, b, ind) = q;
        assert(t == tout[a]);
        while (p<sz(times)&&times[p].first<=t)
        {
            tree.update(times[p].second, times[p].first);
            p++;
        }

        if (tree.query(tin[b], tout[b] + 1) >= tin[a]) answers[ind] = 1;
    }

    rep(i, q)
    {
        cout << (answers[i] ? "Yes" : "No") << "\n";
    }

    return 0;
}
