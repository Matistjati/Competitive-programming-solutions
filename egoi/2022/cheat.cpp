// NOTE: gets 71 points

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

#define PBDS 0
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

vector<pair<p2, p2>> available = {
    {{0,0},{0,1}}, //
    {{0,0},{1,0}}, // 
    {{0,0},{2,1}}, //
    {{0,0},{1,1}}, //
    {{0,0},{1,2}}, //
    {{1,0},{2,0}}, //
    {{1,0},{2,1}}, //
    {{1,0},{0,1}}, //
    {{2,0},{2,1}}, //
    {{2,0},{1,1}}, //
    {{2,0},{0,1}}, //
    {{2,0},{1,2}}, //
    {{2,1},{2,2}}, //
    {{2,1},{1,2}}, //
    {{2,1},{0,2}}, //
    {{2,2},{1,0}}, //
    {{2,2},{1,1}}, //
    {{2,2},{1,2}}, //
    {{1,2},{0,1}}, //
    {{1,2},{0,2}}, //
    {{0,2},{0,1}}, //
    {{0,2},{1,0}}, //
    {{0,1},{2,2}}, //
    {{0,2},{1,1}}, //

};
map<pair<p2, p2>, int> mapping;
map<pair<p2, p2>, int> rot;
map<int, pair<p2, p2>> revmap;

vector<pair<p2, p2>> reserved = {

};
bool inited = false;
map<p2, p2> nextrot = {
    {{0,0},{2,0}},
    {{1,0},{2,1}},
    {{2,0},{2,2}},
    {{2,1},{1,2}},
    {{2,2},{0,2}},
    {{1,2},{0,1}},
    {{0,2},{0,0}},
    {{0,1},{1,0}},
    {{1,1},{1,1}},



};
map<set<set<p2>>, p2> specialvalues;
map<p2, set<set<p2>>> revspecialvalues;

set<p2> toset(pair<p2, p2> v)
{
    return { v.first,v.second };
}

pair<p2, p2> fromset(set<p2> v)
{
    pair<p2, p2> hi;
    auto it = begin(v);
    hi.first = *it;
    hi.second = *next(it);
    return hi;
}

set<set<p2>> special = {
    {{0,1},{1,1}},
    {{1,0},{1,1}},
    {{1,2},{1,1}},
    {{2,1},{1,1}},
};

