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
typedef unsigned long long ull;
#if enablell
#define int ll
#define inf int(1e18)
#define float double
#else
const int inf = int(2e9);
#endif
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef pair<int, int> p2;
typedef vector<p2> vp2;
typedef vector<vp2> vvp2;
typedef vector<vvp2> vvvp2;
typedef tuple<int, int, int> p3;
typedef vector<p3> vp3;
typedef vector<vp3> vvp3;
typedef vector<vvp3> vvvp3;
typedef tuple<int, int, int, int> p4;
typedef vector<p4> vp4;

#define _LOCAL _MSC_VER > 0
#if _LOCAL
#define gc() getchar()
#define popcount(x) __popcnt(x)
#define leading_zeros(x) _lzcnt_u64(x)
#define ctz(x) _tzcnt_u64(x)
#define bswap64(x) _byteswap_uint64(x)
#define assert(x) debassert(x)
#else
#define popcount(x) __builtin_popcount(x)
#define leading_zeros(x) __builtin_clz(x)
#define ctz(x) __builtin_ctzll(x)
#define bswap64(x) __builtin_bswap64(x)
#define gc() getchar_unlocked()
#if 0
#include <bits/extc++.h>
using namespace __gnu_pbds;
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};
typedef __gnu_pbds::gp_hash_table<ll, ll, chash> fast_map;
#endif

#endif

#define CIN_IN 1
#define FILE_TC 0
#if FILE_TC
ifstream filein("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#define cin filein
//ifstream cin("C:\\Users\\Matis\\desktop\\po-two\\swedish-olympiad-2014\\");
void fast() {}
#else
inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
#endif

#if !FILE_TC && !CIN_IN
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } v *= sign; }
inline void read(int& u, int& v) { read(u); read(v); }
//inline void read(int& v) { char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } }
inline void read(string& s) { char c; while ((c = gc()) != EOF && c != '\n' && c != ' ') { s.push_back(c); } }
#else
template <typename T> inline void read(T& a) { cin >> a; }
template <typename T> inline void read(T& a, T& b) { cin >> a >> b; }
template <typename T> inline void read(T& a, T& b, T& c) { cin >> a >> b >> c; }
#endif
template <typename T> inline void write(T a) { cout << (a) << "\n"; }
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; read(a)
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
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

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define revall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define indexpair(p, i) ((i==0)?p.first:p.second)
#define chmax(a,b) ((a)=max((a),b))
#define chmin(a,b) ((a)=min((a),b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

template<typename T> inline void eraseOne(multiset<T>& mSet, T k) { auto itr = mSet.find(k); if (itr != mSet.end()) { mSet.erase(itr); } }
template<typename T, typename U> inline T first(U& a) { return *begin(a); }
template <typename T, typename U> inline void operator+=(pair<T, U>& l, const pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator+(const pair<T, U> l, const pair<T, U> r) { return { l.first + r.first, l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator-(const pair<T, U> l, const pair<T, U> r) { return { l.first - r.first, l.second - r.second }; }
template <typename T, typename U> inline pair<T, U> operator*(const pair<T, U> l, const int m) { return { l.first * m, l.second * m }; }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
vector<string> split(string s, string d) { size_t k = 0, n, e = d.length(); string t; vector<string> r; while ((n = s.find(d, k)) != string::npos) { t = s.substr(k, n - k); k = n + e; r.push_back(t); } r.push_back(s.substr(k)); return r; }
ll binpow(ll a, ll b) { ll res = 1; while (b > 0) { if (b & 1) res = res * a; a = a * a; b >>= 1; } return res; }
ll binpow(ll a, ll b, ll m) { a %= m; long long res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } return res; } // For a < 2^31

#if 1
auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;
random_device rd;
mt19937 rng(rd());
template<typename T> inline T randint(T lo, T hi) { return uniform_int_distribution<T>(lo, hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<T>((int)0, v.size()-1)(rng)]; } // [lo,hi]
#endif
const int mod = 1e9 + 7;

const int MAX = (100 * 450 + 10)/2;
typedef bitset<MAX> bset;

int32_t main()
{
    fast();

    dread(int, n);
    vector<bset> dp(n/2+2), newDp(n/2+2);
    dp[0][0] = 1;

    readvector(int, nums, n);
    int s = accumulate(all(nums),0);

    rep(i, n)
    {
        rep(j, dp.size())
        {
            newDp[j] = dp[j];
            if (j != 0) newDp[j] |= (dp[j - 1] << nums[i]);
        }
        dp = newDp;
        rep(i, newDp.size()) newDp[i].reset();
    }


    vi examine;
    if (n % 2 == 0) examine = { n / 2 };
    else examine = { n / 2, n/2+1 };


    int a = inf;
    int b = -inf;

    repe(i, examine)
    {
        rep(j, MAX)
        {
            if (dp[i][j] && abs(j-(s-j))<abs(a-b))
            {
                a = j;
                b = s - j;
            }
        }
    }

    cout << min(a, b) << " " << max(a, b);

    quit;
}