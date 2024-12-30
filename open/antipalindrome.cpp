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

    string x;
    getline(cin, x);
    string f;
    repe(c, x) if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) f.push_back(tolower(c));

    bool good = 0;
    rep(i, sz(f))
    {
        repp(j, 2, sz(f)+1)
        {
            if (i + j - 1 >= sz(f)) continue;
            string s = f.substr(i, j);
            string rev = s;
            reverse(all(rev));
            good |= s == rev;
        }
    }
    cout << (good ? "Palindrome" : "Anti-palindrome");

    return 0;
}
