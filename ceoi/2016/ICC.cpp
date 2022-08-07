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
struct UF
{
    int n;
    vi parent;
    vi size;

    UF(int n) : n(n), size(n, 1), parent(n)
    {
        rep(i, n) parent[i] = i;
    }

    int find(int u) { return (parent[u] == u) ? u : parent[u] = find(parent[u]); }

    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (size[a] < size[b]) swap(a, b);

        parent[b] = a;
        size[a] += size[b];
    }
};

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
#define popcount(x) __popcnt(x)
#define leading_zeros(x) _lzcnt_u32(x)
#define assert(x) debassert(x)


#if 1
bool query(int sa, int sb, int a[], int b[])
{
    cout << "Is there road between ";
    rep(i, sa) cout << a[i] << " ";
    cout << ", and ";
    rep(i, sb) cout << b[i] << " ";
    cout << "\n";

    dread(int, ret);
    return ret;
}
void setRoad(int a, int b) { cout << "road between " << a << " and " << b << "\n"; }

#else
UF judgeuf(0);
int n;
set<p2> jedges;
int n_q = 0;

set<p2> intervals;

void adduf()
{
    if (jedges.size() == n - 1) return;

    if (false)
    {
        while (true)
        {
            int a = rand() % n, b = rand() % n;
            if (judgeuf.find(a) != judgeuf.find(b))
            {
                judgeuf.merge(a, b);
                jedges.insert(mp(min(a, b), max(a, b)));
                return;
            }
        }
    }
    else if (true)
    {
        if (intervals.size() < 2) return;
        p2 a = *intervals.begin();
        intervals.erase(intervals.begin());
        p2 b = *intervals.begin();
        intervals.erase(intervals.begin());
        judgeuf.merge(a.first, b.second);
        jedges.insert(mp(a.first, b.second));
        intervals.insert(mp(a.first, b.second));
    }

}
void init(int n)
{
    judgeuf = UF(n);
    rep(i, n) intervals.insert(mp(i, i));
    adduf();
}

bool query(int sa, int sb, int a[], int b[])
{
    n_q++;
    rep(i, sa) rep(j, sb)
    {
        if (j == i) continue;
        if (setcontains(jedges, mp(min(a[i] - 1, b[j] - 1), max(a[i] - 1, b[j] - 1))))
        {
            return true;
        }
    }

    return false;
}

void setRoad(int a, int b)
{
    assert(setcontains(jedges, mp(min(a, b), max(a, b))));
    adduf();
}
#endif
#else
#define popcount(x) __builtin__popcount(x)
#define leading_zeros(x) __builtin_clz(x)
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

#include "icc.h"
#endif

const int mod = 1e9 + 7;

bool q(vvi& components, vi a, vi b)
{
    vi qa;
    vi qb;
    repe(i, a) repe(j, components[i]) qa.push_back(j + 1);
    repe(i, b) repe(j, components[i]) qb.push_back(j + 1);
    return query(qa.size(), qb.size(), &qa[0], &qb[0]);
}

bool q2(vi a, vi b)
{
    rep(i, a.size()) a[i]++;
    rep(i, b.size()) b[i]++;
    return query(a.size(), b.size(), &a[0], &b[0]);
}

pair<vi, vi> split(vi& v)
{
    int half_size = v.size() / 2;
    vi split_lo(v.begin(), v.begin() + half_size);
    vi split_hi(v.begin() + half_size, v.end());
    return { split_lo, split_hi };
}

void run(int n)
{
    UF uf(n);
    rep(times, n - 1)
    {
        vvi components2(n);

        rep(i, n)
        {
            components2[uf.find(i)].push_back(i);
        }

        vvi components;
        rep(i, n)
        {
            if (components2[i].size())
            {
                components.push_back(components2[i]);
            }
        }

        vi componentInd;
        rep(i, components.size())
        {
            componentInd.push_back(i);
        }



        // Computing a xor b
        int k = 0;
        int hi = 32-leading_zeros(componentInd.back());
        vi diff(hi, true);
        rep(i, hi)
        {
            vi lo;
            vi hi;
            rep(j, componentInd.size())
            {
                if (componentInd[j] & (1 << i)) lo.push_back(componentInd[j]);
                else hi.push_back(componentInd[j]);
            }

            diff[i] = q(components, lo, hi);
        }

        // Atleast one one bit is true (differing), otherwise a==b, which is a contradiction
        int diffBit = -1;
        rep(i, hi) if (diff[i]) diffBit = i;
        int qa = 1 << diffBit;
        int qb = 0;
        rep(i, hi)
        {
            if (i == diffBit) continue;

            if (diff[i])
            {
                vi a;
                vi b;

                // Determine the bit of qb
                // a will contain qa
                repe(j, componentInd) if (j & (1 << diffBit)) a.push_back(j);
                repe(j, componentInd) if (!(j & (1 << diffBit))&&(j & (1 << i))) b.push_back(j);

                // If b contains qb, qa[i] = 0, qb[i] = 1. Else reverse
                if (q(components, a, b)) qb |= 1 << i;
                else qa |= 1 << i;
            }
            else
            {
                vi a;
                vi b;

                // Determine the bit of qb
                // a will contain qa
                repe(j, componentInd) if (j & (1 << diffBit)) a.push_back(j);
                repe(j, componentInd) if (!(j & (1 << diffBit)) && (j & (1 << i))) b.push_back(j);

                // If a contains qa and b contains qb, qa[i] = 1, qb[i] = 1. Else reverse
                if (q(components, a, b))
                {
                    qb |= 1 << i;
                    qa |= 1 << i;
                }

            }
        }


        // a and b are now the components

        vi a;
        vi b;
        repe(j, components[qa]) a.push_back(j);
        repe(j, components[qb]) b.push_back(j);

        while (a.size() > 1 || b.size() > 1)
        {
            if (a.size() < b.size()) a.swap(b);

            vi lo, hi;
            tie(lo, hi) = split(a);

            // If yes, discard split_hi
            if (q2(lo, b)) a = lo;
            else a = hi;
        }

        uf.merge(a[0], b[0]);
        setRoad(a[0] + 1, b[0] + 1);
    }
}

#if _MSC_VER > 0
int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\joshua.jeffmarander\\downloads\\segs\\fil\\in\\fil2l.in");
#endif

#if 0
    cin >> n;
    init(n);
    run(n);
#else
    dread(int, n);
    run(n);
#endif
    quit;
}
#endif