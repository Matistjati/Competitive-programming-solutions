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

    int r, c;
    cin >> r >> c;
    vvi freq(c, vi(26));
    rep(i, r)
    {
        string x;
        cin >> x;
        rep(j, c) freq[j][x[j] - 'a']++;
    }

    rep(i, c)
    {
        vector<p2> occs;
        rep(j, 26) occs.emplace_back(-freq[i][j], j);
        sort(all(occs));
        cout << ((char)(occs[0].second+'a'));
    }

    return 0;
}
