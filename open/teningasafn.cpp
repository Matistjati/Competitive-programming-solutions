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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int mod = int(1e9 + 7);
int binpow(int a, int b, int m) // a^b mod m
{
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

    int n, k;
    cin >> n >> k;

    ModFactorial fact(k + 10);

    int ans = 0;
    vi bernoulli(k + 1);
    bernoulli[0] = 1;
    rep(r, k + 1)
    {
        if (r)
        {
            int acc = 0;
            rep(i, r)
            {
                acc += fact.choose(r, i) * bernoulli[i] % mod * binpow(r-i+1, mod-2,mod) % mod;
            }
            bernoulli[r] = (1 - acc) % mod;
            bernoulli[r] += mod;
            bernoulli[r] %= mod;
        }
        
        ans = (ans + fact.choose(k+1, r)*binpow(n%mod, k-r+1, mod)%mod * bernoulli[r] % mod) % mod;
    }
    ans = (ans * binpow(k + 1, mod - 2, mod)) % mod;
    cout << ans;

    return 0;
}
