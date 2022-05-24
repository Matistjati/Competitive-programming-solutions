// Pragmas for faster code
#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

// Type definitions
#define enablell 0

#define ll long long
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

// IO, debugging
#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define read3(a,b,c) cin >> a >> b >> c
#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
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

// Loops
#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

// Helper
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define mp(a,b) (make_pair(a,b))
#define ceildiv(x,y) ((x + y - 1) / y)

// Heuristic time limit
auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

// Helpers
inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }

long long degree(long long a, long long k, long long p) {
    long long res = 1;
    long long cur = a;

    while (k) {
        if (k % 2) {
            res = (res * cur) % p;
        }
        k /= 2;
        cur = (cur * cur) % p;
    }
    return res;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    // We call a choice of ? a permutation
    // For each permutation, the answer is:
    // Sum distance of each one to end of string - ((num_ones-1)*(num_ones)/2)
    // The sum of distances is easy: each ? shows up 2^n_q/2 times, and 1 shows up 2^n_q times
    // For the ones(ones+1)/2, we use n choose k
    // Number of times 2 shows up: (n choose 2)
    // We do this up until n
    dread(string, in);

    int mod = 1e9 + 7;

    int n_q = 0;
    rep(i, in.size()) n_q += in[i] == '?';

    ll k = 1;
    rep(i, n_q - 1) k = (k * 2) % mod;

    ll k2 = (k * 2) % mod;

    if (n_q==0)
    {
        k = 1;
        k2 = 1;
    }

    vector<ll> fact(n_q+1);
    ll m = 1;
    rep(i, n_q+1)
    {
        fact[i] = m;
        m = (m * (i + 1)) % mod;
    }

    ll ans = 0;

    int num_ones = 0;
    rep(i, in.size())
    {
        if (in[i]=='?')
        {
            ans = (ans+ ((in.size()-i-1) * k)) % mod;
        }
        else if (in[i]=='1')
        {
            num_ones++;
            ans = (ans+((in.size()-i-1) * k2)) % mod;
        }
    }

    rep(i, n_q+1)
    {
        ll l = num_ones + i-1;
        ll a = ((l * (l + 1) / 2) % mod);
        ll m = (fact[i] * fact[n_q - i])%mod;

        ll b = (fact[n_q] * degree(m,mod-2, mod)) % mod;
        ll amount = (a * b) % mod;
        ans = (mod+ans-amount)%mod;
    }


    cout << ans;

    quit;
}
