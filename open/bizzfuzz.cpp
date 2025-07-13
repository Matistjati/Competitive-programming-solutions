#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

#if _LOCAL
#include <__msvc_int128.hpp>
typedef _Unsigned128 big_u;
#else
typedef __uint128_t big_u;
#endif

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    
    ll a, b, c, d;
    cin >> b >> a >> c >> d;
    auto cnt = [&](big_u hi, big_u d)
        {
            return hi / d;
        };

    auto cnt_inter = [&](big_u hi, big_u lo, big_u d)
        {
            return cnt(hi, d) - cnt(lo - 1, d);
        };

    auto gcd = [](big_u a, big_u b)
        {
            while (b)
            {
                a %= b;
                swap(a, b);
            }
            return a;
        };

    big_u m = c * d / gcd(c,d);

    cout << (ll)cnt_inter(a,b,m) << "\n";

    return 0;
}
