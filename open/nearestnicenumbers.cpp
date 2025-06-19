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

    int n, d;
    cin >> n >> d;
    int left = 0;

    double ans = 0;
    vector<double> fracs;
    int juice = d;
    rep(i, n)
    {
        double x;
        cin >> x;
        double t = d * x;
        ans += t;
        if (t>1)
        {
            if (floor(t)>juice)
            {
                t -= juice;
                ans -= juice;
                juice = 0;
            }
            else
            {
                double take = floor(t);
                juice -= take;
                ans -= take;
                t -= take;
            }
        }

        fracs.push_back(t);
    }

    sort(all(fracs));

    while (juice && sz(fracs))
    {
        double v = fracs.back();
        fracs.pop_back();
        ans -= v;
        ans += 1 - v;
        juice--;
    }
    while (juice) juice--, ans++;

    cout << fixed << setprecision(15) << ans;

    return 0;
}
