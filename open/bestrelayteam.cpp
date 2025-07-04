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
    vector<tuple<double, double, string>> team;
    rep(i, n)
    {
        string name;
        double timef, times;
        cin >> name >> timef >> times;
        team.emplace_back(times, timef, name);
    }
    sort(all(team));

    double best = inf;
    vector<string> bestteam;
    rep(i, n)
    {
        double cost = get<1>(team[i]);
        vector<string> t = { get<2>(team[i]) };
        rep(j, n)
        {
            if (sz(t) == 4) break;
            if (i == j) continue;
            cost += get<0>(team[j]);
            t.push_back(get<2>(team[j]));
        }
        if (cost<best)
        {
            best = cost;
            bestteam = t;
        }
    }
    cout << fixed << setprecision(15) << best << "\n";
    repe(p, bestteam) cout << p << "\n";

    return 0;
}
