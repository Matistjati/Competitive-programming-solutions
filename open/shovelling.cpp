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

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

typedef tuple<int, int, int> p3;
signed main()
{
    fast();

    int n, m;
    while (cin >> m >> n && n != 0)
    {
        vector<string> grid(n);
        rep(i, n) cin >> grid[i];
        vector<string> gc(grid);
        vector<p2> ppl;
        vvi isspecial(n, vi(m, -1));
        rep(i, n)rep(j, m)
        {
            if (grid[i][j] >= 'A' && grid[i][j] <= 'D') isspecial[i][j] = sz(ppl), ppl.emplace_back(i, j),
                grid[i][j] = '.';
        }
        vector<vvi> dist(4, vvi(n, vi(m)));
        vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
        rep(i, 4)
        {
            deque<p3> q;
            q.emplace_front(0, ppl[i].first, ppl[i].second);
            vvi vis(n, vi(m));
            while (q.size())
            {
                int d, a, b;
                tie(d, a, b) = q.front();
                q.pop_front();
                if (vis[a][b]) continue;
                vis[a][b] = 1;
                dist[i][a][b] = d;
                repe(dir, dirs)
                {
                    p2 np = p2(dir.first + a, dir.second + b);
                    if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m || grid[np.first][np.second] == '#') continue;
                    if (grid[np.first][np.second] == '.') q.emplace_front(d, np.first, np.second);
                    else if (grid[np.first][np.second] == 'o') q.emplace_back(d + 1, np.first, np.second);
                    else assert(0);
                }
            }
        }
        typedef tuple<int, int, int> S;
        S defaultS = { -1,-1,-1 };
        vector<vvi> cost(1 << 4, vvi(n, vi(m, inf)));
        vector<vector<vector<S>>> par(1 << 4, vector<vector<S>>(n, vector<S>(m, defaultS)));
        rep(i, 4)
        {
            cost[1 << i][ppl[i].first][ppl[i].second] = 0;
            par[1 << i][ppl[i].first][ppl[i].second] = S({ -2,-2,-2 });
            
        }

        rep(mask, 1 << 4)
        {
            priority_queue<p3> pq;
            bool any = 0;
            rep(i, n)
            {
                rep(j, m)
                {
                    if (cost[mask][i][j] != inf) pq.emplace(-cost[mask][i][j], i, j);
                }
            }
            vvi vis(n, vi(m));
            while (pq.size())
            {
                int d, a, b;
                tie(d, a, b) = pq.top();
                pq.pop();
                if (vis[a][b]) continue;
                vis[a][b] = 1;

                rep(i, 4)
                {
                    if ((mask & (1 << i)) == 0)
                    {
                        int c = -d + dist[i][a][b] - (grid[a][b] == 'o');
                        if (c < cost[mask | (1 << i)][a][b])
                        {
                            cost[mask | (1 << i)][a][b] = -d + dist[i][a][b] - (grid[a][b] == 'o');
                            par[mask | (1 << i)][a][b] = S({ mask, a,b });
                        }
                        
                    }
                }

                repe(dir, dirs)
                {
                    p2 np = p2(dir.first + a, dir.second + b);
                    if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m || grid[np.first][np.second] == '#') continue;
                    if (grid[np.first][np.second] == '.')
                    {
                        if (-d<cost[mask][np.first][np.second])
                        {
                            par[mask][np.first][np.second] = S({ mask,a,b });
                            cost[mask][np.first][np.second] = -d;
                            pq.emplace(d, np.first, np.second);
                        }
                    }
                    else if (grid[np.first][np.second] == 'o')
                    {
                        if (-d + 1< cost[mask][np.first][np.second])
                        {
                            par[mask][np.first][np.second] = S({ mask,a,b });
                            cost[mask][np.first][np.second] = -d+1;
                            pq.emplace(d-1, np.first, np.second);
                        }
                    }
                    else assert(0);
                }
            }
        }
        int cheapest = inf;
        S bests = S({ -inf,0,0 });
        int finalmask = (1 << 4) - 1;
        rep(i, n) rep(j, m)
        {
            if (cost[finalmask][i][j] < cheapest)
            {
                cheapest = cost[finalmask][i][j];
                bests = { finalmask,i,j };
            }
        }
        //cout << cheapest << "\n";
        int clear = 0;
        while (bests != S({ -2,-2,-2 }))
        {
            int mask, a, b;
            tie(mask, a, b) = bests;
            S p = par[mask][a][b];
            if (get<0>(p) == -2) break;
            if (get<0>(p) == mask)
            {
                char& c = gc[get<1>(p)][get<2>(p)];
                if (c == 'o')
                {
                    clear++;
                    c = '.';
                }
            }
            else
            {
                vector<vector<p2>> ps(n, vector<p2>(m,p2(- 1,-1)));
                deque<pair<p2,p2>> q;
                q.emplace_front(p2(a,b),p2(-2,-2));
                p2 t;
                rep(i, 4)
                {
                    if ((1<<i)==(mask^get<0>(p)))
                    {
                        t = ppl[i];
                    }
                }
                while (q.size())
                {
                    p2 pos, par;
                    tie(pos, par) = q.front();
                    q.pop_front();
                    if (ps[pos.first][pos.second].first != -1) continue;
                    ps[pos.first][pos.second] = par;
                    if (pos ==t)
                    {
                        break;
                    }
                    repe(dir, dirs)
                    {
                        p2 np = p2(pos.first + dir.first, pos.second + dir.second);
                        if (np.first < 0 || np.second < 0 || np.first >= n ||
                            np.second >= m || grid[np.first][np.second] == '#') continue;
                        if (grid[np.first][np.second] == '.' || (grid[np.first][np.second]>='A'
                            &&grid[np.first][np.second]<='D')) q.emplace_front(np, pos);
                        else q.emplace_back(np, pos);
                    }
                }
                p2 pos = t;
                while (pos.first!=-2)
                {
                    if (gc[pos.first][pos.second] == 'o') gc[pos.first][pos.second] = '.',clear++;
                    pos = ps[pos.first][pos.second];
                }
            }
            bests = p;
        }
        assert(clear == cheapest);
        cout << m << " " << n << "\n";
        rep(i, n) cout << gc[i] << "\n";
        cout << "\n";
    }
    cout << "0 0";

    return 0;
}
