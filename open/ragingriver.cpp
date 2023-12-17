#pragma GCC optimize("Ofast,inline,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")

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

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

#define _LOCAL _MSC_VER > 0
#if _LOCAL

#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
uint32_t ctz(uint32_t x) { return _tzcnt_u32(x); }
#else
#define popcount(x) __builtin_popcountll(x)
uint32_t ctz(uint32_t x) { return __builtin_ctzll(x); }

#if 0
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
inline void read(p2& a) { cin >> a.first >> a.second; }
#endif

#define quit cout << flush; _Exit(0);
void readinput() {} // Recursion base case
template<typename T, typename... Args> void readinput(T& arg, Args&... args) { read(arg); readinput(args...); }
#define dread(type, ...) type __VA_ARGS__; readinput(__VA_ARGS__);
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (T& u : v) read(u); return is; }
#define _ << " " <<

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

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)
ll binpow(ll a, ll b) { ll res = 1; while (b > 0) { if (b & 1) res = res * a; a = a * a; b >>= 1; } return res; }
ll binpow(ll a, ll b, ll m) { a %= m; long long res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } return res; } // For a < 2^31

template <typename T, typename U> inline void operator+=(pair<T, U>& l, const pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator+(const pair<T, U> l, const pair<T, U> r) { return { l.first + r.first, l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator-(const pair<T, U> l, const pair<T, U> r) { return { l.first - r.first, l.second - r.second }; }
template <typename T, typename U> inline pair<T, U> operator*(const pair<T, U> l, const int m) { return { l.first * m, l.second * m }; }
vector<string> split(string s, string d) { size_t k = 0, n, e = d.length(); string t; vector<string> r; while ((n = s.find(d, k)) != string::npos) { t = s.substr(k, n - k); k = n + e; r.push_back(t); } r.push_back(s.substr(k)); return r; }

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

// Modified network simplex for ease of use https://gist.github.com/brunodccarvalho/fb9f2b47d7f8469d209506b336013473

// Network simplex for mincost circulation/flow with supply/demand at nodes
// Supports edge lower bounds, negative costs and negative cost cycles
// Flow type should be large enough to hold node supply/excess and sum of all capacities
// Cost type should be large enough to hold costs and potentials (usually >=64 bits)
// CostSum type should be large enough to hold inner product of capacities and costs
// Expected runtime: O(VE) for positive costs, O(E²) for negative costs too
// Usage:
//   network_simplex<int, long> netw(V);
//   for (edges...) { netw.add(u, v, lower, upper, unit_cost); }
//   for (nodes...) { netw.set_supply(u, supply); }
//   auto max_flow = netw.mincost_flow();           or mincost_circulation()
//   auto min_cost = netw.get_circulation_cost();
template <typename Flow = int64_t, typename Cost = int64_t>
struct network_simplex {
    explicit network_simplex(int V) : V(V), node(V + 1) {}

    int add(int u, int v, Flow lower, Flow upper, Cost cost) {
        assert(0 <= u && u < V && 0 <= v && v < V&& lower <= upper);
        return edge.push_back({ {u, v}, lower, upper, cost }), E++;
    }
    int add_node() { return node.emplace_back(), V++; }

    void add_supply(int u, Flow supply) { node[u].supply += supply; }
    void add_demand(int u, Flow demand) { node[u].supply -= demand; }
    void set_supply(int u, Flow supply) { node[u].supply = supply; }

    void update_edge(int e, Flow lower, Flow upper, Cost cost) {
        edge[e].lower = lower, edge[e].upper = upper, edge[e].cost = cost;
    }

    auto get_supply(int u) const { return node[u].supply; }
    auto get_potential(int u) const { return node[u].pi; }
    auto get_flow(int e) const { return edge[e].flow; }

    auto reduced_cost(int e) const {
        auto [u, v] = edge[e].node;
        return edge[e].cost + node[u].pi - node[v].pi;
    }

    // Get excess for every vertex: excess(u) = flow(out of u) - flow(into u)
    auto get_excesses() const {
        vector<Flow> excess(V);
        for (int e = 0; e < E; e++) {
            auto [u, v] = edge[e].node;
            excess[u] += edge[e].flow;
            excess[v] -= edge[e].flow;
        }
        return excess;
    }

    template <typename CostSum = int64_t>
    auto get_circulation_cost() const {
        CostSum sum = 0;
        for (int e = 0; e < E; e++) {
            sum += edge[e].flow * CostSum(edge[e].cost);
        }
        return sum;
    }

    void verify() const {
        for (int e = 0; e < E; e++) {
            assert(edge[e].lower <= edge[e].flow && edge[e].flow <= edge[e].upper);
            assert(edge[e].flow == edge[e].lower || reduced_cost(e) <= 0);
            assert(edge[e].flow == edge[e].upper || reduced_cost(e) >= 0);
        }
    }

    // Run as circulation: find a feasible circulation and fail if one doesn't exist.
    // Also checks for zero supply sum. Usually this is not what you want.
    bool mincost_circulation() {
        static constexpr bool INFEASIBLE = false, OPTIMAL = true;

        // Assert supply sum is zero
        Flow sum_supply = 0;
        for (int u = 0; u < V; u++) {
            sum_supply += node[u].supply;
        }
        if (sum_supply != 0) {
            return INFEASIBLE;
        }

        run();

        // Assert zero flow through artificial edges
        for (int e = E; e < E + V; e++) {
            if (edge[e].flow != 0) {
                edge.resize(E);
                return INFEASIBLE;
            }
        }
        edge.resize(E);
        return OPTIMAL;
    }

    // Returns: {maxflow, cost}
    // Run as mincost maxflow: ignore extra artificial flow and non-zero supply sum
    // You must set supply at the source(s) and demand at the sink(s) (inf for maxflow)
    // The excess at a supply/source node u will be in the range [0,supply[u]].
    // The excess at a demand/sink   node u will be in the range [supply[u],0].
    p2 mincost_flow(int source, int sink) {
        add_supply(source, inf);
        add_demand(sink, inf);
        run();

        Flow maxflow = 0;
        for (int e = E; e < E + V; e++) {
            if (edge[e].node[1] == V) {
                maxflow += edge[e].upper - edge[e].flow;
            }
        }

        edge.resize(E);
        return { maxflow,get_circulation_cost() };
    }

    // Implementation
    enum ArcState : int8_t { STATE_UPPER = -1, STATE_TREE = 0, STATE_LOWER = 1 };
    auto signed_reduced_cost(int e) const { return edge[e].state * reduced_cost(e); }

    struct int_lists {
        int L, N;
        vector<int> next, prev;

        // L: lists are [0...L), N: integers are [0...N)
        explicit int_lists(int L = 0, int N = 0) { assign(L, N); }

        int ret(int l) const { return l + N; }
        int head(int l) const { return next[ret(l)]; }
        int tail(int l) const { return prev[ret(l)]; }

        void push_front(int l, int n) { meet(ret(l), n, head(l)); }
        void push_back(int l, int n) { meet(tail(l), n, ret(l)); }
        void erase(int n) { meet(prev[n], next[n]); }

        void clear() {
            iota(begin(next) + N, end(next), N);
            iota(begin(prev) + N, end(prev), N);
        }
        void assign(int L, int N) {
            this->L = L, this->N = N;
            next.resize(N + L), prev.resize(N + L), clear();
        }

    private:
        inline void meet(int u, int v) { next[u] = v, prev[v] = u; }
        inline void meet(int u, int v, int w) { meet(u, v), meet(v, w); }
    };

    struct Node {
        int parent, pred;
        Flow supply;
        Cost pi;
    };
    struct Edge {
        int node[2];
        Flow lower, upper;
        Cost cost;
        Flow flow = 0;
        ArcState state = STATE_LOWER;
    };
    int V, E = 0;
    vector<Node> node;
    vector<Edge> edge;
    int_lists children;

    int next_arc = 0, block_size = 0;
    vector<int> bfs, perm; // scratchpad for bfs and upwards walk / random permutation

    void run() {
        // Remove non-zero lower bounds and compute artif_cost as sum of all costs
        Cost artif_cost = 1;
        for (int e = 0; e < E; e++) {
            auto [u, v] = edge[e].node;
            edge[e].flow = 0;
            edge[e].state = STATE_LOWER;
            edge[e].upper -= edge[e].lower;
            node[u].supply -= edge[e].lower;
            node[v].supply += edge[e].lower;
            artif_cost += edge[e].cost < 0 ? -edge[e].cost : edge[e].cost;
        }

        edge.resize(E + V);
        bfs.resize(V + 1);
        children.assign(V + 1, V + 1);

        // Add root<->node artificial edges with initial supply for feasible flow
        int root = V;
        node[root] = { -1, -1, 0, 0 };

        for (int u = 0, e = E; u < V; u++, e++) {
            node[u].parent = root, node[u].pred = e;
            children.push_back(root, u);
            auto supply = node[u].supply;
            if (supply >= 0) {
                node[u].pi = -artif_cost;
                edge[e] = { {u, root}, 0, supply, artif_cost, supply, STATE_TREE };
            }
            else {
                node[u].pi = artif_cost;
                edge[e] = { {root, u}, 0, -supply, artif_cost, -supply, STATE_TREE };
            }
        }

        // We want to, hopefully, find a pivot edge in O(sqrt(E))
        // This should be <E to check different sets of edges in each select()
        // Otherwise we are vulnerable to simplex killers
        block_size = max(int(ceil(sqrt(E + V))), min(5LL, V + 1));
        next_arc = 0;

        // Random permutation of the edges; helps with wide graphs and killer test cases
        static mt19937 rng(random_device{}());
        perm.resize(E + V);
        iota(begin(perm), end(perm), 0);
        shuffle(begin(perm), end(perm), rng);

        // Pivot until we're done
        int in_arc = select_pivot_edge();
        while (in_arc != -1) {
            pivot(in_arc);
            in_arc = select_pivot_edge();
        }

        // Restore flows and supplies
        for (int e = 0; e < E; e++) {
            auto [u, v] = edge[e].node;
            edge[e].flow += edge[e].lower;
            edge[e].upper += edge[e].lower;
            node[u].supply += edge[e].lower;
            node[v].supply -= edge[e].lower;
        }
    }

    int select_pivot_edge() {
        // lemon-like block search, check block_size edges and pick the best one
        Cost minimum = 0;
        int in_arc = -1;
        int count = block_size, seen_edges = E + V;
        for (int& e = next_arc; seen_edges-- > 0; e = e + 1 == E + V ? 0 : e + 1) {
            int x = perm[e];
            if (minimum > signed_reduced_cost(x)) {
                minimum = signed_reduced_cost(x);
                in_arc = x;
            }
            if (--count == 0 && minimum < 0) {
                break;
            }
            else if (count == 0) {
                count = block_size;
            }
        }
        return in_arc;
    }

    void pivot(int in_arc) {
        // Find join node (lca of u_in and v_in)
        auto [u_in, v_in] = edge[in_arc].node;
        int a = u_in, b = v_in;
        while (a != b) {
            a = node[a].parent == -1 ? v_in : node[a].parent;
            b = node[b].parent == -1 ? u_in : node[b].parent;
        }
        int join = a;

        // Orient edge so that we add flow to source->target
        int source = edge[in_arc].state == STATE_LOWER ? u_in : v_in;
        int target = edge[in_arc].state == STATE_LOWER ? v_in : u_in;

        enum OutArcSide { SAME_EDGE, SOURCE_SIDE, TARGET_SIDE };
        Flow flow_delta = edge[in_arc].upper;
        OutArcSide side = SAME_EDGE;
        int u_out = -1;

        // Go up the cycle from source to the join node
        for (int u = source; u != join && flow_delta; u = node[u].parent) {
            int e = node[u].pred;
            bool edge_down = u == edge[e].node[1];
            Flow d = edge_down ? edge[e].upper - edge[e].flow : edge[e].flow;
            if (flow_delta > d) {
                flow_delta = d;
                u_out = u;
                side = SOURCE_SIDE;
            }
        }

        // Go up the cycle from target to the join node
        for (int u = target; u != join && (flow_delta || side != TARGET_SIDE);
            u = node[u].parent) {
            int e = node[u].pred;
            bool edge_up = u == edge[e].node[0];
            Flow d = edge_up ? edge[e].upper - edge[e].flow : edge[e].flow;
            if (flow_delta >= d) {
                flow_delta = d;
                u_out = u;
                side = TARGET_SIDE;
            }
        }

        // Augment along the cycle
        if (flow_delta) {
            auto delta = edge[in_arc].state * flow_delta;
            edge[in_arc].flow += delta;
            for (int u = edge[in_arc].node[0]; u != join; u = node[u].parent) {
                int e = node[u].pred;
                edge[e].flow += u == edge[e].node[0] ? -delta : +delta;
            }
            for (int u = edge[in_arc].node[1]; u != join; u = node[u].parent) {
                int e = node[u].pred;
                edge[e].flow += u == edge[e].node[0] ? +delta : -delta;
            }
        }

        if (side == SAME_EDGE) {
            edge[in_arc].state = ArcState(-edge[in_arc].state);
            return;
        }

        // Replace out_arc with in_arc in the spanning tree
        int out_arc = node[u_out].pred;
        edge[in_arc].state = STATE_TREE;
        edge[out_arc].state = edge[out_arc].flow ? STATE_UPPER : STATE_LOWER;

        // Put u_in on the same side as u_out
        u_in = side == SOURCE_SIDE ? source : target;
        v_in = side == SOURCE_SIDE ? target : source;

        // Walk up from u_in to u_out, then fix parent/pred/child pointers backwards
        int i = 0, S = 0;
        for (int u = u_in; u != u_out; u = node[u].parent) {
            bfs[S++] = u;
        }
        for (i = S - 1; i >= 0; i--) {
            int u = bfs[i], p = node[u].parent;
            children.erase(p);
            children.push_back(u, p);
            node[p].parent = u;
            node[p].pred = node[u].pred;
        }
        children.erase(u_in);
        children.push_back(v_in, u_in);
        node[u_in].parent = v_in;
        node[u_in].pred = in_arc;

        // Adjust potentials in the subtree of u_in (pi_delta is not 0)
        Cost current_pi = reduced_cost(in_arc);
        Cost pi_delta = u_in == edge[in_arc].node[0] ? -current_pi : +current_pi;

        bfs[0] = u_in;
        for (i = 0, S = 1; i < S; i++) {
            int u = bfs[i];
            node[u].pi += pi_delta;
            for (int v = children.head(u); v != children.ret(u); v = children.next[v]) {
                bfs[S++] = v;
            }
        }
    }
};

int32_t main()
{
    fast();
#if 0 && _LOCAL
    ifstream instream("C:\\users\\matis\\source\\repos\\comp_prog\\x64\\debug\\in.txt");
    cin.rdbuf(instream.rdbuf());
#endif

    dread(int, p, n, m);
    int source = n;
    int sink = n + 1;
    network_simplex flow(n + 3);
    rep(i, m)
    {
        dread(int, a, b);
        if (a == -2) a = source;
        if (b == -2) b = source;
        if (a == -1) a = sink;
        if (b == -1) b = sink;
        flow.add(a, b, 0, 1, 1);
        flow.add(b, a, 0, 1, 1);
    }
    flow.add(n + 2, source, 0, p, 0);

    p2 res = flow.mincost_flow(n + 2, sink);
    if (res.first == p)
    {
        cout << res.second;
    }
    else cout << (p - res.first) << " people left behind";

    quit;
}