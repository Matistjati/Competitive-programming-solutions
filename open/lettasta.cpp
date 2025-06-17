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

    int c, r;
    cin >> c >> r;
    vector<pair<int, string>> problems(c);
    repe(prob, problems) cin >> prob.second;

    rep(i, r)
    {
        rep(j, c)
        {
            int x;
            cin >> x;
            problems[j].first += x;
        }
    }
    sort(all(problems));
    reverse(all(problems));
    cout << problems[0].second;

    return 0;
}
