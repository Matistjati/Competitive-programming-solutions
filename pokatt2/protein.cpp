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

#define enablell 1

#define ll long long
#if enablell
#define int ll
#define inf 2e18
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

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }


string p;
vi dp;
int base = 27;
const int maxN = 5e5+2;
const int logN = 19;

int hashing[maxN][logN];
int up[maxN][logN];

long long intPow(long long a, long long b)
{
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

struct Tree
{
    typedef p2 T;
    static constexpr int unit = INT_MIN;
    T f(T a, T b) // (any associative fn)
    {
        if (a.first == INT_MIN && b.first == INT_MIN) return a;
        if (a.first == INT_MIN && b.first != INT_MIN) return b;
        if (b.first == INT_MIN && a.first != INT_MIN) return a;

        int a1 = a.second;
        int b1 = b.second;

        per(d, logN) // power of two string comparison
        {
            if (hashing[a1][d] == hashing[b1][d])
            {
                a1 = up[a1][d];
                b1 = up[b1][d];
            }
        }

        return (p[a1] < p[b1]) ? a : b;

    }


    vector<T> s; int n;
    Tree(int n = 0) : s(2 * n, { unit,unit }), n(n) {}
    void update(int pos, T val)
    {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e)
    { // query [b, e)
        T ra = { unit,unit }, rb = { unit,unit };
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

// follow the graph in order to print our final string
void printS(int beg)
{
    int i = beg;
    while (true)
    {
        cout << p[i];
        i = dp[i];
        if (i == dp[i])break;
    }
}


int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, k, n);

    vvb removes(k,vb(k));
    rep(i, k)
    {
        dread(string, row);
        rep(j, row.size()) removes[i][j] = (row[j] == '1');
    }

    read(p);
    // add whitespace to the end so characters that can remove everything aren't forced to pick a letter
    p.push_back(' ');

    vi r(n);

    stack<pair<char,int>> st;

    // find furthest point each index can remove to in linear time
    per(i, p.size()-1)
    {
        int rv = i;
        while (st.size() && removes[p[i]-'a'][st.top().first-'a'])
        {
            rv = st.top().second;
            st.pop();
        }
        r[i] = rv+2;

        st.push(mp(p[i],rv));
    }

    dp = vi(n+1, inf);
    rep(i, n + 1) dp[i] = i; // necessary? idk

    Tree tree(n + 1);
    tree.update(n, { n,n });

    rep(d, logN) up[n][d] = n;

    per(i, n)
    {
        int ind = n;

        // query for lexographically smallest string in interval [i+1,r[i])
        p2 v = tree.query(i + 1, min(r[i], sz(p)));
        dp[i] = v.second;

        // build jump table and hash table
        up[i][0] = dp[i];
        hashing[i][0] = p[i] - 'a' + 1;
        repp(d, 1, logN)
        {
            up[i][d] = up[up[i][d - 1]][d - 1];
        }
        repp(d, 1, logN)
        {
            hashing[i][d] = hashing[i][d - 1] + intPow(base, d) * hashing[up[i][d-1]][d-1];
        }
        // only update after table is built so that comparisons can be accurate
        tree.update(i, { v.second,i });
    }

    // print the smallest string reachable from 0
    printS(0);

    quit;
}
