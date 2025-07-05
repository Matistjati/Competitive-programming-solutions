#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
//const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

int fw[31][500*500];

signed main()
{
    fast();

    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    repe(row, grid) cin >> row;

    map<char, p2> dirs;
    dirs['v'] = { 1,0 };
    dirs['^'] = { -1,0 };
    dirs['>'] = { 0,1 };
    dirs['<'] = { 0,-1 };
    rep(i, r) rep(j, c)
    {
        p2 dir = dirs[grid[i][j]];
        p2 p = p2(i + dir.first, j + dir.second);
        fw[0][i * c + j] = p.first * c + p.second;
    }

    repp(k, 1, 31)
    {
        rep(i, r * c)
        {
            fw[k][i] = fw[k - 1][fw[k - 1][i]];
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        int a, b, k;
        cin >> a >> b >> k;
        a--; b--;
        int p = a * c + b;

        rep(i, 30)
        {
            if (k & (1 << i)) p = fw[i][p];
        }
        cout << (p / c)+1 << " " << (p % c)+1 << "\n";
    }

    return 0;
}
