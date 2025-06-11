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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int n, k;
    cin >> n >> k;

    auto query = [](string x)
        {
            cout << "? " << x << endl;
            int resp;
            cin >> resp;
            return resp;
        };

    vector<pair<int, char>> occs;
    rep(i, k)
    {
        occs.emplace_back(query(string(n, i + 'a')), i + 'a');
    }
    sort(all(occs));

    string s = string(occs[0].first, occs[0].second);
    repp(o, 1, k)
    {
        if (occs[o].first == 0) continue;
        char c = occs[o].second;


        string into = string(occs[o].first, occs[o].second);

        for (int i = sz(into); i >= 0; i--)
        {
            int lo = -1;
            int hi = sz(s) + 1;
            while (lo + 1 < hi)
            {
                int mid = (lo + hi) / 2;

                string cop(into);
                string cops(s);

                rep(j, mid)
                {
                    cop.insert(cop.begin() + i, cops.back());
                    cops.pop_back();
                }
                if (sz(cop) == query(cop))
                {
                    lo = mid;
                }
                else hi = mid;
            }

            rep(j, lo)
            {
                into.insert(into.begin() + i, s.back());
                s.pop_back();
            }
        }
        s = into;

    }

    cout << "! " << s;

    return 0;
}
