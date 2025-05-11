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

    int k, n;
    cin >> k >> n;
    vector<p2> fn(n);
    for (auto& [a, b] : fn) cin >> a >> b;

    int maxang = 0;
    for (auto& [a, b] : fn) maxang = max(maxang, a);

    int lo = maxang-1;
    int hi = int(1e15);

    while (lo+1<hi)
    {
        int mid = (lo + hi) / 2;
        int numtasks = 0;
        rep(i, n)
        {
            numtasks += (mid - fn[i].first) / fn[i].second;
        }
        if (numtasks >= k)
        {
            hi = mid;
        }
        else lo = mid;
    }
    cout << hi;

    return 0;
}
