#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>

using namespace std;

#define enablell 0

typedef long long ll;
#if enablell
#define int ll
#define inf LLONG_MAX
#define float double
#else
#define inf int(2e9)
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define p2 pair<int, int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vvvp2 vector<vvp2>
#define p3 tuple<int,int,int>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define p4 tuple<int,int,int,int>
#define vp4 vector<p4>

//#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define read3(a,b,c) cin >> a >> b >> c
//#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#define debassert(expr) if (!(expr)) deb;
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debassert(expr) ;
#define debif(expr) ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))
#define indexpair(p, i) ((i==0)?p.first:p.second)
#define chmax(a,b) ((a)=max((a),b))
#define chmin(a,b) ((a)=min((a),b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
inline int readintsigned() { int v = 0; int sign = 1; char c = getchar(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v * sign; }
inline int readint() { int v = 0; char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v; }
inline string readstring() { string s; char c; while ((c = getchar()) != EOF && c != '\n') { s.push_back(c); } return s; }
#if _MSC_VER > 0
#define gc() getchar()
#else
#if 0
#include <bits/extc++.h>
using namespace __gnu_pbds;
#endif
#define gc() getchar_unlocked()
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return x; }
};
//typedef __gnu_pbds::gp_hash_table<int, null_type, chash> h;

#endif



int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\joshua.jeffmarander\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread3(int, n, m, k);

    readvector(int, dishes, n);
    readvector(int, chefs, m);

    int s = 0;
    rep(i, n) s += dishes[i];

    rep(i, n)
    {
        if (dishes[i] < k)
        {
            cout << "Impossible";
            quit;
        }
    }

    vi dp(90010, -inf);
    dp[0] = 0;

    vi next(dp);

    rep(i, chefs.size())
    {
        int uniques = min(n, chefs[i]);
        int working = chefs[i];


        repp(j, working, dp.size())
        {
            next[j] = max(dp[j], dp[j - working] + uniques);
        }
        dp = next;
    }

    int ans = inf;

    rep(i, dp.size())
    {
        if (dp[i] >= n * k)
        {
            if (i >= s)
            {
                ans = min(ans, i - s);
            }
        }
    }

    if (ans != inf) cout << ans;
    else cout << "Impossible";

    quit;
}