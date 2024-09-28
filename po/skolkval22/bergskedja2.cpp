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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


int n, m;
typedef pair<int, int> p2;
vector<p2> directions = { {0,1},{0,-1},{1,0},{-1,0} };

typedef tuple<int, int, int> p3;
int solve_max(vvi num_neighbours)
{
    priority_queue<p3> q;
    rep(i, n) rep(j, m) if (num_neighbours[i][j] == 0) q.emplace(p2(i,j)!=p2(0,0), i, j);

    int ans = 0;
    while (sz(q))
    {
        int _, r, c;
        tie(_, r, c) = q.top();
        q.pop();

        if (_ == 0)
        {
            return ans;
        }
        ans++;

        for (auto dir : directions)
        {
            p2 np = p2(r + dir.first, c + dir.second);
            if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m) continue;
            num_neighbours[np.first][np.second]--;
            if (num_neighbours[np.first][np.second]==0)
            {
                q.emplace(np!=p2(0,0), np.first, np.second);
            }
        }
    }
}

int solve_min(vvi grid)
{
    vvi indeg(n, vi(m));
    rep(i, n) rep(j, m)
    {
        int num_corners = 0;
        for (auto dir : directions)
        {
            p2 np = p2(i + dir.first, j + dir.second);
            if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m) continue;
            num_corners++;
        }
        indeg[i][j] = num_corners - grid[i][j];
    }
    return n*m-solve_max(indeg);
}

signed main()
{
    fast();

    cin >> n >> m;
    vvi grid(n, vi(m));
    rep(i, n)
    {
        string row;
        cin >> row;
        rep(j, m) grid[i][j] = row[j] - '0';
    }

    cout << solve_min(grid) << " " << solve_max(grid)+1;


    return 0;
}
