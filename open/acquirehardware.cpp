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
    vector<string> grid(r);
    repe(row, grid) cin >> row;

    vvi dp(r, vi(c));
    rep(i, r) rep(j, c)
    {
        if (i != r - 1) dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + (grid[i][j]=='I'));
        if (j != c - 1) dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + (grid[i][j]=='I'));
        if (i!=r-1&&j!=c-1) dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + (grid[i][j]=='I'));
    }

    cout << dp.back().back() + (grid.back().back() == 'I');

    return 0;
}
