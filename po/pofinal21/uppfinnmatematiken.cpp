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
#define FILE_TC 1
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

int c, n, t;
vvi parents;
vvi children;
vi value;
vi cost;
vi cnt;
vi taken;
unordered_set<int> takenset;
int timespent = 0;

inline double heuristicgreedy1(int value, int cost)
{
    if (cost == 0) return value + 1e9;
    return (value + 0.) / cost;
}

void solvegreedy()
{
    priority_queue<pair<double, int>> pq;
    rep(i, n) if (cnt[i] == 0) pq.emplace(-heuristicgreedy1(value[i], cost[i]), i);

    while (pq.size())
    {
        double _; int node;
        tie(_, node) = pq.top();
        pq.pop();

        if (cost[node] + timespent > t) continue;
        timespent += cost[node];
        taken.emplace_back(node);

        repe(c, children[node])
        {
            cnt[c]--;
            if (cnt[c] == 0)
            {
                pq.emplace(-heuristicgreedy1(value[c], cost[c]), c);
            }
        }
    }
}

double heuristic(int value, int cost)
{
    if (cost == 0) return value + 1e9;
    return (value + 0.) / cost;
}

vp2 dpparents;
p2 getparentscore(int u)
{
    if (dpparents[u].first != -1) return dpparents[u];
    p2 ret = { value[u],cost[u] };

    repe(p, parents[u])
    {
        ret += getparentscore(p);
    }
    return dpparents[u] = ret;
}

void findallparents(int u, unordered_set<int>& ret)
{
    if (setcontains(ret, u)) return;
    ret.insert(u);
    repe(p, parents[u])
    {
        findallparents(p, ret);
    }
}

void greedybetter()
{
    dpparents.resize(n, mp(-1, -1));


    vp2 nodestats(n);
    priority_queue<pair<double, int>> pq;
    vector<unordered_set<int>> fullparents;
    rep(i, n)
    {
        unordered_set<int> parens;
        findallparents(i, parens);
        repe(p, parens)
        {
            nodestats[i].first += value[p];
            nodestats[i].second += cost[p];
        }
        fullparents.emplace_back(parens);
        pq.emplace(nodestats[i].first / (nodestats[i].second + 0.), i);
    }
    vi used(n);

    while (taken.size() < n &&
#if !_LOCAL
        elapsedmillis() < 1900)
#else
        true)
#endif
    {
        vector<pair<double, int>> alternatives;
        vp2 updatedstats(n);
        rep(i, n)
        {
            if (used[i]) continue;
            p2& v = updatedstats[i];
            v = nodestats[i];

            if (fullparents.size() < taken.size())
            {
                repe(p, fullparents[i])
                {
                    if (setcontains(takenset, p))
                    {
                        v = v - mp(value[p], cost[p]);
                    }
                }
            }
            else
            {
                repe(p, takenset)
                {
                    if (setcontains(fullparents[i], p))
                    {
                        v = v - mp(value[p], cost[p]);
                    }
                }
            }
            alternatives.emplace_back(heuristic(v.first, v.second), i);
        }
        sort(rall(alternatives));
        if (alternatives.size() == 0) break;

        int node = alternatives[0].second;

        if (used[node]) continue;
        if (updatedstats[node].second + timespent > t)
        {
            used[node] = 1;
            continue;
        }
        timespent += updatedstats[node].second;

        vi order;
        queue<int> q;
        q.emplace(node);

        while (q.size())
        {
            int u = q.front();
            q.pop();

            if (used[u]) continue;
            used[u] = 1;
            order.push_back(u);

            repe(p, parents[u]) q.emplace(p);
        }



        unordered_set<int> orderset(all(order));
        vi finalorder;
        q = queue<int>();
        rep(i, order.size()) if (cnt[order[i]] == 0) q.emplace(order[i]);
        while (q.size())
        {
            int node = q.front();
            q.pop();
            finalorder.push_back(node);

            repe(c, children[node])
            {
                cnt[c]--;
                if (cnt[c] == 0 && setcontains(orderset, c))
                {
                    q.push(c);
                }
            }
        }



        repe(o, finalorder) taken.push_back(o);
        repe(o, finalorder) takenset.insert(o);
    }
}

