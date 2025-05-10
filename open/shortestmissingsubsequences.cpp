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

    string cset, s;
    cin >> cset >> s;
    s.insert(s.begin(), 'a'+26);

    int q;
    cin >> q;

    vvi nextc(sz(s), vi(26));

    vi latest(27, sz(s));
    for (int i = sz(s) - 1; i >= 0; i--)
    {
        nextc[i] = latest;
        latest[s[i] - 'a'] = i;
    }

    vi dp(sz(s) + 1, inf);
    repe(c, cset) dp[nextc[0][c - 'a']] = 1;
    rep(i, sz(s))
    {
        repe(c, cset)
        {
            dp[nextc[i][c - 'a']] = min(dp[nextc[i][c - 'a']], dp[i] + 1);
        }
    }

    int shortestlen = dp.back();

    while (q--)
    {
        string k;
        cin >> k;
        if (sz(k) != shortestlen)
        {
            cout << "0\n";
            continue;
        }

        bool breaked = 0;
        int p = 0;
        repe(c, k)
        {
            p = nextc[p][c - 'a'];
            if (p == sz(s))
            {
                breaked = 1;
                break;
            }
        }
        if (!breaked)
        {
            cout << "0\n";
            continue;
        }

        cout << "1\n";
    }


    return 0;
}
