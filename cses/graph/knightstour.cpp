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
#define __builtin_clz 
#define assert(x) if (!(x)) __debugbreak()
#endif

vector<p2> deltas = { {1,2},{-1,2},{1,-2},{-1,-2},{2,1},{-2,1},{2,-1},{-2,-1} };
void solve(p2 pos, int d, vvi& vis)
{
    
    assert(vis[pos.first][pos.second] == -1);
    vis[pos.first][pos.second] = d;

    if (d == 64)
    {
        rep(i, 8)
        {
            rep(j, 8)
            {
                cout << vis[i][j] << " ";
            }
            cout << "\n";
        }
        exit(0);
    }

    vector<pair<int,p2>> moves;
    
    repe(d, deltas)
    {
        p2 np = p2(pos.first + d.first, pos.second + d.second);
        if (np.first < 0 || np.second < 0 || np.first >= 8 || np.second >= 8) continue;
        if (vis[np.first][np.second] != -1) continue;
        int cnt=0;
        repe(move, deltas)
        {
            p2 npp = p2(np.first + move.first, np.second + move.second);
            if (npp.first < 0 || npp.second < 0 || npp.first >= 8 || npp.second >= 8) continue;
            if (vis[npp.first][npp.second] != -1) continue;
            cnt++;
        }
        moves.emplace_back(cnt, np);
    }

    sort(all(moves));
    repe(m, moves)
    {
        solve(m.second, d + 1, vis);
    }

    vis[pos.first][pos.second] = -1;
}

signed main()
{
    fast();

    p2 pos;
    cin >> pos.second >> pos.first;
    pos.first--;
    pos.second--;
    vvi vis(8, vi(8, -1));
    solve(pos, 1, vis);

    return 0;
}