void updatestatsgreedy(vi& used, vp2& stats)
{

    stats.resize(0);
    stats.resize(n);

    vi count(n);
    rep(i, n) count[i] = parents[i].size();
    queue<int> q;
    rep(i, n) if (count[i] == 0) q.emplace(i);
    while (q.size())
    {
        int u = q.front();
        q.pop();

        if (!used[u]) stats[u] += mp(value[u], cost[u]);

        repe(c, children[u])
        {
            if (!used[u]) stats[c] += stats[u];
            count[c]--;
            if (count[c] == 0)
            {
                q.emplace(c);
            }
        }
    }
}

void greedyfast()
{

    vp2 nodestats(n);

    vi used(n);
    vi impossible(n);
    int k = 0;
    vector<pair<double, int>> alternatives;

    while (taken.size() < n &&
#if !_LOCAL
        elapsedmillis() < 1900)
#else
        true)
#endif
    {

        if (alternatives.empty() || k % 150 == 0)
        {
            updatestatsgreedy(used, nodestats);
            alternatives.resize(0);
            rep(i, n)
            {
                if (used[i] || impossible[i]) continue;
                p2& v = nodestats[i];

                alternatives.emplace_back(heuristic(v.first, v.second), i);
            }
            sort(all(alternatives));
            if (alternatives.empty()) break;
        }



        int node = alternatives.back().second;
        alternatives.pop_back();
        if (used[node]) continue;
        if (nodestats[node].second + timespent > t)
        {
            impossible[node] = 1;
            continue;
        }
        timespent += nodestats[node].second / 1.3;
        k++;

        vi order;
        queue<int> q;
        q.emplace(node);

        while (q.size())
        {
            int u = q.front();
            q.pop();

            if (used[u]) continue;
            used[u] = 1;
            order.push_back(u);

            repe(p, parents[u]) q.emplace(p);
        }



        unordered_set<int> orderset(all(order));
        vi finalorder;
        q = queue<int>();
        rep(i, order.size()) if (cnt[order[i]] == 0) q.emplace(order[i]);
        while (q.size())
        {
            int node = q.front();
            q.pop();
            finalorder.push_back(node);

            repe(c, children[node])
            {
                cnt[c]--;
                if (cnt[c] == 0 && setcontains(orderset, c))
                {
                    q.push(c);
                }
            }
        }

        repe(o, finalorder) taken.push_back(o);
        repe(o, finalorder) takenset.insert(o);
    }
}

void updatestats(int u, p2 s, vi& used, vp2& stats)
{
    if (!used[u]) s += mp(value[u], cost[u]);
    stats[u] = s;
    repe(c, children[u]) updatestats(c, s, used, stats);
}

// The tree is pretty shallow
void solvelargetree()
{
    vi roots;
    rep(i, n) if (cnt[i] == 0) roots.push_back(i);

    int k = 0;
    vi used(n);
    vi impossible(n);
    vector<pair<double, int>> alternatives;
    vp2 updatedstats(n);
    while (taken.size() < n &&
#if !_LOCAL
        elapsedmillis() < 1900)
#else
        true)
#endif
    {
        if (alternatives.empty() || k % 130 == 0)
        {
            updatestats(0, mp(0, 0), used, updatedstats);
            alternatives.resize(0);
            rep(i, n)
            {
                if (used[i] || impossible[i]) continue;
                p2& v = updatedstats[i];


                alternatives.emplace_back(heuristic(v.first, v.second), i);
            }
            sort(all(alternatives));
            if (alternatives.empty()) break;

        }




        int u = alternatives.back().second;
        alternatives.pop_back();
        if (used[u]) continue;
        if (updatedstats[u].second + timespent > t)
        {
            impossible[u] = 1;
            continue;
        }
        timespent += updatedstats[u].second / 1.17;
        k += 1;
        vi toadd;
        while (!used[u])
        {
            toadd.push_back(u);
            used[u] = 1;
            if (parents[u].empty()) break;
            u = parents[u][0];
        }
        reverse(all(toadd));
        rep(i, toadd.size()) taken.push_back(toadd[i]);
    }


}

