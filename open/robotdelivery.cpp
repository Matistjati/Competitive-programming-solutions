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
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
    if (btoa[j] == -1) return 1;
    vis[j] = 1; int di = btoa[j];
    for (int e : g[di])
        if (!vis[e] && find(e, g, btoa, vis)) {
            btoa[e] = di;
            return 1;
        }
    return 0;
}
int dfsMatching(vector<vi>& g, vi& btoa) {
    vi vis;
    repp(i, 0, sz(g)) {
        vis.assign(sz(btoa), 0);
        for (int j : g[i])
            if (find(j, g, btoa, vis)) {
                btoa[j] = i;
                break;
            }
    }
    return sz(btoa) - (int)count(all(btoa), -1);
}
signed main()
{
    fast();
    int r, c, n;
    cin >> r >> c >> n;

    vector<string> grid(r);
    vvi cost(n, vi(n, inf));
    vector<p2> pos;
    map<p2, int> ind;
    rep(i, r)
    {
        cin >> grid[i];
        rep(j, c)
        {
            if (grid[i][j] == 'R')
            {
                pos.emplace_back(i, j);
            }
            if (grid[i][j] == 'P')
            {
                ind[p2(i, j)] = ind.size();
            }
        }
    }

    typedef tuple<int, int, int> p3;
    int j = 0;
    vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
    repe(p, pos)
    {
        queue<p3> q;
        q.emplace(0, p.first, p.second);
        int d = 0;
        vvi vis(r, vi(c));
        while (q.size())
        {
            int d, a, b;
            tie(d, a, b) = q.front();
            q.pop();

            if (vis[a][b]) continue;
            vis[a][b] = 1;

            if (grid[a][b] == 'P')
            {
                cost[j][ind[p2(a, b)]] = d;
            }

            repe(dir, dirs)
            {
                p2 np = p2(a + dir.first, b + dir.second);
                if (np.first < 0 || np.first >= r || np.second < 0 || np.second >= c) continue;
                if (grid[np.first][np.second] == '#') continue;
                q.emplace(d + 1, np.first, np.second);
            }
        }
        j++;
    }

    int lo = 0;
    int hi = int(400 * 400 + 1);
    while (lo + 1 < hi)
    {
        int mid = (lo + hi) / 2;
        bool good = 1;

        vi ans(n, -1);
        vvi edges(n);
        rep(i, n)
        {
            rep(j, n)
            {
                if (cost[i][j] <= mid)
                {
                    edges[i].push_back(j);
                }
            }
        }
        good = dfsMatching(edges, ans) == n;

        if (good) hi = mid;
        else lo = mid;
    }

    cout << hi;

    return 0;
}
