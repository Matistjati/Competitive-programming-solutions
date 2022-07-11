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

typedef long long ll;
#if enablell
#define int ll
#define inf int(5e18)
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
#define debif(expr) if(expr) deb;
#define debassert(expr) if(!(expr)) deb;
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

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

#if _MSC_VER > 0
#define gc() getchar()
#else
#if 0
#include <bits/extc++.h>
using namespace __gnu_pbds;
#endif
#define gc() getchar_unlocked()
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return x; }
};
//typedef __gnu_pbds::gp_hash_table<int, null_type, chash> h;

#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
inline p2 operator+(const p2& l, const p2& r) { return mp(l.first + r.first, l.second + r.second); }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
inline int readintsigned() { int v = 0; int sign = 1; char c = getchar(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v * sign; }
inline int readint() { int v = 0; char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v; }
inline string readstring() { string s; char c; while ((c = getchar()) != EOF && c != '\n') { s.push_back(c); } return s; }
#if 1
random_device rd;
mt19937 rng(rd());
// lower inclusive, upper exclusive
inline int randint(int low, int high) { return uniform_int_distribution<int>(low, high - 1)(rng); }
inline int randint(int high) { return randint(0, high); }
#endif

#define lg1e5 18
int up[int(1e5) + 1][lg1e5];
int upPath[int(1e5) + 1][lg1e5];

vi tin, tout;
int timer = 0;
vi depth;
vb is_shop;
vi sub;
vi costifparent;

void rootTree(vvp3& edges, vi& edgeToNode, int curr, int parent, int dist)
{
    tin[curr] = ++timer;


    depth[curr] = dist;

    repe(edge, edges[curr])
    {
        int node, w, index;
        tie(node, w, index) = edge;

        if (node == parent) continue;

        edgeToNode[index] = node;

        rootTree(edges, edgeToNode, node, curr, dist+w);
    }

    tout[curr] = ++timer;
}


int closestshop(vvp3& edges, int u, int p)
{
    int ret = is_shop[u] ? 0 : inf;

    repe(edge, edges[u])
    {
        int v, w, _;
        tie(v, w, _) = edge;

        if (v == p) continue;

        ret = min(ret, closestshop(edges, v, u) + w);
    }

    sub[u] = ret;
    return ret;
}

void lift(vvp3& edges, int u, int p)
{
    //(u == 0||u==8);
    up[u][0] = p;
    upPath[u][0] = costifparent[p];
    repp(d, 1, lg1e5)
    {
        upPath[u][d] = min(upPath[u][d - 1], upPath[up[u][d - 1]][d-1]);
        up[u][d] = up[up[u][d - 1]][d - 1];
    }

    repe(edge, edges[u])
    {
        int v = get<0>(edge);
        if (v == p) continue;
        lift(edges, v, u);
    }
}

// is u ancestor of v
bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int i = lg1e5; i >= 0; i--)
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];

    return up[u][0];
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread4(int, n, s, q, e);
    e--;

    vvp3 edges(n);
    rep(i, n - 1)
    {
        dread3(int, a, b, w);
        a--;
        b--;
        edges[a].emplace_back(b, w, i);
        edges[b].emplace_back(a, w, i);
    }

    is_shop.resize(n);
    rep(i, s)
    {
        dread(int, j);
        j--;
        is_shop[j] = true;
    }

    vi edgeToNode(n-1);

    tin.resize(n);
    tout.resize(n);
    depth.resize(n);

    rootTree(edges, edgeToNode, e, e, 0);

    sub.resize(n);
    closestshop(edges, e, e);

    costifparent.resize(n);
    rep(i, n) costifparent[i] = sub[i] - depth[i];

    lift(edges, e, e);

    while (q--)
    {
        dread2(int, i, r);
        i--;
        r--;

        int removedNode = edgeToNode[i];


        if (is_ancestor(removedNode, r))
        {
            int ans = inf;
            ans = min(ans, costifparent[r]);
            int u = r;

            for (int i = lg1e5-1; i >= 0; i--)
                if (!is_ancestor(up[u][i], removedNode) || up[u][i]==removedNode)
                {
                    ans = min(ans, upPath[u][i]);
                    u = up[u][i];
                }

            if (ans > int(1e14)) cout << "oo";
            else cout << ans+depth[r];
        }
        else
        {
            cout << "escaped";
        }
        cout << "\n";
    }

    quit;
}