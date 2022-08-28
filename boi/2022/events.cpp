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
#define leading_zeros(x) _lzcnt_u32(x)
#define bswap64(x) _byteswap_uint64(x)
#define assert(x) debassert(x)
#else
#define popcount(x) __builtin__popcount(x)
#define leading_zeros(x) __builtin_clz(x)
#define bswap64(x) __builtin_bswap64(x)
#define gc() getchar_unlocked()
#if 0
#include <bits/extc++.h>
using namespace __gnu_pbds;
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return x; }
};
//typedef __gnu_pbds::gp_hash_table<int, null_type, chash> h;
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
template <typename T> inline void write(T& a) { cout << (a) << "\n"; }
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

template<typename T, typename U> inline T first(U a) { return *begin(a); }
template <typename T, typename U> inline void operator+=(pair<T, U>& l, const pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator+(const pair<T, U> l, const pair<T, U> r) { return { l.first + r.first, l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator-(const pair<T, U> l, const pair<T, U> r) { return { l.first - r.first, l.second - r.second }; }
template <typename T, typename U> inline pair<T, U> operator*(const pair<T, U> l, const int m) { return { l.first * m, l.second * m }; }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }

#if 1
auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;
random_device rd;
mt19937 rng(rd());
#endif
const int mod = 1e9 + 7;

struct Segtree
{
    int n;
    vp2 tree;

    Segtree(int n) : n(n), tree(5 * n, p2(inf,inf)) {}

    p2 merge(p2 a, p2 b)
    {
        if (a.first < b.first) return a;
        if (b.first < a.first) return b;
        else return a;
    }

    void update(int x, int l, int r, int pos, p2 v)
    {
        if (r == l) tree[x] = merge(tree[x],v);
        else
        {
            int mid = (l + r) / 2;
            if (pos <= mid) update(x * 2, l, mid, pos, v);
            else update(x * 2 + 1, mid + 1, r, pos, v);
            tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
        }
    }

    void update(int pos, p2 v) { update(1, 0, n - 1, pos, v); }

    p2 query(int x, int l, int r, int ql, int qr)
    {
        if (r<ql || l>qr) return p2(inf,inf);
        if (l >= ql && r <= qr) return tree[x];
        int mid = (l + r) / 2;
        return merge(query(x * 2, l, mid, ql, qr),
            query(x * 2 + 1, mid + 1, r, ql, qr));
    }

    p2 query(int ql, int qr) { return query(1, 0, n - 1, ql, qr); }
};

const int maxn = 1e5;
const int lg = 17;
int up[maxn][lg];


int32_t main()
{
	fast();

#if 0
	//ifstream cin("C:\\Users\\Christian\\in.txt");
#endif

    dread2(int, n, q);

    rep(i, n) rep(j, lg) up[i][lg] = -1;

    vp2 events;
    vi endpoints;
    rep(i, n)
    {
        dread2(int, s, e);
        events.emplace_back(s, e);
        endpoints.emplace_back(e);
    }
    sort(all(endpoints));
    endpoints.erase(unique(all(endpoints)), endpoints.end());

    Segtree tree(n);
    rep(i, events.size())
    {
        p2 ev = events[i];
        int index = lower_bound(all(endpoints), ev.second) - begin(endpoints);
        tree.update(index, mp(ev.first, i));
    }

    vi left(n);
    rep(i, events.size())
    {
        p2 ev = events[i];
        int endpoint = lower_bound(all(endpoints), ev.second) - begin(endpoints);
        int start = lower_bound(all(endpoints), ev.first) - begin(endpoints);
        up[i][0] = tree.query(start, endpoint).second;
    }
    repp(d, 1, lg)
    {
        rep(i, n)
        {
            up[i][d] = up[up[i][d - 1]][d - 1];
        }
    }

    while (q--)
    {
        dread2(int, s, e);
        s--; e--;

        if (e==s)
        {
            cout << "0";
        }
        else if (events[s].second>events[e].second)
        {
            cout << "impossible";
        }
        else if (events[s].second<=events[e].second&&events[s].second>=events[e].first)
        {
            cout << "1";
        }
        else
        {
            int v = e;


            int ans = 2;
            per(i, lg)
            {
                if (up[v][i] != -1 && events[up[v][i]].first>events[s].second)
                {
                    ans += 1 << i; v = up[v][i];
                }
            }

            if (up[v][0] != -1 && events[up[v][0]].first<=events[s].second)
            {
                cout << ans;
            }
            else
            {
                cout << "impossible";

            }

        }
        write("");
    }

	quit;
}