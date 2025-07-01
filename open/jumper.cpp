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

    // brute force shows that if you query ask(x,1),...ask(x,5), and then ask 75 after that, then greedy, you will use at most 15 rounds

    int x;
    cin >> x;

    auto ask = [&](int u, int k)
        {
            cout << "? " << u << " " << k << endl;
            int res;
            cin >> res;
            return res;
        };

    auto ans = [](int x)
        {
            cout << "! " << x << endl;
            exit(0);
        };

    vi known;
    known.push_back(x);

    int k = 5;
    rep(i, k)
    {
        int res = ask(x, i + 1);
        if (res == x)
        {
            ans(known.back());
        }
        known.push_back(res);
    }

    vi candidates;
    repp(i, k, 101)
    {
        candidates.push_back(i);
    }

    int its = 0;
    while (sz(candidates) > 1)
    {
        int bestcost = inf;
        int bestchoice = inf;
        repp(i, k + 1, 101)
        {
            int cost = 0;
            repe(j, candidates)
            {
                if (i % j <= k) continue;
                cost++;
            }
            if (cost < bestcost)
            {
                bestcost = cost;
                bestchoice = i;
            }
        }
        if (its++ == 0) bestchoice = 75;

        int res = ask(x, bestchoice);
        if (find(all(known), res) != known.end())
        {
            auto ind = find(all(known), res) - begin(known);
            ans(ask(x, bestchoice - ind - 1));
        }

        vi newcands;
        repe(c, candidates)
        {
            if (bestchoice % c <= k) continue;
            newcands.push_back(c);
        }
        candidates = newcands;
    }
    ans(ask(x, candidates[0] - 1));

    return 0;
}
