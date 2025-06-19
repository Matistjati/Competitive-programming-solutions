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

    string t, x;
    cin >> t >> x;
    if (t=="E")
    {
        char p = '$';
        int cnt = -1;
        repe(c, x)
        {
            if (c!=p)
            {
                if (cnt != -1)
                {
                    cout << p << cnt;
                }
                cnt = 0;
                p = c;
            }
            cnt++;
        }
        cout << p << cnt;
    }
    else
    {
        for (int i = 0; i < sz(x); i += 2)
        {
            rep(j, x[i + 1] - '0') cout << x[i];
        }
    }

    return 0;
}
