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
#else
const int inf = int(2e9);
#endif
typedef vector<ull> vull;
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

#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
uint32_t clz(uint32_t x) { return _lzcnt_u32(x); }
uint32_t ctz(uint32_t x) { return _tzcnt_u32(x); }
#define bswap64(x) _byteswap_uint64(x)
#else

#define popcount(x) __builtin_popcountll(x)
uint32_t clz(uint32_t x) { return __builtin_clz(x); }
uint32_t ctz(uint32_t x) { return __builtin_ctzll(x); }
#define bswap64(x) __builtin_bswap64(x)

#if 0
namespace pbds
{
    using namespace __gnu_pbds;

    template<typename T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
    template<typename T, typename U> using indexed_map = tree<T, U, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

    struct chash { // large odd number for C
        const uint64_t C = ll(4e18 * acos(0)) | 71;
        ll operator()(ll x) const { return __builtin_bswap64(x * C); }
    };
    template<typename T, typename U> using fast_map = __gnu_pbds::gp_hash_table<T, U, chash>;
    template<typename T> using fast_set = __gnu_pbds::gp_hash_table<T, null_type, chash>;
    template<typename T, typename H> using fast_set_h = __gnu_pbds::gp_hash_table<T, null_type, H>;
}
using namespace pbds;
#endif
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
#define FAST_INPUT 0
#if FAST_INPUT && !_LOCAL
#define gc() getchar_unlocked()
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) && c != ' ' && c != '\n') { if (c == EOF) { v = -1; return; } v *= 10; v += c - '0'; } v *= sign; }
inline void read(int& u, int& v) { read(u); read(v); }
inline void read(int& u, int& v, int& k) { read(u); read(v); read(k); }
//inline void read(int& v) { char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } }
inline void read(string& s) { char c; while ((c = gc()) != EOF && c != '\n' && c != ' ') { s.push_back(c); } }
inline void readline(string& s) { char c; while ((c = gc()) != EOF && c != '\n') { s.push_back(c); } }
#else
template <typename T> inline void read(T& a) { cin >> a; }
template <typename T> inline void read(T& a, T& b) { cin >> a >> b; }
template <typename T> inline void read(T& a, T& b, T& c) { cin >> a >> b >> c; }
#endif
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
#define debassert(expr) if(!(expr)) deb;
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debif(expr) ;
#define debassert(expr) ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)

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
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]
#endif
const ll mod = 1e9 + 7;
vp2 dirs = { {0,1},{0,-1},{1,0},{-1,0} };

vi dancetype;
const int hi = int(3e5 + 10);
inline p4 merge(const p4& a, const p4& b)
{
    p4 res = p4(-inf, -inf, -inf, -inf);
    if (get<0>(a) > get<0>(res)) get<0>(res) = get<0>(a), get<1>(res) = get<1>(a);
    if (get<2>(a) > get<0>(res)) get<0>(res) = get<2>(a), get<1>(res) = get<3>(a);
    if (get<0>(b) > get<0>(res)) get<0>(res) = get<0>(b), get<1>(res) = get<1>(b);
    if (get<2>(b) > get<0>(res)) get<0>(res) = get<2>(b), get<1>(res) = get<3>(b);

    if (get<1>(res) == -inf) return res;

    if (get<0>(a) > get<2>(res) && get<1>(a) != -inf && dancetype[get<1>(res)] != dancetype[get<1>(a)]) get<2>(res) = get<0>(a), get<3>(res) = get<1>(a);
    if (get<2>(a) > get<2>(res) && get<3>(a) != -inf && dancetype[get<1>(res)] != dancetype[get<3>(a)]) get<2>(res) = get<2>(a), get<3>(res) = get<3>(a);
    if (get<0>(b) > get<2>(res) && get<1>(b) != -inf && dancetype[get<1>(res)] != dancetype[get<1>(b)]) get<2>(res) = get<0>(b), get<3>(res) = get<1>(b);
    if (get<2>(b) > get<2>(res) && get<3>(b) != -inf && dancetype[get<1>(res)] != dancetype[get<3>(b)]) get<2>(res) = get<2>(b), get<3>(res) = get<3>(b);

    return res;
}


struct Tree
{
    vector<p4> tree;
    Tree(int n) : tree(n * 4, p4(-inf, -inf, -inf, -inf)) {}
    void update(int x, int l, int r, int i, p4 v)
    {
        if (l == r) tree[x] = merge(tree[x], v);
        else
        {
            int mid = (l + r) / 2;
            if (i <= mid) update(x * 2, l, mid, i, v);
            else update(x * 2 + 1, mid + 1, r, i, v);
            tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
        }
    }

    p4 query(int x, int l, int r, int ql, int qr)
    {
        if (l > qr || r < ql) return p4(-inf, -inf, -inf, -inf);
        if (l >= ql && r <= qr) return tree[x];
        int mid = (l + r) / 2;
        return merge(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
    }
};

int32_t main()
{
    fast();
#if 0 && _LOCAL
    ifstream instream("C:\\users\\matis\\source\\repos\\comp_prog\\x64\\debug\\in.txt");
    cin.rdbuf(instream.rdbuf());
#endif

    dread2(int, n, m);

    vp2 dances;
    map<int, int> seen;
    vi vals;
    rep(i, n)
    {
        dread2(int, t, f);
        vals.push_back(f);
        dances.emplace_back(t, f);
        dancetype.push_back(t);
    }
    sort(all(vals));
    repe(f, vals) if (!setcontains(seen, f)) seen[f] = seen.size();
    Tree tree(seen.size());

    vp2 par(n);
    rep(i, dances.size())
    {
        int t, f;
        tie(t, f) = dances[i];
        f = seen[f];
        p4 best = p4(-inf, -inf, -inf, -inf);
        best = merge(best, tree.query(1, 0, seen.size() - 1, 0, f - 1));
        best = merge(best, tree.query(1, 0, seen.size() - 1, 0, f - 1));
        p2 res = p2(-inf, -inf);

        if (get<0>(best) == -inf)
        {
            res = p2(0, -2);
        }
        else
        {
            if (dancetype[get<1>(best)] != t)
            {
                res = p2(get<0>(best), get<1>(best));
            }
            else if (get<2>(best) == -inf)
            {
                res = p2(0, -2);
            }
            else
            {
                assert(dancetype[get<1>(best)] != dancetype[get<3>(best)]);
                res = p2(get<2>(best), get<3>(best));
            }
        }
        res.first++;
        par[i] = res;
        tree.update(1, 0, seen.size() - 1, f, p4(res.first, i, -inf, -inf));
    }

    p2 best = p2(-inf, -inf);
    int besti = -1;
    rep(i, par.size())
    {
        p2 v = par[i];
        if (v.first > best.first)
        {
            best = v;
            besti = i;
        }
    }

    vi ans;
    while (1)
    {
        ans.push_back(besti);
        if (best.second == -2) break;
        besti = best.second;
        best = par[best.second];
    }

    cout << ans.size() << "\n";
    reverse(all(ans));
    repe(v, ans)
    {
        cout << v + 1 << " ";
    }

    quit;
}
