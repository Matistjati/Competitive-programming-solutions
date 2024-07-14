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

signed main()
{
    fast();

    int n;
    cin >> n;
    int rows = (n + 1) * 2+1;

    vector<string> ans(rows, string(rows, ' '));
    ans[rows / 2][0] = 'x';
    ans[rows / 2][rows-1] = 'x';
    ans[0][rows / 2] = 'x';
    ans[rows-1][rows / 2] = 'x';

    repp(i, 1, n + 1) ans[rows / 2 - i][i] = '/';
    repp(i, 1, n + 1) ans[rows - 1 - i][rows/2+i] = '/';
    repp(i, 1, n + 1) ans[rows / 2 + i][i] = '\\';
    repp(i, 1, n + 1) ans[rows / 2 - i][rows - 1 -i] = '\\';



    rep(i, rows)
    {
        while (sz(ans[i]) && ans[i].back() == ' ') ans[i].pop_back();
        cout << ans[i] << "\n";
    }

    return 0;
}
