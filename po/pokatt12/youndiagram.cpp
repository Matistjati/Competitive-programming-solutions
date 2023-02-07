#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#define enablell 1

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

#define PBDS 1
#define _LOCAL _MSC_VER > 0
#if _LOCAL
#define gc() getchar()
#define popcount(x) __popcnt(x)
#define leading_zeros(x) _lzcnt_u32(x)
uint32_t clz(uint32_t x) { return _lzcnt_u32(x); }
uint32_t ctz(uint32_t x) { return _tzcnt_u32(x); }
#define bswap64(x) _byteswap_uint64(x)
#define assert(x) debassert(x)
#else
#define popcount(x) __builtin_popcount(x)
uint32_t clz(uint32_t x) { return __builtin_clz(x); }
uint32_t ctz(uint32_t x) { return __builtin_ctzll(x); }
#define bswap64(x) __builtin_bswap64(x)
#define gc() getchar_unlocked()
#if PBDS
using namespace __gnu_pbds;
// lower_bound is now upper_bound and vice versa (multiset). generally a bit broken
template<typename T> using indexed_multiset = tree<int, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};

template<typename T, typename U> using fast_map = __gnu_pbds::gp_hash_table<T, U, chash>;
template<typename T> using fast_set = __gnu_pbds::gp_hash_table<T, null_type, chash>;
template<typename T, typename H> using fast_set_h = __gnu_pbds::gp_hash_table<T, null_type, H>;
#endif

#endif

#define FAST_INPUT 0
#define FILE_TC 0
#if FILE_TC && _LOCAL
//ifstream filein("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
ifstream filein("E:\\downloads\\test_data\\test_data\\005-case05.in");
//ifstream filein("E:\\desktop\\po-repos\\swedish-olympiad-2023\\online\\tomtplanering\\data\\secret\\group10\\010-case10.in");

#define cin filein
//ifstream cin("C:\\Users\\Matis\\desktop\\po-two\\swedish-olympiad-2014\\");
void fast() {}
#else
inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
#endif

#if FAST_INPUT && !FILE_TC
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } v *= sign; }
inline void read(int& u, int& v) { read(u); read(v); }
inline void read(int& u, int& v, int& k) { read(u); read(v); read(k); }
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
#define setcontains(set, x) (set.find(x) != set.end())
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)

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
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T> inline T randint(T lo, T hi) { return uniform_int_distribution<T>(lo, hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<T>((int)0, v.size() - 1)(rng)]; } // [lo,hi]
#endif
const ll mod = 1e9 + 7;

string precompstr = R"V0G0N(
-1

