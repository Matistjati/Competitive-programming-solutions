#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

signed main()
{
    fast();

    int n;
    cin >> n;
    vector<p2> intervals(n);
    repe(i, intervals) cin >> i.first >> i.second;
    sort(all(intervals), [](p2 a, p2 b)
        {
            return a.second < b.second;
        });

    int ans = 0;

    int r = -1;
    repe(i, intervals)
    {
        if (i.first >= r) ans++, r = i.second;
    }

    cout << ans;

    return 0;
}
