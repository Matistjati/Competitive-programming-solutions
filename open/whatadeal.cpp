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
    vector<p2> trades(n);
    repe(t, trades) cin >> t.first >> t.second;
    sort(all(trades), [](p2 a, p2 b)
        {
            if (a.first * b.second != b.first * a.second)
            {
                return a.first * b.second < b.first * a.second;
            }
            return a.first > b.first;
        });

    repe(t, trades)
    {
        cout << t.first << " " << t.second << '\n';
    }

    return 0;
}
