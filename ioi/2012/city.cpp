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

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T, typename U> inline pair<T,U> operator+(const pair<T, U>& l, const pair<T, U>& r) { return { l.first + r.first,l.second + r.second }; }
template <typename T, typename U> inline pair<T,U> operator-(const pair<T, U>& l, const pair<T, U>& r) { return { l.first - r.first,l.second - r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
inline int readintsigned() { int v = 0; int sign = 1; char c = getchar(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v * sign; }
inline int readint() { int v = 0; char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v; }
inline string readstring() { string s; char c; while ((c = getchar()) != EOF && c != '\n') { s.push_back(c); } return s; }
#define LOCAL _MSC_VER > 0
#if LOCAL
#define gc() getchar()
#define popcount(x) __popcnt(x)
#define assert(x) debassert(x)
#else
#define popcount(x) __builtin_popcount(x)
#define gc() getchar_unlocked()
#if 0
#include <bits/extc++.h>
using namespace __gnu_pbds;
#endif
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return x; }
};
//typedef __gnu_pbds::gp_hash_table<int, null_type, chash> h;

#endif

struct UF
{
    vi parent;
    vi size;
    ll n;

    UF(ll n) : n(n), parent(n), size(n,1)
    {
        rep(i, n) parent[i] = i;
    }

    ll find(ll x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void merge(ll a, ll b)
    {
        a = find(a), b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
    void addedge(vector<set<int>>& edges, ll a, ll b)
    {
        a = find(a), b = find(b);
        edges[a].insert(b);
        edges[b].insert(a);
    }
};

ll mod = 1e9;
//vvi edges;
//ll nodenumber = 0;
vp2 dirs = { {0,1},{0,-1},{1,0},{-1,0} };
set<p2> points;
map<p2, int> pointnum;
int* x;
int* y;

inline p2 rev(p2 a) { return mp(-a.first, -a.second); }
inline p2 transpose(p2 a) { return mp(a.second, a.first); }

pair<vvi, vi> gettree(ll n, p2 dir)
{
    vector<set<int>> edges(n);
    set<p2> visited;
    UF uf(n);
    rep(i, n)
    {
        p2 u = mp(x[i], y[i]);
        if (setcontains(points,mp(x[i],y[i])+dir))
        {
            uf.merge(pointnum[u + dir], pointnum[u]);
        }

        if (setcontains(points,mp(x[i],y[i])-dir))
        {
            uf.merge(pointnum[u - dir], pointnum[u]);
        }
    }

    p2 transdir = transpose(dir);
    rep(i, n)
    {
        p2 u = mp(x[i], y[i]);
        if (setcontains(points, mp(x[i], y[i]) + transdir))
        {
            uf.addedge(edges, pointnum[u + transdir], pointnum[u]);
        }

        if (setcontains(points, mp(x[i], y[i]) - transdir))
        {
            uf.addedge(edges, pointnum[u - transdir], pointnum[u]);
        }
    }

    vvi ret(n);
    rep(i, n)
    {
        ret[i] = vi(edges[i].begin(), edges[i].end());
    }
    return { ret,uf.size };
}

ll ans(ll u, ll p, ll depth, vvi& edges, vi& weights)
{
    ll ret = depth * weights[u];
    ret %= mod;

    repe(edge, edges[u])
    {
        if (edge == p) continue;
        ret = (ret + ans(edge, u, depth + 1, edges, weights)) % mod;
    }

    return ret%mod;
}

ll subtreesum(int u, int p, vvi& edges, vi& weights, vector<ll>& nodecumsum, ll& sum)
{
    ll ret = weights[u];
    sum += ret;

    repe(edge, edges[u])
    {
        if (edge == p) continue;
        ret += subtreesum(edge, u, edges, weights, nodecumsum,sum);
    }

    return (nodecumsum[u] = ret);
}

int DistanceSum(int n, int X[], int Y[])
{
    x = X;
    y = Y;

    rep(i, n)
    {
        pointnum[mp(x[i], y[i])] = i;
        points.insert(mp(x[i], y[i]));
    }

    // build shortest path tree. in grid, equivalent to bfs tree


    vvi rowtree, coltree;
    vi rowsize, colsize;
    tie(rowtree,rowsize) = gettree(n, mp(0, 1));
    tie(coltree,colsize) = gettree(n, mp(1, 0));

    ll ret=0;
    vector<ll> cumsumrow(n);
    vector<ll> cumsumcol(n);

    int rowroot = -1;
    int colroot = -1;
    rep(i, n) if (rowtree[i].size()) rowroot = i;
    rep(i, n) if (coltree[i].size()) colroot = i;

    ll sumrowtree =0;
    ll sumcoltree =0;
    subtreesum(rowroot, rowroot, rowtree, rowsize, cumsumrow,sumrowtree);
    subtreesum(colroot, colroot, coltree, colsize, cumsumcol,sumcoltree);


    rep(i, n)
    {
        ret += (cumsumrow[i])%mod * (sumrowtree - cumsumrow[i])%mod;
        ret %= mod;
        ret += (cumsumcol[i])%mod * (sumcoltree - cumsumcol[i])%mod;
        ret %= mod;
    }

    return ret;
}


#if LOCAL
int32_t main()
{
    /*dread3(int, m, c, r);

    readvector(int,)*/

    dread(int, n);
    vi x(n);
    vi y(n);
    rep(i, n)
    {
        cin >> x[i];
        cin >> y[i];
    }
    cout << DistanceSum(n, &x[0], &y[0]);
}
#endif