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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;


    int sum = 0;
    rep(i, m) sum += s[i] == '1';

    int ans = 0;
    rep(i, n)
    {
        if (i + m-1 >= n)
        {
            break;
        }
        if (sum==0)
        {
            ans++;
            if (s[i+m-1] == '0') sum++;
            repp(j, i+m-1, min(n, i + m -1+k))
            {
                s[j] = '1';
            }
        }


        sum -= s[i] - '0';
        sum += s[i + m] - '0';
    }
    cout << ans << "\n";
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
