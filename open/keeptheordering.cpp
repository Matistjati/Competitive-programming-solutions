#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

#define rep(i, b) for(ll i = 0; i < (b); i++)
#define repp(i, a, b) for(ll i = a; i < (b); i++)
#define repe(i,arr) for (auto& i : arr)
#define all(x) begin(x), end(x)
#define sz(x) ((ll)(x).size())
typedef pair<ll, ll> p2;
typedef vector<ll> vi;
typedef vector<vi> vvi;

vi nums;


#if _LOCAL
#include <__msvc_int128.hpp>
typedef _Signed128 big_signed;
typedef _Unsigned128 big_unsigned;
#else
typedef __int128_t big_signed;
typedef __uint128_t big_unsigned;
#endif

bool square_is_sorted(string s)
{
    big_signed v = stoll(s);
    v *= v;
    big_signed last = 10;
    while (v)
    {
        if (v % 10 > last) return false;
        last = v % 10;
        v /= 10;
    }
    return true;
}

void generate(string& s)
{
    if (sz(s) >= 19) return;
    if (sz(s))
    {
        if (square_is_sorted(s)) nums.push_back(stoll(s));
    }
    char lo = sz(s) ? s.back() : '1';
    repp(c, lo, '9' + 1)
    {
        s.push_back(c);
        generate(s);
        s.pop_back();
    }
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    string s;
    generate(s);
    
    sort(all(nums));

    ll t;
    cin >> t;
    while (t--)
    {
        ll x;
        cin >> x;
        cout << (upper_bound(all(nums), x)-begin(nums)) << "\n";
    }

    return 0;
}
