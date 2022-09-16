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
typedef __gnu_pbds::gp_hash_table<int, int, chash> fast_map;
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


struct AngelBeats {
    using i64 = long long;
    static constexpr i64 INF = numeric_limits<i64>::max() / 2.1;

    struct alignas(32) Node {
        i64 sum = 0, g1 = 0, l1 = 0;
        i64 g2 = -INF, gc = 1, l2 = INF, lc = 1, add = 0;
    };

    vector<Node> v;
    i64 n, log;

    AngelBeats() {}
    AngelBeats(int _n) : AngelBeats(vector<i64>(_n)) {}
    AngelBeats(const vector<i64>& vc) {
        n = 1, log = 0;
        while (n < (int)vc.size()) n <<= 1, log++;
        v.resize(2 * n);
        for (i64 i = 0; i < (int)vc.size(); ++i) {
            v[i + n].sum = v[i + n].g1 = v[i + n].l1 = vc[i];
        }
        for (i64 i = n - 1; i; --i) update(i);
    }

    void range_chmin(int l, int r, i64 x) { inner_apply<1>(l, r, x); }
    void range_chmax(int l, int r, i64 x) { inner_apply<2>(l, r, x); }
    void range_add(int l, int r, i64 x) { inner_apply<3>(l, r, x); }
    void range_update(int l, int r, i64 x) { inner_apply<4>(l, r, x); }
    i64 range_min(int l, int r) { return inner_fold<1>(l, r); }
    i64 range_max(int l, int r) { return inner_fold<2>(l, r); }
    i64 range_sum(int l, int r) { return inner_fold<3>(l, r); }

private:
    void update(int k) {
        Node& p = v[k];
        Node& l = v[k * 2 + 0];
        Node& r = v[k * 2 + 1];

        p.sum = l.sum + r.sum;

        if (l.g1 == r.g1) {
            p.g1 = l.g1;
            p.g2 = max(l.g2, r.g2);
            p.gc = l.gc + r.gc;
        }
        else {
            bool f = l.g1 > r.g1;
            p.g1 = f ? l.g1 : r.g1;
            p.gc = f ? l.gc : r.gc;
            p.g2 = max(f ? r.g1 : l.g1, f ? l.g2 : r.g2);
        }

        if (l.l1 == r.l1) {
            p.l1 = l.l1;
            p.l2 = min(l.l2, r.l2);
            p.lc = l.lc + r.lc;
        }
        else {
            bool f = l.l1 < r.l1;
            p.l1 = f ? l.l1 : r.l1;
            p.lc = f ? l.lc : r.lc;
            p.l2 = min(f ? r.l1 : l.l1, f ? l.l2 : r.l2);
        }
    }

    void push_add(int k, i64 x) {
        Node& p = v[k];
        p.sum += x << (log + leading_zeros(k) - 31);
        p.g1 += x;
        p.l1 += x;
        if (p.g2 != -INF) p.g2 += x;
        if (p.l2 != INF) p.l2 += x;
        p.add += x;
    }
    void push_min(int k, i64 x) {
        Node& p = v[k];
        p.sum += (x - p.g1) * p.gc;
        if (p.l1 == p.g1) p.l1 = x;
        if (p.l2 == p.g1) p.l2 = x;
        p.g1 = x;
    }
    void push_max(int k, i64 x) {
        Node& p = v[k];
        p.sum += (x - p.l1) * p.lc;
        if (p.g1 == p.l1) p.g1 = x;
        if (p.g2 == p.l1) p.g2 = x;
        p.l1 = x;
    }
    void push(int k) {
        Node& p = v[k];
        if (p.add != 0) {
            push_add(k * 2 + 0, p.add);
            push_add(k * 2 + 1, p.add);
            p.add = 0;
        }
        if (p.g1 < v[k * 2 + 0].g1) push_min(k * 2 + 0, p.g1);
        if (p.l1 > v[k * 2 + 0].l1) push_max(k * 2 + 0, p.l1);

        if (p.g1 < v[k * 2 + 1].g1) push_min(k * 2 + 1, p.g1);
        if (p.l1 > v[k * 2 + 1].l1) push_max(k * 2 + 1, p.l1);
    }

