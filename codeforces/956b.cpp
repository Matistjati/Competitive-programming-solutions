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


void solve()
{
    int n, m;
    cin >> n >> m;
    vvi a(n,vi(m));
    vvi b(n, vi(m));

    rep(i, n)
    {
        string s;
        cin >> s;
        rep(j, m) a[i][j] = s[j] - '0';
    }
    rep(i, n)
    {
        string s;
        cin >> s;
        rep(j, m) b[i][j] = s[j] - '0';
    }


    vector<vector<int>> diff(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            diff[i][j] = (b[i][j] - a[i][j] + 3) % 3;
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            // Try to fix the top-left element (i, j) to match
            while (diff[i][j] != 0) {
                if (diff[i][j] == 2) {
                    // Apply an operation that adds 1 mod 3 to (i, j) and (i+1, j+1)
                    // and adds 2 mod 3 to (i+1, j) and (i, j+1)
                    diff[i][j] = (diff[i][j] + 1) % 3;
                    diff[i + 1][j + 1] = (diff[i + 1][j + 1] + 1) % 3;
                    diff[i + 1][j] = (diff[i + 1][j] + 2) % 3;
                    diff[i][j + 1] = (diff[i][j + 1] + 2) % 3;
                }
                else if (diff[i][j] == 1) {
                    // Apply an operation that adds 2 mod 3 to (i, j) and (i+1, j+1)
                    // and adds 1 mod 3 to (i+1, j) and (i, j+1)
                    diff[i][j] = (diff[i][j] + 2) % 3;
                    diff[i + 1][j + 1] = (diff[i + 1][j + 1] + 2) % 3;
                    diff[i + 1][j] = (diff[i + 1][j] + 1) % 3;
                    diff[i][j + 1] = (diff[i][j + 1] + 1) % 3;
                }
            }
        }
    }

    // After processing all possible 2x2 subrectangles, we need to check if all values are 0
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (diff[i][j] != 0) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }


    return 0;
}
