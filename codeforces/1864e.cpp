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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

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
typedef Mint<998244353> Mod;

struct Node
{
    Node *l=0, *r=0;

    signed cnt = 0;
    Node() {}

    void insert(int v, int ind)
    {
        cnt++;
        if (ind==-1)
        {
            return;
        }
        Node*& which = (v & (1LL << ind)) ? l : r;
        if (!which) which = new Node();
        which->insert(v, ind - 1);
    }

    
    Mod calc(int ones, bool seen_1)
    {
        Mod ret = 0;
        if (!l && !r) ret = ret + ones * cnt * cnt;

        if (l && r) ret = ret + Mod(ones) * Mod(l->cnt) * Mod(r->cnt)*2 + Mod(l->cnt)*Mod(r->cnt);
        if (l) ret = ret + l->calc(ones + 1, 1);
        if (r) ret = ret + r->calc(ones, seen_1);

        return ret;
    }
};


void solve()
{
    int n;
    cin >> n;
    vi nums(n);
    rep(i, n) cin >> nums[i];

    Node* root = new Node();

    rep(i, n)
    {
        root->insert(nums[i], 31);
    }

    Mod ans = root->calc(1, 0);

    ans = ans / (Mod(n) * Mod(n));
    cout << ans << "\n";
}

signed main()
{
    fast();

    //ifstream in("c:\\users\\matis\\source\\repos\\cprog\\x64\\debug\\in.txt");
    //cin.rdbuf(in.rdbuf());

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }


    return 0;
}
