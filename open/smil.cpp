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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    string s;
    cin >> s;

    vi occs;
    rep(i, sz(s)-1)
    {
        if (s[i] == ':' && s[i + 1] == ')') occs.emplace_back(i);
        if (s[i] == ';' && s[i + 1] == ')') occs.emplace_back(i);
    }
    rep(i, sz(s)-2)
    {
        if (s[i] == ':' && s[i + 1] == '-' && s[i+2]==')') occs.emplace_back(i);
        if (s[i] == ';' && s[i + 1] == '-' && s[i+2]==')') occs.emplace_back(i);
    }
    sort(all(occs));
    repe(oc, occs) cout << oc << "\n";

    return 0;
}
