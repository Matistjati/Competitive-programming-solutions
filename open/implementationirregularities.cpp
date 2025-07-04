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
    vector<p2> result(n);
    rep(i, n) cin >> result[i].second;
    rep(i, n) cin >> result[i].first;
    sort(all(result));

    int lo = -1;
    int hi = int(1e9)+10;
    while (lo+1<hi)
    {
        int mid = (lo + hi) / 2;

        bool good = 1;

        int last = 0;
        int juice = 0;
        rep(i, n)
        {
            if (result[i].first == -1) continue;
            int tim = result[i].first - last;
            juice += mid * tim;
            last = result[i].first;

            if (juice < result[i].second)
            {
                good = 0;
                break;
            }
            juice -= result[i].second;
        }

        if (good) hi = mid;
        else lo = mid;
    }
    cout << hi << "\n";

    return 0;
}
