#pragma GCC optimize("Ofast,inline,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")

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
#define per(i, high) for (int i = high-1; i >= 0; i--)

#if _MSC_VER > 0
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

int leading(int n)
{
    int ret = inf;
    rep(i, 63) if (n & (1LL << i)) ret = i;
    return ret;
}

void solve()
{
    int x;
    cin >> x;
    int lz = leading(x);
    int orig = x;
    int gap = 1000;
    vi placed;
    rep(i, lz)
    {
        placed.push_back((i + 1) * gap);
    }
    x -= (1LL << lz);
    vi placed2;

    while (leading(x) != inf)
    {
        int k = leading(x);

        placed2.push_back((k)*gap + 500);
        x -= (1LL << k);
    }

    cout << placed.size() + placed2.size() << "\n";
    repe(v, placed) cout << v << " ";
    repe(v, placed2) cout << v << " ";

    cout << "\n";

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