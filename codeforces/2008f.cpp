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

// Status: all operations but / are tested
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
    Mint(ll xx, bool nope) : x(xx) { }
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
typedef Mint<int(1e9 + 7)> Mod;

void solve()
{
    int n;
    cin >> n;

    vector<Mod> nums(n);
    rep(i, n) cin >> nums[i];
    Mod s = 0;
    rep(i, n) s = s + nums[i];
    Mod ans = 0;
    Mod mn = n;
    rep(i, n)
    {
        s = s - nums[i];
        ans = ans + nums[i] * s;
    }
    cout << ans / (mn * (mn - 1) / 2) << "\n";
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
