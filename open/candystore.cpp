#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    vector<pair<string, string>> names(n);
    rep(i, n) cin >> names[i].first >> names[i].second;

    while (q--)
    {
        string s;
        cin >> s;

        int num_matches = 0;
        pair<string, string> match;
        rep(i, n)
        {
            if (s[0]==names[i].first[0]&&s[1]==names[i].second[0])
            {
                num_matches++;
            }
        }

        if (num_matches > 1)
        {
            cout << "ambiguous";
        }
        else if (num_matches == 1)
        {
            rep(i, n)
            {
                if (s[0] == names[i].first[0] && s[1] == names[i].second[0])
                {
                    cout << names[i].first << " " << names[i].second;
                }
            }
        }
        else cout << "nobody";
        cout << "\n";
    }

    return 0;
}
