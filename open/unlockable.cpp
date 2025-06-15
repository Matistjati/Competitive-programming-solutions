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

    int n, a;
    cin >> n >> a;
    vi b(n);
    repe(v, b) cin >> v;
    set<int> sb(all(b));
    b = vi(all(sb));

    int ans = 0;
    int ap = 1;
    repp(x, 1, 40)
    {
        ap *= a;
        if (ap > int(1e9)) break;

        repe(v, b) if (v >= ap && v % ap == 0) ans++;
    }
    cout << ans;

    return 0;
}
