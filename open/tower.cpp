#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
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
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<T>((int)0, v.size() - 1)(rng)]; } // [lo,hi]
#endif
const int mod = 1e9 + 7;

#define UNVISITED 0
#define VISITING 1
#define LEFT 2

void dfs(int u, vb& vis, vi& ret, vvi& edges)
{
    if (vis[u]) return;
    vis[u] = 1;

    ret.push_back(u);
    repe(e, edges[u]) dfs(e, vis, ret, edges);
}

bool findcycle(int u, vi& col, vi& ret, vector<unordered_multiset<int>>& edges)
{
    if (col[u] == LEFT) return false;
    if (col[u] == VISITING)
    {
        ret.push_back(u);
        return true;
    }
    col[u] = VISITING;

    while (edges[u].size())
    {
        auto it = edges[u].begin();
        int e = *it;
        edges[u].erase(it);
        edges[e].erase(edges[e].find(u));
        if (findcycle(e, col, ret, edges))
        {
            if (u == ret.front())
            {
                ret.push_back(-1);
                return true;
            }
            else if (ret.back() == -1)
            {
                return true;
            }
            else
            {
                ret.push_back(u);
            }

            return true;
        }
    }

    col[u] == LEFT;
    return false;
}


void find_largest(int u, int& maxv, int& maxu, vi& col, vi& value, vvi& edges)
{
    if (col[u]) return;
    col[u] = 1;

    if (value[u] > maxv)
    {
        maxv = value[u];
        maxu = u;
    }

    repe(e, edges[u]) find_largest(e, maxv, maxu, col, value, edges);
}

int ans_cycle(int u, vi& value, vector<unordered_multiset<int>>& edges)
{
    int ret = 0;

    while (edges[u].size())
    {
        auto it = edges[u].begin();
        int e = *it;
        edges[u].erase(it);
        edges[e].erase(edges[e].find(u));
        ret += value[u];
        ret += ans_cycle(e, value, edges);
    }

    return ret;
}


int32_t main()
{
    fast();

    dread(int, n);
    unordered_map<int, int> sideIndex;
    vi values;

    vector<unordered_multiset<int>> sedges;
    vector<unordered_multiset<int>> sedges2;
    vvi edges;
    int nodeI = 0;
    rep(i, n)
    {
        dread2(int, a, b);
        if (!setcontains(sideIndex, a))
        {
            sideIndex[a] = nodeI++;
            edges.push_back({});
            sedges.push_back({});
            sedges2.push_back({});
            values.push_back(a);
        }
        a = sideIndex[a];
        if (!setcontains(sideIndex, b))
        {
            sideIndex[b] = nodeI++;
            edges.push_back({});
            sedges.push_back({});
            sedges2.push_back({});
            values.push_back(b);
        }
        b = sideIndex[b];

        edges[a].push_back(b);
        sedges[a].insert(b);
        sedges2[a].insert(b);
        edges[b].push_back(a);
        sedges[b].insert(a);
        sedges2[b].insert(a);
    }

    n = nodeI;
    int ans = 0;
    vb vis(n);
    vi col(n);
    rep(i, n)
    {
        if (vis[i]) continue;
        vi comp;
        dfs(i, vis, comp, edges);

        int edgeCount = 0;
        repe(v, comp) edgeCount += edges[v].size();
        assert(edgeCount % 2 == 0);
        edgeCount /= 2;

        if (edgeCount == comp.size())
        {
            vi cycle;
            findcycle(i, col, cycle, sedges2);

            if (cycle.back() == -1) cycle.pop_back();
            assert(cycle.size());
            ans += ans_cycle(cycle.back(), values, sedges);
        }
        else
        {
            int maxv = -1;
            int largest = -1;
            find_largest(i, maxv, largest, col, values, edges);
            assert(largest != -1);
            ans += ans_cycle(largest, values, sedges);
        }
    }

    cout << ans;

    quit;
}