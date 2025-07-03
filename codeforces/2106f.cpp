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


void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    bool seen_one = 0;
    int ans = 0;
    int topside = 0;
    int botside = 0;
    rep(i, n)
    {
        char c = s[i];
        if (c=='0')
        {
            topside += i;
            botside += n - i - 1;
        }
        else
        {
            ans = max(ans, topside);
            topside = botside;
            topside++;
            botside = 0;
        }
    }
    ans = max(ans, topside);
    ans = max(ans, botside);

    cout << ans << "\n";
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
