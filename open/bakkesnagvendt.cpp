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

typedef unsigned long long ull;
struct RollingHash
{
    vi suf, b;
    int mod;
    RollingHash(string& s, ull base = 131, ull mod = 1e9 + 7) : mod(mod), suf(s.size() + 1), b(s.size() + 1)
    {
        b[0] = 1;
        b[1] = base;

        for (int i = sz(s) - 1; i >= 0; i--)
        {
            suf[i] = ((ll)suf[i + 1] * base + s[i]) % mod;
        }

        repp(i, 2, s.size() + 1)
        {
            b[i] = (ll)b[i - 1] * b[1] % mod;
        }
    }

    ull gethash(int l, int r) // get for s in interval [l, r]
    {
        ll v = suf[l] - (ll)suf[r + 1] * b[r - l + 1];
        // Make sure that v is within [0, mod)
        v %= mod;
        v += mod;
        v %= mod;

        return v;
    }
};

const ull mod = int(1e9 + 7);
struct DoubleHash
{
    RollingHash h1;
    RollingHash h2;
    DoubleHash(string& s) : h1(s, 157, mod), h2(s, 131, mod) {}
    ull gethash(int l, int r)
    {
        ull hash = ((ull)h1.gethash(l, r) << 32) + h2.gethash(l, r);
        return hash;
    }
};

signed main()
{
    fast();

    string a, b;
    cin >> a >> b;

    // Remove longest common suffix
    int n = sz(a);
    while (sz(a) && a.back() == b.back())
    {
        a.pop_back();
        b.pop_back();
    }
    n = sz(b);
    if (n == 0)
    {
        cout << "1";
        return 0;
    }

    DoubleHash ha(a);
    DoubleHash hb(b);

    // find longest prefix of a that is suffix of b
    vi lcp1;
    rep(i, n)
    {
        if (ha.gethash(0, i) == hb.gethash(n - 1 - i, n - 1))
        {
            lcp1.push_back(i);
        }
    }
    vi lcp2;
    rep(i, n)
    {
        if (ha.gethash(n - 1 - i, n - 1) == hb.gethash(0, i))
        {
            lcp2.push_back(i);
        }
    }
    reverse(all(lcp1));
    while (sz(lcp1) > 2) lcp1.pop_back();
    reverse(all(lcp2));
    while (sz(lcp2) > 2) lcp2.pop_back();

    repe(a, lcp1)
    {
        repe(b, lcp2)
        {
            assert(ha.gethash(0, a) == hb.gethash(n - 1 - a, n - 1));
            assert(hb.gethash(0, b) == ha.gethash(n - 1 - b, n - 1));
            int h = n - 1 - b - 1;
            if (a == h)
            {
                cout << "1";
                return 0;
            }
            if (a + 1 > h) continue;
            if (ha.gethash(a + 1, h) == hb.gethash(b + 1, n - 1 - a - 1))
            {
                cout << "1";
                return 0;
            }
        }
    }

    cout << "0";

    return 0;
}
