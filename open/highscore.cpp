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

#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC target("lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("avx2") // SIMD


typedef unsigned long long ull;

void solve()
{
    string sin;
    cin >> sin;
    int n = sz(sin);
    vi s;
    rep(i, n) s.push_back(sin[i] - '0');

    if (s == vi(n, 1))
    {
        cout << 1 << " " << n << " " << 1 << " " << 1 << "\n";
        return;
    }
    int numblocks = (n + 63) / 64;


    auto xo = [](vector<ull>& x, ull ind)
        {
            x[ind / 64] ^= (1ULL << (ind % 64));
        };

    auto construct = [&]()
        {
            vector<ull> blocks(numblocks);
            rep(i, n) if (s[i]) xo(blocks, i);
            return blocks;
        };
    vector<ull> best = construct();

    int bestl = -1, bestr = -1;
    rep(i, n) if (s[i] == 0) bestl = bestr = i;

    vector<ull> working = construct();
    rep(r, n)
    {
        rep(i, sz(working)) working[i] = 0;
        rep(i, n) if (s[i]) xo(working, i);

        int o = n - 1;
        for (int l = r; l >= 0; l--)
        {
            if (s[l]) xo(working, o);

            rep(i, numblocks)
            {
                if (working[i] != best[i])
                {

                    int v = __builtin_ctzll(working[i] ^ best[i]);
                    if (working[i] & (1ULL << v))
                    {
                        best = working;
                        bestl = l;
                        bestr = r;
                    }
                }
            }
            o--;
        }
    }

    cout << 1 << " " << n << " " << bestl + 1 << " " << bestr + 1 << "\n";
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