    void subtree_chmin(int k, i64 x) {
        if (v[k].g1 <= x) return;
        if (v[k].g2 < x) {
            push_min(k, x);
            return;
        }
        push(k);
        subtree_chmin(k * 2 + 0, x);
        subtree_chmin(k * 2 + 1, x);
        update(k);
    }

    void subtree_chmax(int k, i64 x) {
        if (x <= v[k].l1) return;
        if (x < v[k].l2) {
            push_max(k, x);
            return;
        }
        push(k);
        subtree_chmax(k * 2 + 0, x);
        subtree_chmax(k * 2 + 1, x);
        update(k);
    }

    template <int cmd>
    inline void _apply(int k, i64 x) {
        if constexpr (cmd == 1) subtree_chmin(k, x);
        if constexpr (cmd == 2) subtree_chmax(k, x);
        if constexpr (cmd == 3) push_add(k, x);
        if constexpr (cmd == 4) subtree_chmin(k, x), subtree_chmax(k, x);
    }

    template <int cmd>
    void inner_apply(int l, int r, i64 x) {
        if (l == r) return;
        l += n, r += n;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) _apply<cmd>(l++, x);
                if (r & 1) _apply<cmd>(--r, x);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <int cmd>
    inline i64 e() {
        if constexpr (cmd == 1) return INF;
        if constexpr (cmd == 2) return -INF;
        return 0;
    }

    template <int cmd>
    inline void op(i64& a, const Node& b) {
        if constexpr (cmd == 1) a = min(a, b.l1);
        if constexpr (cmd == 2) a = max(a, b.g1);
        if constexpr (cmd == 3) a += b.sum;
    }

    template <int cmd>
    i64 inner_fold(int l, int r) {
        if (l == r) return e<cmd>();
        l += n, r += n;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        i64 lx = e<cmd>(), rx = e<cmd>();
        while (l < r) {
            if (l & 1) op<cmd>(lx, v[l++]);
            if (r & 1) op<cmd>(rx, v[--r]);
            l >>= 1;
            r >>= 1;
        }
        if constexpr (cmd == 1) lx = min(lx, rx);
        if constexpr (cmd == 2) lx = max(lx, rx);
        if constexpr (cmd == 3) lx += rx;
        return lx;
    }
};


struct Tree
{
    vi tree;
    int n;
    Tree(int n) : tree(n*4, inf), n(n) {}
    Tree() {}

    void set(int l, int r, int v)
    {
        repp(i, l, r + 1) tree[i] = v;
    }

    void chminUpdate(int l, int r, int v)
    {
        repp(i, l, r + 1) tree[i] = min(tree[i], v);
    }

    int query(int l, int r)
    {
        int ret = inf;
        repp(i, l, r + 1) ret = min(ret, tree[i]);
        return ret;
    }
};

void initDP(int u, int p, vvi& edges, vi& dp, vector<AngelBeats>& childValues)
{
    rep(i, edges[u].size())
    {
        int edge = edges[u][i];
        if (edge == 0 || edge == p) continue;
        if (childValues[u].n) childValues[u].range_chmin(i,i+1, dp[u]+1);
        dp[edge] = dp[u] + 1;
        initDP(edge, u,  edges, dp, childValues);
    }
}

void rootTree(int u, int p, vvi& edges, vvi& children, vi& par)
{
    par[u] = p;
    repe(edge, edges[u])
    {
        if (edge == p) continue;
        children[u].emplace_back(edge);
        rootTree(edge, u, edges, children, par);
    }
}

void updateDP(int n, vi& par, vector<map<int,int>>& nodeToPos, vector<AngelBeats>& childValues, vi& dp)
{
    rep(i, n)
    {
        if (par[i] != -1)
        {
            int index = nodeToPos[par[i]][i];
            dp[i] = min((ll)dp[i], childValues[par[i]].range_min(index, index+1));
        }
    }
}

