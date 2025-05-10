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

signed main()
{
    fast();

    vvi grid(4,vi(4));
    rep(i, 4) rep(j, 4) cin >> grid[i][j];

    int move;
    cin >> move;

    auto rot_clockwise = [](vvi mat, int times)
        {
            rep(i, times)
            {
                vvi trans = mat;
                rep(i, 4) rep(j, 4) trans[i][j] = mat[j][i];
                rep(i, 4) reverse(all(trans[i]));
                mat = trans;
            }
            return mat;
        };

    int numrot;
    if (move == 0) numrot = 3;
    if (move == 1) numrot = 2;
    if (move == 2) numrot = 1;
    if (move == 3) numrot = 0;

    grid = rot_clockwise(grid, numrot);

    rep(j, 4)
    {
        vi col;
        rep(i, 4) if (grid[3 - i][j] != 0) col.push_back(grid[3-i][j]);
        vi res;
        rep(i, sz(col))
        {
            if (i == sz(col)-1)
            {
                res.push_back(col[i]);
            }
            else
            {
                if (col[i] == col[i + 1])
                {
                    res.push_back(col[i] * 2);
                    i++;
                }
                else res.push_back(col[i]);
            }
        }
        while (sz(res) < 4) res.push_back(0);

        rep(i, 4) grid[3-i][j] = res[i];
    }

    grid = rot_clockwise(grid, (4 - numrot) % 4);

    rep(i, 4)
    {
        rep(j, 4)
        {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }


    return 0;
}
