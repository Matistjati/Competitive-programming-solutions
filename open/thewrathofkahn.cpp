// dilworth's theorem
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

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vi> hs; vi H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

    void addEdge(int s, int t, ll cap, ll rcap = 0) {
        if (s == t) return;
        g[s].push_back({ t,sz(g[t]),0,cap });
        g[t].push_back({ s,sz(g[s]) - 1,0,rcap });
    }

    void addFlow(Edge& e, ll f) {
        Edge& back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = sz(g); H[s] = v; ec[t] = 1;
        vi co(2 * v); co[0] = v - 1;
        rep(i, v) cur[i] = g[i].data();
        for (Edge& e : g[s]) addFlow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0) {
                if (cur[u] == g[u].data() + sz(g[u])) {
                    H[u] = 1e9;
                    for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest] + 1)
                        H[u] = H[e.dest] + 1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        rep(i,v) if (hi < H[i] && H[i] < v)
                            --co[H[i]], H[i] = v+1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
            }
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;

    vi can_kill(n);
    vi ind(n, -1);
    int live_ind = 0;

    vvi canreach(n, vi(n));
    rep(i, n) canreach[i][i] = 1;
    vvi edges(n);
    vi indeg(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        canreach[a][b] = 1;
        indeg[b]++;
    }

    vi q;
    rep(i, n) if (indeg[i] == 0) q.push_back(i);

    while (sz(q))
    {
        int u = q.back(); q.pop_back();

        can_kill[u] = 1;
        ind[u] = live_ind++;

        repe(e, edges[u])
        {
            indeg[e]--;
            if (indeg[e]==0)
            {
                q.push_back(e);
            }
        }
    }
    rep(k, n) rep(i, n) rep(j, n) canreach[i][j] |= canreach[i][k] & canreach[k][j];

    int nodecnt = live_ind * 2 + 2;
    PushRelabel flow(nodecnt);

    rep(i, n)
    {
        if (!can_kill[i]) continue;
        flow.addEdge(nodecnt - 2, ind[i], 1);
        flow.addEdge(ind[i] + live_ind, nodecnt - 1, 1);
        rep(j, n)
        {
            if (!can_kill[j] || i == j) continue;
            if (canreach[i][j])
            {
                flow.addEdge(ind[i], ind[j] + live_ind, 1);
            }
        }
    }
    cout << live_ind-flow.calc(nodecnt - 2, nodecnt - 1);

    return 0;
}
