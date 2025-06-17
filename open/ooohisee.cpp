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

    int r, c;
    cin >> r >> c;
    vector<string> rows(r);
    repe(row, rows) cin >> row;

    int cnt = 0;
    p2 p;
    repp(i, 1, r-1) repp(j, 1, c-1)
    {
        bool good = rows[i][j] == '0';
        repp(dx, -1, 2) repp(dy, -1, 2)
        {
            if (dx == dy && dx == 0) continue;
            good &= rows[i + dx][j + dy] == 'O';
        }
        if (good)
        {
            cnt++;
            p = p2(i, j);
        }
    }
    if (cnt == 1) cout << p.first + 1 << " " << p.second + 1;
    else
    {
        if (cnt == 0) cout << "Oh no!";
        else cout << "Oh no! " << cnt << " locations";
    }

    return 0;
}
