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

    int n, l, t;
    cin >> n >> l >> t;
    int words = l * t;
    
    vector<string> ans;
    rep(i, n)
    {
        string x;
        cin >> x;
        if (sz(x)+1>words)
        {
            cout << "/ff\n";
            return 0;
        }

        if (ans.empty())
        {
            ans.push_back(x);
            continue;
        }

        if (sz(ans.back())+2+sz(x)<=words)
        {
            ans.back() += " " + x;
        }
        else
        {
            ans.back() += "\n";
            ans.push_back(x);
        }
    }
    repe(w, ans) cout << w;

    return 0;
}
