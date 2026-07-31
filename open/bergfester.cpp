#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

const int maxn = 2e5 + 10;
int depth[maxn];
void dfs(int u, int p, vvi& adj)
{
    depth[u] = depth[p] + 1;

    repe(e, adj[u]) if (e != p) dfs(e, u, adj);
}

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - countl_zero((unsigned int)(b - a));
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vi time, path;
    vector<int> ret;
    RMQ<int> rmq;

    LCA(const vector<vi>& C, int root) : time(sz(C)), rmq((dfs(C, root, -1), ret)) {}
    void dfs(const vector<vi>& C, int v, int par) {
        time[v] = T++;
        for (int y : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }

    int lca(int a, int b) {
        if (a == -1) return b;
        if (b == -1) return a;
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    //dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};
LCA* g_lca = 0;


struct LCAtree {
    struct Node {
        int minTime;
        int maxTime;

        Node()
            : minTime(INT_MAX), maxTime(INT_MIN) {
        }
        Node(int v)
            : 
            minTime(g_lca->time[v]),
            maxTime(g_lca->time[v]) {
        }
        Node(int l, int r) : minTime(l), maxTime(r) {}
        bool empty() const { return minTime == INT_MAX; }
    };

    int n, N;
    vector<Node> tree;

    LCAtree(int size)
        : n(size)
    {
        N = 1;
        while (N < n) N <<= 1;
        tree.assign(2 * N, Node());
    }

    static Node combine(const Node& A, const Node& B) {
        return { min(A.minTime, B.minTime),max(A.maxTime,B.maxTime) };
    }

    void update(int i, int v) {
        i += N;
        tree[i] = Node(v);
        for (i >>= 1; i >= 1; i >>= 1)
            tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
    }

    int query(int l, int r) const {
        if (l > r) return -1;
        int L = l + N;
        int R = r + N + 1;
        Node resL, resR;
        while (L < R) {
            if (L & 1) resL = combine(resL, tree[L++]);
            if (R & 1) resR = combine(tree[--R], resR);
            L >>= 1; R >>= 1;
        }
        Node res = combine(resL, resR);
        if (res.empty()) return -1;
        //return g_lca->lca(res.minNode, res.maxNode);
        
        return g_lca->path[g_lca->rmq.query(res.minTime, res.maxTime)];
    }
};


struct MaxTree {
    typedef int T;
    static constexpr T unit = INT_MIN;
    T f(T a, T b) { return max(a, b); } // (any associative fn)
    vector<T> s; int n;
    MaxTree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) { // query [b, e)
        e++;
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    vi par(n);
    rep(i, n) cin >> par[i], par[i]--;
    int root = -1;
    rep(i, n) if (par[i] == i) root = i;
    assert(root != -1);

    vvi adj(n);
    rep(i, n) if (i != root)
    {
        adj[i].push_back(par[i]);
        adj[par[i]].push_back(i);
    }
    depth[root] = -1;
    dfs(root, root, adj);
    g_lca = new LCA(adj, root);

    vi who_lives(n, -1);
    vi which_house(m);
    rep(i, m)
    {
        int h;
        cin >> h;
        h--;
        which_house[i] = h;
        who_lives[h] = i;
    }
    
    MaxTree depmax(m);
    LCAtree lcatree(m);
    rep(i, m) depmax.update(i, depth[which_house[i]]);
    rep(i, m) lcatree.update(i, which_house[i]);

    auto swap_houses = [&](int a, int b)
    {
        swap(who_lives[a], who_lives[b]);
        if (who_lives[a] != -1)
        {
            int person = who_lives[a];
            which_house[person] = a;
            depmax.update(person, depth[which_house[person]]);
            lcatree.update(person, which_house[person]);
        }
        if (who_lives[b] != -1)
        {
            int person = who_lives[b];
            which_house[person] = b;
            depmax.update(person, depth[which_house[person]]);
            lcatree.update(person, which_house[person]);
        }
    };

    auto mod = [&](int ind)
    {
        ind %= m;
        if (ind < 0) ind += m;
        return ind;
    };

    auto range_max = [&](int l, int r, MaxTree& T) {
        if (l <= r) return T.query(l, r);
        return max(T.query(l, m - 1), T.query(0, r));
    };
    auto lca = [&](int l, int r, LCAtree& t) {
        if (l == r) return (int)which_house[l];
        return t.query(l, r);
    };
    auto range_lca = [&](int l, int r, LCAtree& T) {
        if (l <= r) return lca(l, r, T);
        return g_lca->lca(lca(l, m - 1, T), lca(0, r, T));
    };

    while (q--)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            int a, b;
            cin >> a >> b;
            a--; b--;
            swap_houses(a, b);
        }
        else
        {
            int p, r;
            cin >> p >> r;
            ll best = 0;
            p--;

            int radius = r;
            {
                int start = p;
                int lo = 0;
                int hi = m + 1;
                while (lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    int ridx = mod(start + mid - 1);
                    int md = range_max(start, ridx, depmax);
                    int h = range_lca(start, ridx, lcatree);
                    if (md - depth[h] > radius) {
                        hi = mid;
                    }
                    else {
                        lo = mid;
                    }
                }
                best = max(best, (ll)lo);
            }

            {
                int start = p;
                int lo = 0;
                int hi = m + 1;
                while (lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    int lidx = mod(start - mid + 1);
                    int ridx = start;
                    int md = range_max(lidx, ridx, depmax);
                    int h = range_lca(lidx, ridx, lcatree);
                    if (md - depth[h] > radius) {
                        hi = mid;
                    }
                    else {
                        lo = mid;
                    }
                }
                best = max(best, (ll)lo);
            }

            cout << best << '\n';
        }
    }

    return 0;
}