int32_t main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Christian\\in.txt");
#endif

    dread2(int, n, m);

    vvi edges(n);

    rep(i, n - 1)
    {
        dread2(int, a, b);
        a--; b--;
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }

    readvector(int, monster, m);
    rep(i, m) monster[i]--;

    vvi children(n);
    vector<AngelBeats> childValues(n);
    vector<map<int, int>> nodeToPos(n);
    vi par(n);
    rootTree(1, -1, edges, children, par);
    rep(i, n)
    {
        rep(j, children[i].size())
        {
            nodeToPos[i][children[i][j]] = j;
        }
        childValues[i] = AngelBeats(children[i].size());
        childValues[i].range_update(0, children[i].size(), inf);
    }

    vi dp(n, inf);
    dp[1] = 0;
    initDP(1, -1, children, dp, childValues);
    if (par[0] != -1)
    {
        int index = nodeToPos[par[0]][0];
        childValues[par[0]].range_update(index, index+1, inf);
    }

    int monsterPos = 0;

    rep(i, m)
    {
        // Pull
        // Parent
        if (par[monsterPos] != -1 && par[monsterPos] != monster[i])
        {
            int index = nodeToPos[par[monsterPos]][monsterPos];
            dp[monsterPos] = min((ll)dp[monsterPos], childValues[par[monsterPos]].range_min(index, index + 1));
            dp[monsterPos] = min(dp[monsterPos], dp[par[monsterPos]]+1);
        }
        // Children. Unnecessary?
        if (setcontains(nodeToPos[monsterPos], monster[i]))
        {
            int monsterIndex = nodeToPos[monsterPos][monster[i]];
            // Split query into two parts
            dp[monsterPos] = min((ll)dp[monsterPos], childValues[monsterPos].range_min(0, monsterIndex)+1);
            dp[monsterPos] = min((ll)dp[monsterPos], childValues[monsterPos].range_min(monsterIndex+1, children[monsterPos].size())+1);
        }
        else
        {
            // If monster is not a child, we take the best of all
            dp[monsterPos] = min((ll)dp[monsterPos], childValues[monsterPos].range_min(0, children[monsterPos].size())+1);
        }
        if (par[monsterPos] != -1)
        {
            int index = nodeToPos[par[monsterPos]][monsterPos];
            childValues[par[monsterPos]].range_chmin(index, index+1, dp[monsterPos]);
        }

        // Push
        int newNode = monster[i];
        int newNodeValue = dp[monster[i]];
        // Parent
        if (par[newNode] != -1)
        {
            int index = nodeToPos[par[newNode]][newNode];
            newNodeValue = min((ll)newNodeValue, childValues[par[newNode]].range_min(index, index+1));
            // Push
            if (par[newNode] != monsterPos)
            {
                dp[par[newNode]] = min(dp[par[newNode]], newNodeValue+1);
            }
        }

        // Children
        if (setcontains(nodeToPos[newNode], monsterPos))
        {
            int prevPosIndex = nodeToPos[newNode][monsterPos];
            // Split query into two parts
            childValues[newNode].range_chmin(0, prevPosIndex, newNodeValue+1);
            childValues[newNode].range_chmin(prevPosIndex + 1, children[newNode].size(), newNodeValue+1);
        }
        else
        {
            // If monster is not a child, we take the best of all
            childValues[newNode].range_chmin(0, children[newNode].size(), newNodeValue+1);
        }

        // Update parent child
        if (par[newNode] != -1)
        {
            int index = nodeToPos[par[newNode]][newNode];
            childValues[par[newNode]].range_update(index, index+1, inf);
        }

        monsterPos = monster[i];
        dp[monsterPos] = inf;
        noop;
        //updateDP(n, par, nodeToPos, childValues, dp);
        noop;
    }

    updateDP(n, par, nodeToPos, childValues, dp);


    if (*min_element(all(dp)) >= inf) cout << -1;
    else cout << *min_element(all(dp));

    quit;
}