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


signed main()
{
    fast();

    int n, m;
    cin >> n >> m;

    vvi radj(n);
    vi outdeg(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        outdeg[a]++;
        radj[b].push_back(a);
    }

    priority_queue<int> q;
    rep(i, n) if (outdeg[i] == 0) q.push(i);
    vi topo;
    while (sz(q))
    {
        int u = q.top(); q.pop();
        topo.push_back(u);
        repe(e, radj[u]) if (--outdeg[e] == 0) q.push(e);
    }
    reverse(all(topo));
    repe(u, topo) cout << u + 1 << " ";


    return 0;
}
