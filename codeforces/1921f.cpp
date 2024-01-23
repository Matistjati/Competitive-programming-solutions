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
#define clz(x) _lzcnt_u32(x)
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

int cutoff = 200;
void solve()
{
    vector<vi> precompprogression(1);
    vector<vi> precomp(1);
    int n, q;
    cin >> n >> q;


    vi nums(n);
    rep(i, n) cin >> nums[i];

    repp(i, 1, cutoff)
    {
        vi prefixsums(n);
        vi prefixsums2(n);

        rep(j, n)
        {
            if (j < i) prefixsums[j] = nums[j];
            else prefixsums[j] = (prefixsums[j - i] + nums[j]);

            if (j < i) prefixsums2[j] = nums[j];
            else prefixsums2[j] = (prefixsums2[j - i] + nums[j] * (j / i + 1));

        }
        precomp.push_back(prefixsums);
        precompprogression.push_back(prefixsums2);
    }
    //cout << elapsedmillis() << "ms\n";
    auto rsq = [](vvi& precomp, int s, int d, int k)
    {
        vi& pref = precomp[d];
        int l = s;
        int r = s + (k - 1) * d;
        if (l - d >= 0) l = pref[l - d];
        else l = 0;
        return pref[r] - l;
    };

    while (q--)
    {
        int s, d, k;
        cin >> s >> d >> k;
        s--;
        int ans = 0;
        if (d < precomp.size())
        {
            int l = (s / d);
            int a = rsq(precompprogression, s, d, k);
            int b = rsq(precomp, s, d, k);
            cout << a - b * l << " ";
        }
        else
        {
            rep(i, k)
            {
                ans += nums[s + d * i] * (i + 1);
            }
            cout << ans << " ";
        }
    }
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