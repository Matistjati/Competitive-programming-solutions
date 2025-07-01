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
#include <__msvc_int128.hpp>
typedef _Signed128 big_signed;
typedef _Unsigned128 big_unsigned;
#else
typedef __int128_t big_signed;
typedef __uint128_t big_unsigned;
#endif

signed main()
{
    fast();

    int a, b, m;
    cin >> a >> b >> m;

    big_signed ans = 1;

    big_signed p = a;
    while (b)
    {
        if (b % 2) ans = (ans * p) % m;
        p = (p * p) % m;
        b >>= 1;
    }

    cout << (int)ans;

    return 0;
}
