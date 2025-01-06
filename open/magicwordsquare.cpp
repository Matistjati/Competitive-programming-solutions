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

inline int hashstring(char a, char b, char c)
{
    return (a - 'a') + (b - 'a') * 26 + (c - 'a') * 26 * 26;
}

inline int hashstring(string a)
{
    return (a[0] - 'a') + (a[1] - 'a') * 26 + (a[2] - 'a') * 26 * 26;
}

signed main()
{
    fast();

    vi seenhashes(int(1e5));
    int n;
    cin >> n;
    vector<string> words(n);
    rep(i, n) cin >> words[i];
    rep(i, n) seenhashes[hashstring(words[i])] = 1;

    int ans = 0;
    int version = 10;
    int seen[26];
    rep(i, 26) seen[i] = 0;
    rep(i, n)
    {
        rep(j, n)
        {
            rep(k, n)
            {
                string& a = words[i];
                string& b = words[j];
                string& c = words[k];
                bool good = 1;
                version++;
                repe(u, a) good &= seen[u-'a'] != version, seen[u-'a'] = version;
                repe(u, b) good &= seen[u-'a'] != version, seen[u-'a'] = version;
                repe(u, c) good &= seen[u-'a'] != version, seen[u-'a'] = version;
                good &= seenhashes[hashstring(a[0], b[0], c[0])];
                good &= seenhashes[hashstring(a[1], b[1], c[1])];
                good &= seenhashes[hashstring(a[2], b[2], c[2])];
                good &= seenhashes[hashstring(a[0], b[1], c[2])];
                good &= seenhashes[hashstring(a[2], b[1], c[0])];
                ans += good;
            }
        }
    }
    cout << ans;

    return 0;
}
