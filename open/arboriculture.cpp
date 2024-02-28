#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e7);//int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#define _LOCAL _DEBUG
#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


pair<int, vi> hungarian(const vector<vi>& a) {
    if (a.empty()) return { 0, {} };
    int n = sz(a) + 1, m = sz(a[0]) + 1;
    vi u(n), v(m), p(m), ans(n - 1);
    repp(i, 1, n) {
        p[0] = i;
        int j0 = 0; // add "dummy" worker 0
        vi dist(m, int(1e12)), pre(m, -1);
        vector<bool> done(m + 1);
        do { // dijkstra
            done[j0] = true;
            int i0 = p[j0], j1, delta = int(1e12);
            repp(j, 1, m) if (!done[j]) {
                auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
                if (dist[j] < delta) delta = dist[j], j1 = j;
            }
            repp(j, 0, m) {
                if (done[j]) u[p[j]] += delta, v[j] -= delta;
                else dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);
        while (j0) { // update alternating path
            int j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    repp(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
    return { -v[0], ans }; // min cost
}

vi getfatherless(vi& adj, int p)
{
    vi ret;
    repe(v, adj) if (v != p) ret.push_back(v);
    return ret;
}

int getcost(vvi& toadj, vvi& fromadj, int t, int tp, int f, int fp)
{
    vi to = getfatherless(toadj[t], tp);
    vi from = getfatherless(fromadj[f], fp);
    if (sz(to) > sz(from)) return inf;
    if (sz(to) == 0) return sz(from);


    vvi cost(sz(to), vi(sz(from), inf));
    rep(i, sz(from)) rep(j, sz(to))
    {
        if (from[i] == fp || to[j] == tp) continue;
        cost[j][i] = getcost(toadj, fromadj, to[j], t, from[i], f);
    }
    return hungarian(cost).first + (sz(from) - sz(to));
}

int tree_cost(vvi& to, vvi& from)
{
    if (sz(from) < sz(to)) return inf;
    return getcost(to, from, 0, 0, 0, 0);
}

signed main()
{
    fast();

    vector<vvi> goal;
    vector<vvi> trees;
    int n, m;
    cin >> n >> m;

    rep(i, n)
    {
        int v;
        cin >> v;
        v++;
        vvi tree(v);
        rep(j, v - 1)
        {
            int u;
            cin >> u;
            tree[j + 1].push_back(u);
            tree[u].push_back(j + 1);
        }
        goal.push_back(tree);
    }

    rep(i, m)
    {
        int v;
        cin >> v;
        v++;
        vvi tree(v);
        rep(j, v - 1)
        {
            int u;
            cin >> u;
            tree[j + 1].push_back(u);
            tree[u].push_back(j + 1);
        }
        trees.push_back(tree);
    }

    vvi cost(n, vi(m));
    rep(i, n)
    {
        rep(j, m)
        {
            cost[i][j] = tree_cost(goal[i], trees[j]);
        }
    }

    cout << hungarian(cost).first;

    return 0;
}