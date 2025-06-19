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

vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
void all_paths(p2 p, int which_p, int num_free, vector<string>& grid, vector<pair<p2,p2>>& pairs)
{
    if (which_p==sz(pairs))
    {
        if (num_free==0)
        {
            cout << "solvable";
            exit(0);
        }
        return;
    }

    if (p != pairs[which_p].second)
    {
        repe(dir, dirs)
        {
            p2 np = p2(p.first + dir.first, p.second + dir.second);
            if (np.first < 0 || np.second < 0 || np.first >= 4 || np.second >= 4) continue;
            if (grid[np.first][np.second] == '#') continue;
            if (grid[np.first][np.second] != 'W' && np != pairs[which_p].second) continue;
            char save = grid[np.first][np.second];
            grid[np.first][np.second] = '#';
            all_paths(np, which_p, num_free - (save == 'W'), grid, pairs);
            grid[np.first][np.second] = save;
        }
    }
    else
    {
        all_paths(which_p + 1 < sz(pairs) ? pairs[which_p + 1].first : p2(-1, -1), which_p + 1, num_free, grid, pairs);
    }
}

signed main()
{
    fast();

    vector<string> grid(4);
    repe(v, grid) cin >> v;
    map<char, vector<p2>> pos;
    rep(i, 4) rep(j, 4) if (grid[i][j] != 'W') pos[grid[i][j]].emplace_back(i, j);
    vector<pair<p2, p2>> pairs;
    repe(p, pos)
    {
        pairs.emplace_back(p.second[0], p.second[1]);
    }
    int free = 0;
    rep(i, 4) rep(j, 4) free += grid[i][j] == 'W';
    all_paths(pairs[0].first, 0, free, grid, pairs);
    cout << "not solvable";

    return 0;
}
