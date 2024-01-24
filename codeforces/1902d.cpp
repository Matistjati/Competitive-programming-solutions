#pragma GCC optimize("Ofast,inline,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

#define _LOCAL _MSC_VER > 0
#if _LOCAL
#define deb __debugbreak();
#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
#define clz(x) _lzcnt_u64(x)
#else
#define clz(x) __builtin_clz(x)
#define deb ;
#define popcount(x) __builtin_popcountll(x)
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#ifdef _DEBUG
#define debassert(expr) if(!(expr)) deb;
#else
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]

const int mod = int(1e9 + 7);

#if !_LOCAL
#include <bits/extc++.h>
namespace pbds
{
    using namespace __gnu_pbds;

    struct chash { // large odd number for C
        const uint64_t C = ll(4e18 * acos(0)) | 71;
        ll operator()(ll x) const { return __builtin_bswap64(x * C); }
    };
    template<typename T, typename U> using fast_map = __gnu_pbds::gp_hash_table<T, U, chash>;
    template<typename T> using fast_set = __gnu_pbds::gp_hash_table<T, null_type, chash>;
}
using namespace pbds;
#else
template<typename T, typename U> using fast_map = unordered_map<T, U>;
template<typename T> using fast_set = unordered_set<T>;

#endif
#define int ll


int geth(p2 x)
{
    return x.first + x.second * int(1e7);
}

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<p2> positions;
    vector<p2> bounds;
    vi ans(q);
    string moves;
    cin >> moves;
    map<char, p2> delta;
    delta['R'] = p2(1, 0);
    delta['L'] = p2(-1, 0);
    delta['U'] = p2(0, 1);
    delta['D'] = p2(0, -1);

    vector<p2> istart(q);
    vvi disable(n);
    rep(i, q)
    {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        l--; r--;
        positions.emplace_back(x, y);
        if (x == 0 && y == 0)ans[i] = 1;
        bounds.emplace_back(l, r);
        disable[l].emplace_back(i);
    }

    fast_map<int, vi> vispos;
    p2 pos = p2(0, 0);
    rep(i, n)
    {
        repe(d, disable[i])
        {
            p2 p = positions[d];
            istart[d] = pos;
        }

        p2 d = delta[moves[i]];
        pos.first += d.first;
        pos.second += d.second;

        vispos[geth(pos)].push_back(i);
    }

    rep(i, q)
    {
        p2 p = positions[i];
        if (vispos.find(geth(p)) != vispos.end())
        {
            vi& v = vispos[geth(p)];
            if (v.empty()) continue;
            if (v[0] < bounds[i].first) ans[i] = 1;
            if (v.back() > bounds[i].second) ans[i] = 1;
        }
    }

    vvi starttime(n);
    rep(i, q)
    {
        starttime[bounds[i].second].push_back(i);
    }


    pos = p2(0, 0);
    fast_map<int, vi> vispos2;
    per(i, n)
    {
        repe(a, starttime[i])
        {
            positions[a].first += -istart[a].first + pos.first;
            positions[a].second += -istart[a].second + pos.second;
        }

        p2 d = delta[moves[i]];
        pos.first += d.first;
        pos.second += d.second;
        vispos2[geth(pos)].push_back(i);
    }

    rep(i, q)
    {
        p2 p = positions[i];
        if (vispos2.find(geth(p)) != vispos2.end())
        {
            vi& v = vispos2[geth(p)];
            if (v.empty()) continue;
            auto it = lower_bound(rall(v), bounds[i].first);
            if (it != v.rend() && *it <= bounds[i].second) ans[i] = 1;
        }
    }

    rep(i, q)
    {
        cout << (ans[i] ? "Yes" : "No") << "\n";
    }
}

signed main()
{
    fast();
#if _LOCAL && 0
    ifstream in("C:\\Users\\matis\\desktop\\comp_prog\\x64\\debug\\in.txt");
    cin.rdbuf(in.rdbuf());
#endif
    int t;
    //cin >> t;
    t = 1;
    while (t--)
    {
        solve();
    }


    return 0;
}