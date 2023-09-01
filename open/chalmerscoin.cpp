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

#if 1
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

static const unsigned char byteswap[] = {
        0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
        0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
        0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
        0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
        0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
        0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
        0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
        0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
        0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
        0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
        0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
        0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
        0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
        0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
        0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
        0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
        0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
        0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
        0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
        0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
        0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
        0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
        0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
        0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
        0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
        0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
        0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
        0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
        0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
        0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
        0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
        0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

inline ull reversenum(ull x)
{
    ull rev = bswap64(x);
    rev = byteswap[rev & 0xFF]
        | ((ull)byteswap[(rev >> 8) & 0xFF] << 8)
        | ((ull)byteswap[(rev >> 16) & 0xFF] << 16)
        | ((ull)byteswap[(rev >> 24) & 0xFF] << 24)
        | ((ull)byteswap[(rev >> 32) & 0xFF] << 32)
        | ((ull)byteswap[(rev >> 40) & 0xFF] << 40)
        | ((ull)byteswap[(rev >> 48) & 0xFF] << 48)
        | ((ull)byteswap[(rev >> 56) & 0xFF] << 56);
    return rev;
}

inline uint32_t bit_set_to(uint32_t number, uint32_t n, bool x) {
    return (number & ~((uint32_t)1 << n)) | ((uint32_t)x << n);
}

uint32_t oneswap[1 << 18];
int precompeven[1 << 21];
void precomp()
{
    array<uint32_t, 8> weirdNumber = { 1, 1, 0, 0, 1, 1, 0, 1 };
    rep(mask, 1 << 21)
    {
        int newv = 0;
        rep(i, 16)
        {
            ll y = 4 * ((mask & (1ULL << (i % 32))) > 0);
            y += 2 * ((mask & (1ULL << ((i + 1) % 32))) > 0);
            y += ((mask & (1ULL << ((i + 5) % 32))) > 0);
            newv = bit_set_to(newv, (i % 32), weirdNumber[y]);
        }
        precompeven[mask] = newv;
    }

    for (int mask = 0; mask < (1 << 18); ++mask) {
        int v = 0;
        for (int i = 0; i < 18; ++i) {
            v |= ((mask >> i) & 1) << (17 - i);
        }
        oneswap[mask] = v;
    }
}


inline ull hashfirst(ull o)
{
#pragma GCC ivdep
#pragma GCC unroll 8
    rep(i, 8) {
        uint32_t newo = 0;
        newo = precompeven[o & 2097151];
        newo |= precompeven[(o >> 16) & 65535 | (newo & 31) << 16] << 16;
        o = newo;
    }

    return o;
}

inline ull hashh(ull k)
{
    rep(i, 16)
    {
        ull rev = bswap64(k);
        rev = byteswap[rev & 0xFF]
            | ((ull)byteswap[(rev >> 8) & 0xFF] << 8)
            | ((ull)byteswap[(rev >> 16) & 0xFF] << 16)
            | ((ull)byteswap[(rev >> 24) & 0xFF] << 24)
            | ((ull)byteswap[(rev >> 32) & 0xFF] << 32)
            | ((ull)byteswap[(rev >> 40) & 0xFF] << 40)
            | ((ull)byteswap[(rev >> 48) & 0xFF] << 48)
            | ((ull)byteswap[(rev >> 56) & 0xFF] << 56);

        bool overflow = false;
        if (rev > ULLONG_MAX - k) overflow = true; // `a + x` would overflow
        k += rev;
        k = ((k ^ 12157665459056928801ULL) >> overflow) | ((ull)overflow << 63);
    }

    return k;
}



int32_t main()
{
    fast();
#if 0 && _LOCAL
    ifstream instream("C:\\users\\matis\\source\\repos\\comp_prog\\x64\\debug\\in.txt");
    cin.rdbuf(instream.rdbuf());
#endif


    precomp();

    vector<ull> numbers(10);

    rep(i, numbers.size()) {
        dread(ull, num);
        numbers[i] = num;
    }

    const int numbits = 18;

    rep(i, numbers.size())
    {
        ull number = (ull)numbers[i] << 36;
        ull bestScore = ULLONG_MAX;
        ll bestK = 0;

        fast_map<ull, ull> heven;
        fast_map<ull, ull> hodd;

        ull base = 0;
        repp(i, 35, 64)
        {
            if (i % 2 == 0 && number & (1ULL << i))
            {
                base += 1ULL << (i);
            }
        }
        ull basecontract = 0;
        rep(i, 32) if (base & (1ULL << (i * 2))) basecontract |= 1ULL << (31 - i);

#pragma ivdep
        rep(mask, (1ULL << numbits))
        {
            uint32_t o = basecontract | oneswap[mask] << 14;
            o = hashfirst(o);

            if (!setcontains(heven, o))
            {
                heven[o] = mask;
            }
        }

        base = 0;
        repp(i, 35, 64)
        {
            if (i % 2 == 1 && number & (1ULL << i))
            {
                base += 1ULL << (i);
            }
        }
        basecontract = 0;
        rep(i, 32) if (base & (1ULL << (i * 2 + 1))) basecontract |= 1ULL << (31 - i);

#pragma ivdep
        rep(mask, (1ULL << numbits))
        {
            uint32_t o = basecontract | oneswap[mask] << 14;
            o = hashfirst(o);

            if (!setcontains(hodd, o))
            {
                hodd[o] = mask;
            }
        }

        auto expandeven = [](uint32_t o)
        {
            ull k = 0;
#pragma ivdep
#pragma GCC unroll 32
            rep(i, 32) if (o & (1ULL << i)) k += 1ULL << (i * 2);
            k = reversenum(k);

            k >>= 1;
            return k;
        };

        auto expandodd = [](uint32_t o)
        {
            ull k = 0;
#pragma ivdep
#pragma GCC unroll 32
            rep(i, 32) if (o & (1ULL << i)) k |= (1ULL << (i * 2 + 1));
            k = reversenum(k);

            k <<= 1;
            return k;
        };

        repe(aa, heven)
        {
            repe(bb, hodd)
            {
                ull a = aa.second;
                ull b = bb.second;

                ull oddv = 0;
                ull evenv = 0;
                rep(i, 36)
                {
                    if (a & (1ULL << i)) evenv += (1ULL << (2 * i));

                    if (b & (1ULL << i)) oddv += (1ULL << (2 * i + 1));
                }

                ull score = hashh(expandeven(aa.first) + expandodd(bb.first));

                if (score < bestScore)
                {
                    bestScore = score;
                    bestK = oddv + evenv;
                }
            }
        }

        cout << ((ull)bestK) << "\n";
    }

    quit;
}
