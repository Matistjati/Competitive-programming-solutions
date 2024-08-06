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

vector<p2> normalize(string s)
{
    char curr = s[0];
    int cnt = 1;
    vector<p2> ret;
    repp(i, 1, sz(s))
    {
        if (s[i]!=curr)
        {
            ret.emplace_back(curr, cnt);
            curr = s[i];
            cnt = 1;
        }
        else
        {
            cnt++;
        }
    }
    ret.emplace_back(curr, cnt);
    return ret;
}

signed main()
{
    fast();

    string a, b;
    getline(cin, a);
    getline(cin, b);

    set<char> sticky;

    vector<p2> aa = normalize(a);
    vector<p2> bb = normalize(b);
    assert(sz(aa) == sz(bb));
    rep(i, sz(aa))
    {
        if (aa[i].second!=bb[i].second)
        {
            sticky.insert(aa[i].first);
        }
    }

    repe(c, sticky) cout << c;

    return 0;
}
