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

    vi result(m);
    vector<vector<p2>> trades(m);
    vi numunknowns(m);
    vvi waitingforme(n);
    rep(i, m)
    {
        int what, k;
        cin >> what >> k;
        result[i] = what;
        vector<p2> trade(k);
        rep(j, k) cin >> trade[j].first >> trade[j].second, waitingforme[trade[j].second].push_back(i);
        numunknowns[i] = sz(trade);
        trades[i] = trade;
    }

    const int UNKNOWN = inf;
    vi price(n, UNKNOWN);

    priority_queue<p2> pq;

    auto finalize_price = [&](int u, int p)
        {
            price[u] = p;
            repe(w, waitingforme[u])
            {
                numunknowns[w]--;
                if (numunknowns[w] == 0)
                {
                    int cost = 0;
                    repe(u, trades[w])
                    {
                        cost += u.first * price[u.second];
                    }
                    pq.emplace(-cost, result[w]);
                }
            }
        };
    finalize_price(0, 1);

    while (sz(pq))
    {
        int p, u;
        tie(p, u) = pq.top();
        pq.pop();

        if (price[u] != UNKNOWN) continue;

        finalize_price(u, -p);
    }

    cout << price.back();

    return 0;
}
