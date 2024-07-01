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

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    rep(i, n) cin >> grid[i];
    vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
    rep(i, n)
    {
        rep(j, m)
        {
            if (j % 2 == i%2 && grid[i][j] == '.')grid[i][j] = 'E';
            if (grid[i][j] == '#') continue;
            bool all_water = 1;

            repe(dir, dirs)
            {
                p2 np = p2(i + dir.first, j + dir.second);
                if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m) continue;
                if (grid[np.first][np.second] == '#') continue;
                all_water = 0;
            }

            if (all_water) grid[i][j] = 'E';
        }
    }
    rep(i, n) cout << grid[i] << "\n";


    return 0;
}