void updatestatsupside(vi& used, vp2& stats)
{

    stats.resize(0);
    stats.resize(n);

    rep(i, n) cnt[i] = parents[i].size();
    queue<int> q;
    rep(i, n) if (cnt[i] == 0) q.emplace(i);
    while (q.size())
    {
        int u = q.front();
        q.pop();

        if (!used[u]) stats[u] += mp(value[u], cost[u]);

        repe(c, children[u])
        {
            if (!used[u]) stats[c] += stats[u];
            cnt[c]--;
            if (cnt[c] == 0)
            {
                q.emplace(c);
            }
        }
    }
}

void solvereversetree()
{
    int k = 0;
    vi used(n);
    vi impossible(n);
    vector<pair<double, int>> alternatives;
    vp2 updatedstats(n);
    while (taken.size() < n &&
#if !_LOCAL
        elapsedmillis() < 1900)
#else
        true)
#endif
    {
        if (alternatives.empty() || k % 160 == 0)
        {
            updatestatsupside(used, updatedstats);
            alternatives.resize(0);
            rep(i, n)
            {
                if (used[i] || impossible[i]) continue;
                p2& v = updatedstats[i];


                alternatives.emplace_back(heuristic(v.first, v.second), i);
            }
            sort(all(alternatives));
            if (alternatives.empty()) break;

        }




        int u = alternatives.back().second;
        alternatives.pop_back();
        if (used[u]) continue;
        if (updatedstats[u].second + timespent > t)
        {
            impossible[u] = 1;
            continue;
        }
        timespent += updatedstats[u].second / 1.028;
        k += 1;
        vi toadd;
        queue<int> q;
        q.emplace(u);
        while (q.size())
        {
            int u = q.front();
            q.pop();
            if (used[u]) continue;
            used[u] = 1;
            toadd.push_back(u);
            if (parents[u].empty()) continue;
            repe(p, parents[u]) q.emplace(p);
        }
        reverse(all(toadd));
        rep(i, toadd.size()) taken.push_back(toadd[i]);
    }
}

void verify()
{
    set<int> takenset(all(taken));
    debassert(takenset.size() == taken.size());

    int timespent = 0;
    vi proven(n);
    int score = 0;
    repe(i, taken)
    {
        if (proven[i])
        {
            deb;
        }
        proven[i] = 1;
        if (i < 0 || i >= n)
        {
            deb;
        }

        repe(p, parents[i])
        {
            if (!proven[p]) deb;
        }

        timespent += cost[i];
        score += value[i];
        if (timespent > t)
        {
            deb;
        }
    }
    cerr << "score: " << score << ", lg10: " << log10(score) << ", " << timespent << ", /t " << (timespent / (t + 0.));
}

int32_t main()
{
    fast();

    read(c);
    read(n, t);
    cost.resize(n);
    parents.resize(n);
    value.resize(n);
    children.resize(n);
    cnt.resize(n);

    rep(i, n)
    {
        read(cost[i]);
        read(value[i]);
        dread(int, k);
        parents[i].resize(k);
        rep(j, k) read(parents[i][j]);
        cnt[i] = parents[i].size();
        rep(j, k)
        {
            int p = parents[i][j];
            children[p].push_back(i);
        }
    }

    if (false) return 0;

    if (c == 1 || c == 2 || c == 3 || c == 4 || c == 8 || c == 7) greedybetter();
    if (c == 5) greedyfast();
    if (c == 6) solvegreedy();
    if (c == 9) solvelargetree();
    if (c == 10) solvereversetree();


#if _LOCAL
    verify();
#else


    cout << taken.size() << "\n";
    repe(node, taken) cout << node << " ";
#endif
    quit;
}
