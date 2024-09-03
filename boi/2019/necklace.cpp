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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif
typedef uint64_t ull;
struct H {
    ull x; H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) {
        auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64);
    }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator!=(H o) const { return !(*this == o); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3; // (order ~ 3e9; random also ok)

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(sz(str) + 1), pw(ha) {
        pw[0] = 1;
        repp(i, 0, sz(str))
            ha[i + 1] = ha[i] * C + str[i],
            pw[i + 1] = pw[i] * C;
    }
    H hashInterval(int a, int b) { // hash [a, b)
        b++;
        return ha[b] - ha[a] * pw[b - a];
    }
};

pair<int, p2> best(string a, string b, bool rev)
{
    int ret = -1;
    p2 r = p2(-1, -1);
    HashInterval h1(a);
    HashInterval h2(b);
    mt19937 rng;
    uniform_int_distribution<int> da(0, sz(a) - 1);
    uniform_int_distribution<int> db(0, sz(b) - 1);
    int l = 10;
    auto start = chrono::high_resolution_clock::now();

    while (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() < 700)
    {
        int aa = da(rng);
        int ab = aa;
        int ba = db(rng);
        int bb = ba;

        int lo = -1;
        int hi = 4001;
        while (lo + 1 < hi)
        {
            int mid = (lo + hi) / 2;
            if (aa + mid >= sz(a) || ba + mid >= sz(b) || h1.hashInterval(aa, aa + mid) != h2.hashInterval(ba, ba + mid))
            {
                hi = mid;
            }
            else lo = mid;
        }
        aa += hi;
        ba += hi;

        lo = -1;
        hi = 4001;
        while (lo + 1 < hi)
        {
            int mid = (lo + hi) / 2;
            if (ab - 1 - mid < 0 || bb - 1 - mid < 0 || h1.hashInterval(ab - 1 - mid, ab - 1) != h2.hashInterval(bb - 1 - mid, bb - 1))
            {
                hi = mid;
            }
            else lo = mid;
        }
        ab -= hi;
        bb -= hi;

        int starta = aa;
        int startb = bb;
        if (rand() % 2)
        {
            starta = ab;
            startb = ba;
        }

        int rp = 0;
        repp(rlen, 1, l * 2 + 1)
        {
            int i = starta - rlen;
            int j = startb;
            if (i < 0 || j + rlen - 1 >= sz(b)) break;
            bool good = h1.hashInterval(i, i + rlen - 1) == h2.hashInterval(j, j + rlen - 1);
            if (good) rp = rlen;
        }
        int lp = 0;
        repp(llen, 1, l * 2 + 1)
        {
            int i = starta;
            int j = startb - llen;
            if (j < 0 || i + llen - 1 >= sz(a)) break;
            bool good = h1.hashInterval(i, i + llen - 1) == h2.hashInterval(j, j + llen - 1);
            if (good) lp = llen;
        }

        if (rp + lp > ret)
        {
            r = { starta - rp,startb - lp };
            if (rev) r.second = sz(b) - r.second - rp - lp;
            ret = rp + lp;
            l = max(l, ret);
        }
    }


    return { ret, r };
}

signed main()
{
    fast();

    string a, b;
    cin >> a >> b;
    pair<int, p2> ans = { -1000,p2(0,0) };
    ans = max(ans, best(a, b, 0));
    reverse(all(b));
    ans = max(ans, best(a, b, 1));
    cout << ans.first << "\n" << ans.second.first << " " << ans.second.second;

    return 0;
}
