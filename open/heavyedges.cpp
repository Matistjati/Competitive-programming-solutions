#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }



struct state
{
    int a, b;
    int parb;
    int sizea;
};

struct UF
{
    vi par;
    vi size;

    UF(int n) : par(n), size(n, 1)
    {
        rep(i, n) par[i] = i;
    }

    int find(int x) { return x == par[x] ? x : find(par[x]); }

    stack<state> changes;

    void merge(int a, int b)
    {
        state change;
        a = find(a); b = find(b);
        if (size[a] < size[b]) swap(a, b);
        change.a = a;
        change.b = b;
        change.parb = par[b];
        change.sizea = size[a];
        if (a != b)
        {
            par[b] = a;
            size[a] += size[b];
        }
        changes.push(change);
    }

    void undo()
    {
        state change = changes.top();
        changes.pop();
        par[change.b] = change.parb;
        size[change.a] = change.sizea;
    }
};

int ans = 0;

UF uf(0);

void dc(int l, int r, vector<p2>& q)
{
    if (l > r) return;
    if (l == r)
    {
        ans += (uf.find(q[l].first) == uf.find(q[l].second));
        return;
    }
    int mid = (l + r) / 2;

    repp(i, l, mid + 1) uf.merge(q[i].first, q[i].second);
    dc(mid + 1, r,q);
    repp(i, l, mid + 1) uf.undo();

    repp(i, mid + 1, r+1) uf.merge(q[i].first, q[i].second);
    dc(l, mid, q);
    repp(i, mid + 1, r+1) uf.undo();
}

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;

    map<int, vector<p2>> edges;
    rep(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        edges[c].emplace_back(a, b);
    }

    uf = UF(n);
    repe(w,edges)
    {
        dc(0, sz(w.second) - 1, w.second);

        for (auto [a, b] : w.second)
        {
            uf.merge(a,b);
        }
    }

    cout << ans;

    return 0;
}
