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

vi city;
vvi edges;
vi par;
vi depth;
vi timein;
vi timeout;
vi cost;
vi citylazy;
vi personlazy;
int up[200010][19];

void roottree(int u, int p, int d, int& time)
{
    timein[u] = time++;
    par[u] = p;
    up[u][0] = p;

    repp(d, 1, 19)
        up[u][d] = up[up[u][d - 1]][d - 1];

    depth[u] = d;
    repe(e, edges[u]) if (e != p) roottree(e, u, d + 1, time);
    timeout[u] = time++;
}

bool isancestor(int a, int b)
{
    return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

int lca(int a, int b)
{
    if (isancestor(a, b)) return a;
    if (isancestor(b, a)) return b;

    for (int i = 18; i >= 0; i--)
    {
        if (!isancestor(up[a][i], b))
        {
            a = up[a][i];
        }
    }

    return up[a][0];
}

int dist(int a, int b)
{
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

struct Tree
{
    vi color;
    vi lazycolor;
    vb islazy;
    vi lazy;
    int n;

    Tree(int n) : color(n * 4 + 10, 0), lazy(n * 4 + 10, 0), n(n), lazycolor(n * 4 + 10, -10), islazy(n * 4 + 10) {}

    void paint(int x, int l, int r, int ql, int qr, int col)
    {
        if (r < ql || l > qr) return;
        if (l >= ql && r <= qr)
        {

            color[x] = col;
            lazycolor[x] = col;
            islazy[x] = 1;
            return;
        }

        int mid = (l + r) / 2;
        paint(x * 2, l, mid, ql, qr, col);
        paint(x * 2 + 1, mid + 1, r, ql, qr, col);

        color[x] = (color[x * 2] == color[x * 2 + 1] ? color[x * 2] : -1);
    }


    void add(int x, int l, int r, int ql, int qr, int v)
    {
        if (r < ql || l > qr) return;
        if (color[x] != -1 && l >= ql && r <= qr)
        {
            lazy[x] -= dist(v, color[x]);
            lazy[x] += citylazy[color[x]];
            lazy[x] -= citylazy[v];
            return;
        }
        if (islazy[x])
        {
            color[x * 2] = color[x * 2 + 1] = lazycolor[x];
            lazycolor[x * 2] = lazycolor[x * 2 + 1] = lazycolor[x];
            islazy[x * 2] = islazy[x * 2 + 1] = 1;
            islazy[x] = 0;
            lazycolor[x] = -10;
        }

        int mid = (l + r) / 2;
        add(x * 2, l, mid, ql, qr, v);
        add(x * 2 + 1, mid + 1, r, ql, qr, v);
    }


    int query(int x, int l, int r, int i)
    {
        if (i < l || i > r) return 0;
        if (l == r) return lazy[x];

        int mid = (l + r) / 2;
        if (i <= mid) return lazy[x] + query(x * 2, l, mid, i);
        else return lazy[x] + query(x * 2 + 1, mid + 1, r, i);
    }

    int querycolor(int x, int l, int r, int i)
    {
        if (i < l || i > r) deb;
        if (l == r) return color[x];

        if (islazy[x])
        {
            color[x * 2] = color[x * 2 + 1] = lazycolor[x];
            lazycolor[x * 2] = lazycolor[x * 2 + 1] = lazycolor[x];
            islazy[x * 2] = islazy[x * 2 + 1] = 1;
            islazy[x] = 0;
            lazycolor[x] = -10;
        }

        int mid = (l + r) / 2;
        if (i <= mid) return querycolor(x * 2, l, mid, i);
        else return querycolor(x * 2 + 1, mid + 1, r, i);
    }

};


string solvesmart(int n, int m, int q, vi& cityin, vp2& ein, vvi& queries)
{
    city.resize(m);
    edges.resize(n);
    par.resize(n);
    depth.resize(n);
    timein.resize(n);
    timeout.resize(n);
    cost.resize(m);

    rep(i, 200010) rep(j, 19) up[i][j] = -1;
    rep(i, m)
    {
        city[i] = cityin[i];
        city[i]--;
    }

    rep(i, n - 1)
    {
        int a = ein[i].first;
        int b = ein[i].second;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    int time = 0;
    roottree(0, 0, 0, time);

    Tree tree(m);
    rep(i, m) tree.paint(1, 0, m - 1, i, i, city[i]);
    citylazy.resize(0);
    citylazy.resize(n);

    stringstream ret;
    rep(_, q)
    {
        int t = queries[_][0];
        if (t == 0)
        {
            int l = queries[_][1];
            int r = queries[_][2];
            int c = queries[_][3];
            l--; r--; c--;

            tree.add(1, 0, m - 1, l, r, c);
            tree.paint(1, 0, m - 1, l, r, c);
        }
        if (t == 1)
        {
            int c = queries[_][1];
            c--;
            int d = queries[_][2];
            citylazy[c] += d;
        }
        if (t == 2)
        {
            int v = queries[_][1];
            v--;
            ret << tree.query(1, 0, m - 1, v) + citylazy[tree.querycolor(1, 0, m - 1, v)] << "\n";
        }
    }
    return ret.str();
}


struct UF
{
    vi par;
    UF(int n) : par(n) { rep(i, n)par[i] = i; }

    int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }

    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;

        par[a] = b;
    }
};

int32_t main()
{
    fast();


    dread3(int, n, m, q);
    readvector(int, cit, m);
    vp2 e(n - 1);
    rep(i, n - 1) read(e[i].first), read(e[i].second);
    vvi queries(q);
    rep(i, q)
    {
        dread(char, t);
        if (t == 't')
        {
            dread3(int, l, r, c);
            queries[i] = { 0, l, r, c };
        }
        else if (t == 'e')
        {
            dread2(int, c, d);
            queries[i] = { 1,c,d };
        }
        else if (t == 'q')
        {
            dread(int, v);
            queries[i] = { 2, v };
        }
    }
    cout << solvesmart(n, m, q, cit, e, queries);

    quit;
}
