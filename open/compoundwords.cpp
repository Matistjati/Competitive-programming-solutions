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

    vector<string> all;
    string word;
    while (cin >> word)
    {
        all.push_back(word);
    }

    set<string> ans;
    rep(i, sz(all)) rep(j, sz(all))
    {
        if (i != j) ans.insert(all[i] + all[j]);
    }
    repe(w, ans) cout << w << "\n";

    return 0;
}
