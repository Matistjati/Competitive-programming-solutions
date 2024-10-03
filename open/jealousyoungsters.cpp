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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();


    int n, m;
    cin >> n >> m;
    if (n > m)
    {
        cout << "impossible";
        return 0;
    }

    vvi first(n, vi(m, inf));

    vvi seconds(n, vi(m));

    int d, e;
    cin >> d >> e;
    vi start(n);
    vi which(n, -1);
    while (e--)
    {
        int t, k, s;
        cin >> s >> k >> t;
        t--;
        k--;

        if (t != -1) first[k][t] = min(first[k][t], s);

        if (which[k] != -1)
        {
            seconds[k][which[k]] += s - start[k];
        }
        which[k] = t;
        start[k] = s;
    }
    rep(i, n)
    {
        if (which[i] != -1)
        {
            seconds[i][which[i]] += d - start[i];
        }
        while (sz(seconds[i]) > n) seconds[i].pop_back();
        while (sz(first[i]) > n) first[i].pop_back();
    }

    vvi proposed(n, vi(n, 0));
    vi engaged(n, -1);

    vi q(n);
    rep(i, n) q[i] = i;

    while (sz(q))
    {
        int c = q.back();
        q.pop_back();

        int best = -1;
        rep(i, n)
        {
            if (proposed[c][i]) continue;
            if (best == -1 || first[c][i] < first[c][best])
            {
                best = i;
            }
        }

        proposed[c][best] = 1;
        if (engaged[best] == -1)
        {
            engaged[best] = c;
        }
        else
        {
            if (seconds[c][best] < seconds[engaged[best]][best])
            {
                q.push_back(engaged[best]);
                engaged[best] = c;
            }
            else q.push_back(c);
        }
    }

    vi which_toy(n);
    rep(i, n) which_toy[engaged[i]] = i;
    repe(u, which_toy) cout << u + 1 << " ";

    return 0;
}
