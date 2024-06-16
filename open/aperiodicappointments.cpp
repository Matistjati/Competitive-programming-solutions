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
#define __builtin_popcountll popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

int count(int n, int k)
{
    if (n <= k) return 0;
    int ret = 0;
    int u = k;
    int numones = 0;
    rep(i, k - 1)
    {
        if ((u+1)*k>=n)
        {
            int d = n / (u+1);
            ret += (numones+1) * d;
            ret += count(n % (u+1), k);
            break;
        }
        numones++;
        numones *= k;
        u++;
        u *= k;
    }

    return ret;
}

signed main()
{
    fast();

    int n, k;
    cin >> n >> k;
    if (n<=k)
    {
        cout << 0;
        return 0;
    }
    // bruteforce for finding pattern
    /*string s;
    rep(i, k) s += "0";

    while (sz(s)<n)
    {
        bool any = 0;
        reverse(all(s));
        repp(tl, 1, sz(s)+1)
        {
            string t = s.substr(0, tl);
            string tk;
            rep(i, k) tk += t;
            if (sz(tk) > size(s)) break;
            bool match = 1;
            rep(i, sz(tk)) match &= tk[i] == s[i];
            any |= match;
        }
        reverse(all(s));
        s += (any ? "1" : "0");
    }
    cout << s << "\n";
    int onecnt = 0;
    rep(i, sz(s)) onecnt += s[i] == '1';
    cout << onecnt << "\n";*/

    int u = k;
    int numones = 0;
    bool contained = 0;
    rep(i, k - 1)
    {
        if (u>=n)
        {
            contained = 1;
            break;
        }
        u++;
        u *= k;
        if (u >= n)
        {
            contained = 1;
            break;
        }
    }
    
    int ans = 0;
    if (!contained)
    {
        ans += n - u;
        n = u;
    }

    cout << ans+count(n,k);

    return 0;
}