void init()
{
    pair<p2, p2> s = { {0,1},{1,1} };
    rep(i, 4)
    {
        rot[s] = i * 90;
        swap(s.first, s.second);
        rot[s] = i * 90;
        reserved.push_back(s);
        s = { nextrot[s.first],nextrot[s.second] };
    }

    int maxv = 0;
    int i = 1;
    repe(p, available)
    {
        mapping[p] = i;
        swap(p.first, p.second);
        mapping[p] = i;
        maxv = max(maxv, i);
        i *= 2;
    }

    s = { {0,1},{1,1} };
    rep(i, 4)
    {
        set<set<p2>> davalues;
        pair<p2, p2> c = pair<p2, p2>(s);
        rep(j, 1)
        {
            davalues.insert(toset(c));
            c = { nextrot[c.first],nextrot[c.second] };
        }
        specialvalues[davalues] = { 0, i * 90 };
        revspecialvalues[mp(0, i * 90)] = { davalues };
        s = { nextrot[s.first],nextrot[s.second] };
    }

    s = { {0,1},{1,1} };
    rep(i, 4)
    {
        set<set<p2>> davalues;
        pair<p2, p2> c = pair<p2, p2>(s);
        rep(j, 2)
        {
            davalues.insert(toset(c));
            c = { nextrot[c.first],nextrot[c.second] };
        }
        specialvalues[davalues] = { maxv * 2, i * 90 };
        revspecialvalues[mp(maxv * 2, i * 90)] = { davalues };
        s = { nextrot[s.first],nextrot[s.second] };
    }

    s = { {0,1},{1,1} };
    rep(i, 4)
    {
        set<set<p2>> davalues;
        pair<p2, p2> c = s;
        rep(j, 3)
        {
            davalues.insert(toset(c));
            c = { nextrot[c.first],nextrot[c.second] };
        }
        specialvalues[davalues] = { maxv * 4, i * 90 };
        revspecialvalues[mp(maxv * 4, i * 90)] = { davalues };
        s = { nextrot[s.first],nextrot[s.second] };
    }

    set<set<p2>> key;
    specialvalues[key] = { maxv * 2 + maxv * 4,0 };
    revspecialvalues[{ maxv * 2 + maxv * 4, 0 }] = { key };

    /*key = { {{0,1},{1,1}}, {{2,1},{1,1}} };
    specialvalues[key] = { maxv * 2 + maxv * 4,90 };
    revspecialvalues[{ maxv * 2 + maxv * 4, 90 }] = { key };

    key = { {{1,0},{1,1}}, {{1,1},{1,2}} };
    specialvalues[key] = { maxv * 2 + maxv * 4,180};
    revspecialvalues[{ maxv * 2 + maxv * 4, 180 }] = { key };

    key = { {{1,0},{1,1}}, {{1,1},{1,2}},{{0,1},{1,1}}, {{2,1},{1,1}} };
    specialvalues[key] = { maxv * 2 + maxv * 4,270};
    revspecialvalues[{ maxv * 2 + maxv * 4, 270 }] = { key };*/






    repe(m, mapping)
    {
        revmap[m.second] = m.first;
    }
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> BuildPattern(int n)
{
    if (!inited)
    {
        init();
        inited = true;
    }
    vector<pair<p2, p2>> ret;
    rep(i, 24)
    {
        if (n & (1 << i))
        {
            ret.push_back(revmap[1 << i]);
        }
    }

    int ligmoid = (n & (1 << 24)) | (n & (1 << 25));

    repe(p, revspecialvalues[mp(ligmoid, 0)])
    {
        ret.push_back(fromset(p));
    }

    return ret;
}



void rotate(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& pattern, int degs)
{
    rep(i, degs / 90)
    {
        rep(i, pattern.size())
        {
            pattern[i] = { nextrot[pattern[i].first],nextrot[pattern[i].second] };
        }
    }
}

void unrotate(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& pattern, int degs)
{
    if (degs == 0)
    {

    }
    if (degs == 90)
    {
        rotate(pattern, 270);
    }
    if (degs == 180)
    {
        rotate(pattern, 180);

    }
    if (degs == 270)
    {
        rotate(pattern, 90);

    }
}

int GetCardNumber(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> pattern)
{
    set<pair<p2, p2>> patterns(all(pattern));

    set<set<p2>> sickreckt;
    repe(p, pattern)
    {
        set<p2> asset = toset(p);
        if (setcontains(special, asset))
        {
            sickreckt.insert(asset);
        }
    }

    int ret = specialvalues[sickreckt].first;
    int rotation = specialvalues[sickreckt].second;
    unrotate(pattern, rotation);


    /*cout << "after: ";
    repe(k, pattern)
    {
        cout << "a {" << k.first.first << ", " << k.first.second << "}. b {" << k.second.first << ", " << k.second.second << "}\n";
    }*/



    repe(p, pattern)
    {
        ret += mapping[p];
    }

    return ret;
}

#if _LOCAL
int32_t main()
{
    fast();

    /*deb;

    repe(e, mapping)
    {
        pair<p2, p2> a = e.first;
        if (mapping.count(a)!=1)
        {
            deb;
        }
        swap(a.first, a.second);
        if (setcontains(mapping, a))
        {
            deb;
        }
    }*/

    while (1)
    {
        int N;
        std::cin >> N;
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> P = BuildPattern(N);

        cout << "bef: ";
        repe(k, P)
        {
            cout << "a {" << k.first.first << ", " << k.first.second << "}. b {" << k.second.first << ", " << k.second.second << "}\n";
        }
        rep(i, P.size())
        {
            if (rand() % 2 == 0)
            {
                swap(P[i].first, P[i].second);
            }
        }
        int am = randint(0, 3);
        rotate(P, am * 90);
        cout << "mid: ";
        repe(k, P)
        {
            cout << "a {" << k.first.first << ", " << k.first.second << "}. b {" << k.second.first << ", " << k.second.second << "}\n";
        }
        int N_output = GetCardNumber(P);
        std::cout << "N: " << ", out:" << N_output << "\n";
    }

    quit;
}
#endif