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
#include <__msvc_int128.hpp>

typedef _Unsigned128 bigint;
#else
typedef __uint128_t bigint;
#endif

const bigint mod = bigint((int)1e10);
bigint binpow(int a, int b)
{
    bigint ret = 1;
    bigint m = a;
    while (b)
    {
        if (b % 2) ret = ret*m % mod;
        m = (m*m) % mod;
        b >>= 1;
    }
    return ret;
}

signed main()
{
    fast();

    int n;
    cin >> n;
    bigint ans = 0;
    repp(i, 1, n + 1) ans = (ans + binpow(i, i)) % mod;
    cout << (int)ans;

    return 0;
}
