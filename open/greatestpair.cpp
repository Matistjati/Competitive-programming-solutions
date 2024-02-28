#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#define _LOCAL _DEBUG
#if _LOCAL
#define clz(x) __lzcnt(x)
#define assert(x) if (!(x)) __debugbreak()
#else
#define clz(x) __builtin_clz(x)
#endif



template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            repp(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;

    LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(vector<vi>& C, int v, int par) {
        time[v] = T++;
        for (int y : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }

    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    //dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

const int MAX_PR = 5e5 + 20;
vi smallestfactor(MAX_PR);

// Find smallest factor of all numbers in range[0, hi)
void smallestFactorSieve(int hi = MAX_PR)
{
    rep(i, hi) smallestfactor[i] = i;
    for (int i = 0; i < hi; i += 2) smallestfactor[i] = 2;

    repp(i, 3, min(hi + 0., ceil(sqrt(hi)) + 10))
    {
        if (smallestfactor[i] == i)
        {
            for (size_t j = i * i; j < hi; j += i)
            {
                if (smallestfactor[j] == j) smallestfactor[j] = i;
            }
        }
    }
}
using ull = unsigned long long;

// Factor n in log(n) time
vector<ull> GetFactors(int n)
{
    vector<ull> factors;
    int k = n;
    while (k != 1 && k != 0)
    {
        factors.emplace_back(smallestfactor[k]);
        k /= smallestfactor[k];
    }
    return factors;
}
void setDivisors(ull n, ull i, vector<ull>& divisors, vector<pair<ull, ull>>& factors) {
    ull j, x, k;
    for (j = i; j < factors.size(); j++) {
        x = factors[j].first * n;
        for (k = 0; k < factors[j].second; k++) {
            divisors.push_back(x);
            setDivisors(x, j + 1, divisors, factors);
            x *= factors[j].first;
        }
    }
}
// Get all factor from a list of primes
vector<ull> getDivisors(vector<ull> primes)
{
    unordered_map<ull, ull> primeCount;
    repe(prime, primes) primeCount[prime]++;
    vector<pair<ull, ull>> factorCount;
    repe(p, primeCount) factorCount.emplace_back(p);
    vector<ull> ret;
    setDivisors(1, 0, ret, factorCount);
    ret.push_back(1);
    return ret;
}

const int maxn = int(1e5);
int depth[maxn];
int closest[maxn];
void dfs(int u, int p, int d, vector<vector<p2>>& adj)
{
    depth[u] = d;

    repe(e, adj[u]) if (e.first != p) dfs(e.first, u, d + e.second, adj);
}

signed main()
{
    fast();

    smallestFactorSieve();

    auto dist = [&](int a, int b, LCA& lca)
    {
        return depth[a] + depth[b] - 2 * depth[lca.lca(a, b)];
    };

    int n;
    while ((cin >> n) && n)
    {
        vvi adj(n);
        vector<vector<p2>> edges(n);
        vi label(n);
        rep(i, n) cin >> label[i];
        rep(i, n)closest[i] = inf;
        rep(i, n - 1)
        {
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
            edges[a].emplace_back(b, c);
            edges[b].emplace_back(a, c);
        }
        dfs(0, 0, 0, edges);

        LCA lca(adj);
        map<int, vi> who;
        rep(i, n)
        {
            repe(div, getDivisors(GetFactors(label[i])))
            {
                who[div].push_back(i);
            }
        }


        int ans = 0;
        repe(w, who)
        {
            vi& nodes = w.second;
            int root = 0;
            int best = -1;
            int furthest = -1;
            repe(u, nodes)
            {
                if (dist(root, u, lca) > furthest)
                {
                    furthest = dist(root, u, lca);
                    best = u;
                }
            }
            root = best;
            furthest = -1;
            repe(u, nodes)
            {
                furthest = max(furthest, dist(root, u, lca));
            }

            ans = max(ans, w.first * furthest);
        }
        cout << ans << "\n";
    }


    return 0;
}
