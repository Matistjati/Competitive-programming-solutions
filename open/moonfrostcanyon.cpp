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

signed main()
{
    fast();

    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    rep(i, r) cin >> grid[i];

    vector<p2> dirs = { {0,2},{1,2},{-1,2},
                        {0,-2},{1,-2},{-1,-2},
                        {2, -1},{2,0},{2,1},
                        {-2,-1},{-2,0},{-2,1} };
    rep(i, r) rep(j, c)
    {
        if (grid[i][j] == '.')
        {
            p2 center = p2(i + 1, j + 1);
            set<int> colors = { 1,2,3,4 };
            repe(dir, dirs)
            {
                p2 np = p2(center.first + dir.first, center.second + dir.second);
                if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= c) continue;
                if (grid[np.first][np.second] != '.' && grid[np.first][np.second] != '*') colors.erase(grid[np.first][np.second] - '0');
            }
            assert(sz(colors));
            int c = *begin(colors) + '0';
            
            grid[center.first][center.second] = c;
            grid[center.first + 1][center.second] = c;
            grid[center.first - 1][center.second] = c;
            grid[center.first][center.second + 1] = c;
            grid[center.first][center.second - 1] = c;
            grid[center.first - 1][center.second - 1] = c;
            grid[center.first + 1][center.second - 1] = c;
            grid[center.first - 1][center.second + 1] = c;
            grid[center.first + 1][center.second + 1] = c;
        }
    }
    rep(i, r) cout << grid[i] << "\n";

    return 0;
}
