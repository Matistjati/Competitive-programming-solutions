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

typedef unsigned long long ull;

struct RollingHash
{
    vector<ull> suf, b;
    const ull mod = int(1e9 + 7);
    RollingHash(string& s) : suf(s.size() + 1), b(s.size() + 1)
    {
        ull base = (ull)malloc(10) % mod; // hacking-proof source of random
        if (base < 255) base += 255;
        b[0] = 1;
        b[1] = base;

        for (int i = sz(s) - 1; i >= 0; i--)
        {
            suf[i] = (suf[i + 1] * base + s[i]) % mod;
        }

        repp(i, 2, s.size() + 1)
        {
            b[i] = b[i - 1] * b[1] % mod;
        }
    }

    ull gethash(int l, int r) // hash s[l, r]
    {
        ull rv = (suf[r + 1] * b[r - l + 1]) % mod;
        return suf[l] + mod * (suf[l] < rv) - rv;
    }
};

struct DoubleHash
{
    RollingHash h1;
    RollingHash h2;
    DoubleHash(string& s) : h1(s), h2(s) {}
    ull gethash(int l, int r)
    {
        return (h1.gethash(l, r) << 32) + h2.gethash(l, r);
    }
};

signed main()
{
    fast();

    string s;
    cin >> s;

    DoubleHash h(s);
    rep(i, sz(s)-1)
    {
        int prefsize = i + 1;
        int sufsize = sz(s) - prefsize;
        if (prefsize < sufsize) continue;
        int midlen = sz(s) - 2 * sufsize;
        
        if (midlen == 0) continue;
        if (h.gethash(0, midlen - 1) == h.gethash(sufsize, sufsize + midlen - 1) &&
            h.gethash(prefsize-sufsize, prefsize-1) == h.gethash(sz(s)-sufsize, sz(s)-1)
            )
        {
            cout << "YES\n" << s.substr(0, i + 1);
            return 0;
        }

    }
    cout << "NO\n";

    return 0;
}
