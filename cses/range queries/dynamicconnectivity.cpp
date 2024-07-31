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
#define assert(x) if (!(x)) __debugbreak()
#endif

struct state
{
    int a, b;
    int parb, sza;
    int numcomps;
};

struct UF
{
    vi par;
    vi size;
    vector<state> history;
    int numcomps;
    UF(int n) : par(n), size(n, 1), numcomps(n)
    {
        rep(i, n) par[i] = i;
    }
    int find(int x) { return par[x] == x ? x : find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (size[a] < size[b]) swap(a, b);
        state s = { a,b,par[b],size[a], numcomps };
        if (a!=b)
        {
            numcomps--;
            par[b] = a;
            size[a] += size[b];
        }

        history.push_back(s);
    }

    void undo()
    {
        state s = history.back();
        history.pop_back();
        numcomps = s.numcomps;
        par[s.b] = s.parb;
        size[s.a] = s.sza;
    }
};
UF uf(0);

struct Tree
{
    vector<vector<p2>> edges;
    vi compsizes;
    Tree(int n) : edges(n*4), compsizes(n) {}

    void update(int x, int l, int r, int ql, int qr, p2 e)
    {
        if (r<ql || l>qr) return;
        if (l>=ql&&r<=qr)
        {
            edges[x].push_back(e);
            return;
        }
        int mid = (l + r) / 2;
        update(x * 2, l, mid, ql, qr, e);
        update(x * 2 + 1, mid + 1, r, ql, qr, e);
    }

    void dfs(int x, int l, int r, UF& uf)
    {
        repe(e, edges[x]) uf.merge(e.first, e.second);
        if (l==r)
        {
            compsizes[l] = uf.numcomps;
        }
        else
        {
            int mid = (l + r) / 2;
            dfs(x * 2, l, mid, uf);
            dfs(x * 2 + 1, mid + 1, r, uf);
        }
        repe(e, edges[x]) uf.undo();
    }
};



signed main()
{
    fast();

    int n, m, q;
    cin >> n >> m >> q;
    uf = UF(n);
    map<p2, int> alive;
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (a < b) swap(a, b);
        alive[p2(a, b)] = i;
    }
    Tree tree(m + q);
    rep(i, q)
    {
        int t, a, b;
        cin >> t >> a >> b;
        a--; b--;
        if (a < b) swap(a, b);
        if (t==1)
        {
            alive[p2(a, b)] = i+m;
        }
        else
        {
            int l = alive[p2(a, b)];
            alive.erase(p2(a, b));
            tree.update(1, 0, m + q -1, l, i+m - 1, p2(a,b));
        }
    }
    repe(a, alive)
    {
        tree.update(1, 0, m + q - 1, a.second, m + q - 1, a.first);
    }
    tree.dfs(1, 0, m+q-1, uf);
    repp(i, m - 1, m + q)
    {
        cout << tree.compsizes[i] << " ";
    }

    return 0;
}
