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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    vector<string> grid(8);
    rep(i, 8) cin >> grid[i];
    string moves;
    cin >> moves;
    vector<p2> gr = { {0,1},{-1,0},{0,-1},{1,0} };
    int dir = 0;
    p2 p;
    rep(i, 8)
    {
        rep(j, 8)
        {
            if (grid[i][j] == 'T') p = p2(i, j), grid[i][j] = '.';
        }
    }
    if (p!=p2(7,0))
    {
        cout << "Bug!";
        return 0;
    }
    repe(m, moves)
    {
        p2 d = gr[dir];

        if (m=='L')
        {
            dir++;
            dir %= 4;
        }
        if (m=='R')
        {
            dir--;
            if (dir == -1) dir = 3;
        }
        if (m=='F')
        {
            p = p2(p.first + d.first, p.second + d.second);
            if (p.first<0||p.second<0||p.first>=8||p.second>=8||grid[p.first][p.second]=='C'||grid[p.first][p.second]=='I')
            {
                cout << "Bug!";
                return 0;
            }
        }
        if (m=='X')
        {
            p2 PO = p;
            bool good = 1;

            while (true)
            {
                p2 np = p2(PO.first + d.first, PO.second + d.second);
                if (grid[np.first][np.second]=='C')
                {
                    good = 0;
                    break;
                }
                if (grid[np.first][np.second]=='I')
                {
                    grid[np.first][np.second] = '.';
                    break;
                }
                if (np.first<0||np.second<0||np.first>=8||np.second>=8)
                {
                    good = 0;
                    break;
                }
                PO = np;
                break;
            }

            if (!good)
            {
                cout << "Bug!";
                return 0;
            }
        }
    }

    if (grid[p.first][p.second] == 'D')
    {
        cout << "Diamond!";
    }
    else
    {
        cout << "Bug!";
    }

    return 0;
}