1
1 
2
1 1 
4
2 1 
6
2 1 1 
9
3 1 1 
13
3 2 1 
18
3 2 1 1 
25
4 2 1 1 
32
4 2 1 1 1 
41
4 2 2 1 1 
55
4 3 2 1 1 
74
5 3 2 1 1 
93
5 3 2 1 1 1 
117
6 3 2 1 1 1 
144
6 3 2 2 1 1 
180
6 4 2 2 1 1 
229
6 4 3 2 1 1 
285
6 4 3 2 1 1 1 
355
7 4 3 2 1 1 1 
427
7 4 3 2 2 1 1 
521
7 4 3 2 2 1 1 1 
632
7 5 3 2 2 1 1 1 
773
8 5 3 2 2 1 1 1 
914
8 5 3 2 2 1 1 1 1 
1124
8 5 4 3 2 1 1 1 
1340
8 5 4 3 2 1 1 1 1 
1620
8 5 4 3 2 2 1 1 1 
1934
9 5 4 3 2 2 1 1 1 
2350
9 6 4 3 2 2 1 1 1 
2768
9 6 4 3 2 2 1 1 1 1 
3261
10 6 4 3 2 2 1 1 1 1 
3754
10 6 4 3 2 2 1 1 1 1 1 
4413
10 6 4 3 3 2 2 1 1 1 
5230
9 6 5 4 3 2 2 1 1 1 
6223
10 6 5 4 3 2 2 1 1 1 
7479
10 7 5 4 3 2 2 1 1 1 
8786
10 7 5 4 3 2 2 1 1 1 1 
10323
11 7 5 4 3 2 2 1 1 1 1 
11860
11 7 5 4 3 2 2 1 1 1 1 1 
13710
11 7 5 4 3 2 2 2 1 1 1 1 
15924
11 7 5 4 3 3 2 2 1 1 1 1 
18313
12 7 5 4 3 3 2 2 1 1 1 1 
21313
11 8 6 4 3 3 2 2 1 1 1 1 
24897
12 8 6 4 3 3 2 2 1 1 1 1 
28812
11 8 6 5 4 3 2 2 1 1 1 1 
33785
12 8 6 5 4 3 2 2 1 1 1 1 
38758
12 8 6 5 4 3 2 2 1 1 1 1 1 
44593
12 8 6 5 4 3 2 2 2 1 1 1 1 
51253
12 8 6 5 4 3 3 2 2 1 1 1 1 
58926
13 9 6 5 4 3 2 2 2 1 1 1 1 
67854
13 9 6 5 4 3 3 2 2 1 1 1 1 
78402
13 9 7 5 4 3 3 2 2 1 1 1 1 
89549
13 9 7 5 4 3 3 2 2 1 1 1 1 1 
102286
14 9 7 5 4 3 3 2 2 1 1 1 1 1 
115946
14 9 7 5 4 3 3 2 2 2 1 1 1 1 
131481
14 10 7 5 4 3 3 2 2 2 1 1 1 1 
149040
14 10 7 5 4 3 3 2 2 2 1 1 1 1 1 
170652
14 9 7 6 5 4 3 2 2 2 1 1 1 1 
195787
14 10 7 6 5 4 3 2 2 2 1 1 1 1 
223705
14 10 7 6 5 4 3 3 2 2 1 1 1 1 
256159
14 10 8 6 5 4 3 3 2 2 1 1 1 1 
292241
14 10 8 6 5 4 3 3 2 2 1 1 1 1 1 
333419
15 10 8 6 5 4 3 3 2 2 1 1 1 1 1 
376734
15 10 8 6 5 4 3 3 2 2 2 1 1 1 1 
426575
15 10 8 6 5 4 3 3 2 2 2 1 1 1 1 1 
482175
15 11 8 6 5 4 3 3 2 2 2 1 1 1 1 1 
546031
16 11 8 6 5 4 3 3 2 2 2 1 1 1 1 1 
609887
16 11 8 6 5 4 3 3 2 2 2 1 1 1 1 1 1 
681223
17 11 8 6 5 4 3 3 2 2 2 1 1 1 1 1 1 
763217
16 11 8 6 5 4 4 3 3 2 2 1 1 1 1 1 1 
861527
16 11 8 6 5 4 4 3 3 2 2 2 1 1 1 1 1 
979169
15 11 9 7 6 5 4 3 3 2 2 1 1 1 1 1 
1116124
16 11 9 7 6 5 4 3 3 2 2 1 1 1 1 1 
1258089
16 11 9 7 6 5 4 3 3 2 2 2 1 1 1 1 
1423437
16 11 9 7 6 5 4 3 3 2 2 2 1 1 1 1 1 
1604967
16 12 9 7 6 5 4 3 3 2 2 2 1 1 1 1 1 
1816080
17 12 9 7 6 5 4 3 3 2 2 2 1 1 1 1 1 
2027193
17 12 9 7 6 5 4 3 3 2 2 2 1 1 1 1 1 1 
2262881
18 12 9 7 6 5 4 3 3 2 2 2 1 1 1 1 1 1 
2506145
18 12 9 7 6 5 4 3 3 2 2 2 2 1 1 1 1 1 
2820234
17 12 9 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 
3149134
18 12 9 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 
3507733
18 12 9 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 1 
3918068
18 12 10 8 6 5 4 4 3 3 2 2 2 1 1 1 1 1 
4418444
18 13 10 8 6 5 4 4 3 3 2 2 2 1 1 1 1 1 
4923068
18 13 10 8 6 5 4 4 3 3 2 2 2 1 1 1 1 1 1 
5485391
19 13 10 8 6 5 4 4 3 3 2 2 2 1 1 1 1 1 1 
6171169
18 13 10 8 7 6 5 4 3 3 2 2 2 1 1 1 1 1 
6885083
18 13 10 8 7 6 5 4 3 3 2 2 2 1 1 1 1 1 1 
7681683
19 13 10 8 7 6 5 4 3 3 2 2 2 1 1 1 1 1 1 
8495787
19 13 10 8 7 6 5 4 3 3 2 2 2 2 1 1 1 1 1 
9474004
18 13 10 8 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 
10572785
19 13 10 8 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 
11771283
19 13 10 8 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 1 
13028133
19 14 10 8 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 1 
14634309
19 14 11 9 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 
16296994
19 14 11 9 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 1 
18148771
20 14 11 9 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 1 
20000548
20 14 11 9 7 6 5 4 4 3 3 2 2 2 1 1 1 1 1 1 1 
22121100
20 14 11 9 7 6 5 4 4 3 3 2 2 2 2 1 1 1 1 1 1 
24378871
21 14 11 9 7 6 5 4 4 3 3 2 2 2 2 1 1 1 1 1 1 
)V0G0N";
int32_t main()
{
    dread(int, s);
    stringstream precomp(precompstr);
    string _;
    getline(precomp, _);
    rep(i, 101)
    {
        string cnt;
        getline(precomp, cnt);

        string placement;
        getline(precomp, placement);
        if (i == s)
        {
            cout << cnt << "\n";
            cout << placement;
            break;
        }
    }

    quit;
}
