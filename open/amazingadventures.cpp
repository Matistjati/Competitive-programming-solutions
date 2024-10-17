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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
    struct edge {
        int from, to, rev;
        ll cap, cost, flow;
    };
    int N;
    vector<vector<edge>> ed;
    vi seen;
    vector<ll> dist, pi;
    vector<edge*> par;

    MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

    void addEdge(int from, int to, ll cap, ll cost) {
        if (from == to) return;
        ed[from].push_back(edge{ from,to,sz(ed[to]),cap,cost,0 });
        ed[to].push_back(edge{ to,from,sz(ed[from]) - 1,0,-cost,0 });
    }

    void path(int s) {
        fill(all(seen), 0);
        fill(all(dist), INF);
        dist[s] = 0; ll di;

        priority_queue<pair<ll, int>> q;
        q.push({ 0, s });

        while (!q.empty()) {
            s = q.top().second; q.pop();
            seen[s] = 1; di = dist[s] + pi[s];
            for (edge& e : ed[s]) if (!seen[e.to]) {
                ll val = di - pi[e.to] + e.cost;
                if (e.cap - e.flow > 0 && val < dist[e.to]) {
                    dist[e.to] = val;
                    par[e.to] = &e;
                    q.push({ -dist[e.to], e.to });
                }
            }
        }
        repp(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
    }

    pair<ll, ll> maxflow(int s, int t) {
        ll totflow = 0, totcost = 0;
        while (path(s), seen[t]) {
            ll fl = INF;
            for (edge* x = par[t]; x; x = par[x->from])
                fl = min(fl, x->cap - x->flow);

            totflow += fl;
            for (edge* x = par[t]; x; x = par[x->from]) {
                x->flow += fl;
                ed[x->to][x->rev].flow -= fl;
            }
        }
        repp(i, 0, N) for (edge& e : ed[i]) totcost += e.cost * e.flow;
        return { totflow, totcost / 2 };
    }

    // If some costs can be negative, call this before maxflow:
    void setpi(int s) { // (otherwise, leave this out)
        fill(all(pi), INF); pi[s] = 0;
        int it = N, ch = 1; ll v;
        while (ch-- && it--)
            repp(i, 0, N) if (pi[i] != INF)
            for (edge& e : ed[i]) if (e.cap)
                if ((v = pi[i] + e.cost) < pi[e.to])
                    pi[e.to] = v, ch = 1;
        assert(it >= 0); // negative cost cycle
    }
};

void dfs(int u, int sink, vi& path, MCMF& flow)
{
    if (u == sink) return;
    repe(e, flow.ed[u])
    {
        if (e.flow > 0)
        {
            e.flow = 0;
            path.push_back(e.to);
            dfs(e.to, sink, path, flow);
            return;
        }
    }
}

signed main()
{
	fast();

    int r, c;
    while (cin >> r >> c && r+c)
    {
        p2 start, forbidden, mid, goal;
        cin >> start.first >> start.second;
        cin >> mid.first >> mid.second;
        cin >> goal.first >> goal.second;
        cin >> forbidden.first >> forbidden.second;
        start.first--, start.second--, mid.first--, mid.second--;
        goal.first--, goal.second--, forbidden.first--, forbidden.second--;

        int numnodes = 2 * r * c + 2;
        MCMF flow(numnodes);
        int source = numnodes - 2;
        int sink = numnodes - 1;

        flow.addEdge(source, 2 * (start.first * c + start.second), 1, 0);
        flow.addEdge(source, 2 * (goal.first * c + goal.second), 1, 0);
        flow.addEdge(2 * (mid.first * c + mid.second), sink, 2, 0);

        vector<p2> dirs = { {0,1},{1,0},{0,-1},{-1,0} };
        rep(i, r)
        {
            rep(j, c)
            {
                if (p2(i, j) == forbidden) continue;
                flow.addEdge(2 * (i * c + j), 2 * (i * c + j) + 1, 1, 1);
                repe(dir, dirs)
                {
                    p2 np = p2(i + dir.first, j + dir.second);
                    if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= c) continue;
                    flow.addEdge(2 * (i * c + j) + 1, 2 * (np.first * c + np.second), 1, 0);
                }
            }
        }

        if (flow.maxflow(source, sink).first == 2)
        {
            cout << "YES\n";
            vi p1, p2;
            dfs(source, sink, p1, flow);
            dfs(source, sink, p2, flow);
            p1.pop_back();
            p2.pop_back();

            bool first = find(all(p1), 2 * (start.first * c + start.second)) != p1.end();
            if (!first) swap(p1, p2);
            vector<pair<int,int>> ans;

            repe(u, p1)
            {
                if (u % 2 == 1) continue;
                u /= 2;
                ans.emplace_back(u / c, u % c);
            }
            reverse(all(p2));
            repe(u, p2)
            {
                if (u % 2 == 1) continue;
                u /= 2;
                ans.emplace_back(u / c, u % c);
            }
            string moves = "";
            map<pair<int, int>, char> dirs;
            dirs[make_pair(1, 0)] = 'U';
            dirs[make_pair(-1, 0)] = 'D';
            dirs[make_pair(0, 1)] = 'R';
            dirs[make_pair(0, -1)] = 'L';

            repp(i, 1, sz(ans))
            {
                moves += dirs[make_pair(ans[i].first - ans[i - 1].first, ans[i].second - ans[i - 1].second)];
            }

            cout << moves << "\n";
        }
        else cout << "NO\n";
    }

	return 0;
}
