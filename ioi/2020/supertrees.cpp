#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll

//const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

static void check(bool cond, std::string message);

void build(std::vector<std::vector<int>> _b);

struct UF
{
    vi par;
    vi size;
    UF(int n) : par(n), size(n, 1)
    {
        rep(i, n) par[i] = i;
    }
    int find(int x) { return par[x] == x ? x: par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        par[b] = a;
        size[a] += size[b];
    }
};

int construct(vvi p) {
	int n = p.size();
	vvi ans(n,vi(n));

    UF uf(n);
    rep(i, n) rep(j, n)
    {
        if (p[i][j]) uf.merge(i, j);
        if (p[i][j] == 3) return 0;
    }


    map<int, vi> comps;
    rep(i, n) comps[uf.find(i)].push_back(i);

    repe(c, comps)
    {
        vi& comp = c.second;
        if (sz(comp) == 0) continue;

        int all_one = 1;

        repe(a, comp)
        {
            repe(b, comp)
            {
                all_one &= p[a][b] == 1;
                if (!p[a][b])
                {
                    return 0;
                }
            }
        }
        if (all_one)
        {
            rep(i, sz(comp) - 1)
            {
                int u = comp[i];
                int v = comp[i + 1];
                ans[u][v] = 1;
                ans[v][u] = 1;
            }
        }
        else
        {
            UF uf2(n);

            repe(a, comp)
            {
                repe(b, comp)
                {
                    if (p[a][b] == 1)
                    {
                        uf2.merge(a, b);
                    }
                }
            }

            set<int> cycleset;
            map<int, vi> heads;
            repe(a, comp)
            {
                if (uf2.find(a) == a) cycleset.insert(a);
                else
                {
                    if (!heads.count(uf2.find(a))) cycleset.insert(uf2.find(a));
                    heads[uf2.find(a)].push_back(a);
                }
            }
            vi cycle(all(cycleset));
            if (sz(cycle) <= 2)
            {
                return 0;
            }

            rep(i, sz(cycle))
            {
                int u = cycle[i];
                int v = cycle[(i + 1) % sz(cycle)];
                ans[u][v] = 1;
                ans[v][u] = 1;
            }
            repe(g, heads)
            {
                int p = g.first;
                repe(u, g.second)
                {
                    ans[p][u] = 1;
                    ans[u][p] = 1;
                    p = u;
                }
            }
        }
    }
    build(ans);
	return 1;
}
