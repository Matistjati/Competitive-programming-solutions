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
    string t;
    cin >> n >> t;
    vector<p2> rice(n);
    repe(r, rice) cin >> r.first >> r.second;
    if (t == "storlek") repe(r, rice) swap(r.first, r.second);

    int best = 0;
    repp(i, 1, n)
    {
        auto [a, b] = rice[i];
        if (a+b > rice[best].first +rice[best].second || (a + b == rice[best].first + rice[best].second && a > rice[best].first)) best = i;
    }
    cout << best+1;

    return 0;
}
