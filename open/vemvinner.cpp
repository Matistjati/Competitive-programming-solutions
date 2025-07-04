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

    vector<vector<char>> grid(3, vector<char>(3));
    rep(i, 3) rep(j, 3) cin >> grid[i][j];

    auto check_color = [&](char c)
        {
            rep(i, 3)
            {
                bool good = 1;
                rep(j, 3) good &= grid[i][j] == c;
                if (good) return 1;
            }
            rep(i, 3)
            {
                bool good = 1;
                rep(j, 3) good &= grid[j][i] == c;
                if (good) return 1;
            }
            bool good = 1;
            rep(i, 3) good &= grid[i][i] == c;
            if (good) return 1;
            good = 1;
            rep(i, 3) good &= grid[i][2-i] == c;
            if (good) return 1;

            return 0;
        };

    bool johan = check_color('X');
    bool abdullah = check_color('O');

    if (johan) cout << "Johan ";
    else if (abdullah) cout << "Abdullah ";
    else cout << "ingen ";
    cout << "har vunnit";

    return 0;
}
