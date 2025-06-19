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

    int n;
    cin >> n;

    int budget = n * 10 + 100;

    int ans = 0;

    auto ask = [&ans](p2 p)
        {
            cout << "? " << p.first + 1 << " " << p.second + 1 << endl;
            int resp;
            cin >> resp;
            ans = max(ans, resp);
            return resp;
        };

    p2 p;
    int best = -1;

    mt19937 rng(10);
    uniform_int_distribution<int> dist(0, n - 1);
    rep(i, budget / 2)
    {
        p2 pos = p2(dist(rng), dist(rng));
        int h = ask(pos);
        if (h > best)
        {
            best = h;
            p = pos;
        }
    }

    best = ask(p);
    vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
    p2 prev = p2(-1, -1);
    rep(i,budget/2)
    {
        vector<pair<int, p2>> options;
        repe(dir, dirs)
        {
            p2 np = p2(dir.first + p.first, dir.second + p.second);
            if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= n) continue;
            if (np == prev) continue;
            int h = ask(np);
            if (h < best) continue;
            options.emplace_back(h, np);
        }
        sort(all(options));
        reverse(all(options));
        if (options.empty()) break;
        prev = p;
        p = options[0].second;
        best = options[0].first;
        ans = max(ans, best);
    }
    cout << "! " << ans;


    return 0;
}
