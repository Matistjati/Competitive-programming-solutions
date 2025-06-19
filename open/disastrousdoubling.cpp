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

    int n;
    cin >> n;
    vi bacteria(n);
    repe(v, bacteria) cin >> v;
    auto fails = [&]()
        {
            big_signed big = 1;
            rep(i, 61) big *= 2;

            big_signed bact = 2;
            rep(i,n)
            {
                if (bact > big) return false;
                bact -= bacteria[i];
                if (bact < 0) return true;
                bact *= 2;
            }
            return false;
        };

    if (fails())
    {
        cout << "error";
    }
    else
    {
        int mod = int(1e9) + 7;
        int ans = 2;
        rep(i, n)
        {
            ans -= bacteria[i];
            ans += mod;
            ans %= mod;
            ans += mod;
            if (i!=n-1) ans *= 2;
            ans %= mod;
        }
        cout << ans;
    }


    return 0;
}
