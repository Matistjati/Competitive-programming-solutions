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

int binpow(int a, int b, int m) // a^b mod m
{
    a %= m;
    int ret = 1;
    int e = a;
    while (b)
    {
        if (b % 2) ret = (ret * e) % m;
        e = (e * e) % m;
        b >>= 1;
    }

    return ret;
}

ll euclid(ll a, ll b, ll& x, ll& y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}
template<int mod>
struct Mint {
    ll x;
    Mint(ll xx) : x(xx) { x %= mod; x += mod; x %= mod; }
    // No-mod constructor
    Mint(ll xx, bool nope) : x(xx) {}
    Mint() : x(0) {}
    Mint operator+(Mint b) { int y = x + b.x; return { y - (y >= mod) * mod, false }; }
    Mint operator-(Mint b) { int y = x - b.x; return { y + (y < 0) * mod, false }; }
    Mint operator-() { return { -x + mod, false }; }
    Mint operator*(Mint b) { return { x * b.x % mod, false }; }
    Mint operator/(Mint b) { return { x * invert(b).x % mod, false }; }
    Mint invert(Mint a) {
        ll x, y, g = euclid(a.x, mod, x, y);
        assert(g == 1); return { (x + mod) % mod };
    }
    friend ostream& operator<<(ostream& out, const Mint& a) { return out << a.x; }
    friend istream& operator>>(istream& in, Mint& a) { ll val; in >> val; a = Mint(val); return in; }
};
const int mod = int(1e9 + 7);
typedef Mint<mod> Mod;

struct ModFactorial
{
    vi fact;
    ModFactorial(int hi) : fact(hi, 1)
    {
        int v = 1;
        repp(i, 1, hi)
        {
            v *= i;
            v %= mod;
            fact[i] = v;
        }
    }
    inline int operator[](int index) { return fact[index]; }
    inline int choose(int n, int k) { return fact[n] * binpow(fact[k], mod - 2, mod) % mod * binpow(fact[n - k], mod - 2, mod) % mod; } // assumes prime mod
};


signed main()
{
    fast();

    ModFactorial fact(int(3e5 + 10));

    int n, k, s, a;
    cin >> n >> k >> s >> a;

    auto F = [&](int k)
        {
            Mod ans = 0;
            rep(i, min(n, k)+1)
            {
                ans = ans + Mod(fact.choose(n, i)) * Mod(binpow(a*k, n-i, mod)) * Mod(fact.choose(k, i)) * Mod(binpow(s, i, mod));
            }
            return ans;
        };

    cout << F(k) - F(k - 1);



    return 0;
}
