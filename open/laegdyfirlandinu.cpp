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
    vvi nums(n, vi(m));
    rep(i, n) rep(j, m) cin >> nums[i][j];

    vector<p2> dirs = { {0,1},{1,0},{-1,0},{0,-1} };
    repp(i, 1, n-1) repp(j, 1, m-1)
    {
        bool good = 1;
        repe(dir, dirs)
        {
            p2 np = p2(i + dir.first, j + dir.second);
            good &= nums[np.first][np.second] > nums[i][j];
        }
        if (good)
        {
            cout << "Jebb";
            return 0;
        }
    }
    cout << "Neibb";

    return 0;
}
