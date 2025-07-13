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

map<int, int> dp(int u, vvi & adj, vi & value)
{
    map<int, int> ret;

    repe(e, adj[u])
    {
        map<int, int> c = dp(e, adj, value);
        if (sz(c) > sz(ret)) swap(c, ret);
        repe(u, c) ret[u.first] += u.second;
    }

    int v = value[u];

    if (v>=0)
    {
        ret[0] += v;
    }
    else
    {
        int s = -v;
        int moneys = v;

        while (sz(ret) && (moneys < 0 || begin(ret)->first <= s))
        {
            s = max(s, begin(ret)->first - moneys);
            moneys += begin(ret)->second;
            ret.erase(ret.begin());
        }

        if (moneys>0)
        {
            ret[s] += moneys;
        }
    }


    return ret;
}


signed main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, s;
    cin >> n >> s;

    vi nodevalue(n+1);
    vvi adj(n+1);
    vi roots;
    rep(i, n)
    {
        int p, v;
        cin >> v >> p;
        nodevalue[i+1] = v;
        adj[p].push_back(i+1);
    }

    int moneys = s;
    repe(s, dp(0, adj, nodevalue))
    {
        if (moneys>=s.first)
        {
            moneys += s.second;
        }
    }
    cout << moneys-s;


    return 0;
}
