#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2")
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

auto start = chrono::high_resolution_clock::now();

int n;

const int MAX_N = 5e5+5;
struct Node {
    int max,lazy;
} segtree[1<<20];

int subtree_sz[MAX_N];

void dfs1(int u, vector<vector<int>>& adj) {
    subtree_sz[u]=1;

    repe(e,adj[u]) {
        dfs1(e,adj);
        subtree_sz[u] += subtree_sz[e];
    }
}

int timer = 0;
int tin[MAX_N];
int path_parent[MAX_N], path_begin[MAX_N];
void dfs2(int u, int path_parent_node, int path_begin_node, vector<vector<int>>& adj) {
    tin[u] = timer++;
    path_parent[tin[u]] = path_parent_node;
    path_begin[tin[u]] = path_begin_node;
    if (adj[u].empty()) return;

    int heaviest = *max_element(all(adj[u]), [&](int a, int b) {
        return subtree_sz[a]<subtree_sz[b];
    });

    dfs2(heaviest,path_parent_node,path_begin_node, adj);

    repe(e,adj[u]) {
        if (e==heaviest) continue; 
        dfs2(e,tin[u],timer,adj);
    }
}

int n_tree=1;
void path_add(int ql, int qr, int v) {
    int l0 = ql + n_tree, r0 = qr + n_tree;
    
    for (int l = l0, r = r0 + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            segtree[l].max += v;
            segtree[l].lazy += v;
            l++;
        }
        if (r & 1) {
            --r;
            segtree[r].max += v;
            segtree[r].lazy += v;
        }
    }
    
    for (l0 >>= 1, r0 >>= 1; l0 > 0; l0 >>= 1, r0 >>= 1) {
        segtree[l0].max = max(segtree[l0 << 1].max, segtree[l0 << 1 | 1].max) + segtree[l0].lazy;
        segtree[r0].max = max(segtree[r0 << 1].max, segtree[r0 << 1 | 1].max) + segtree[r0].lazy;
    }
}

void increment_ancestors(int u, int v) { 
    while (u != -1) {
        __builtin_prefetch(&path_parent[u],0,1);
        __builtin_prefetch(&path_parent[path_parent[u]],0,1);
        __builtin_prefetch(&path_parent[path_parent[path_parent[u]]],0,1);
        path_add(path_begin[u], u, v);
        u = path_parent[u];
    }
}

pair<int, int> rightmost(int x, int l, int r, int cutoff, int acc_lazy = 0) { 
    if (l == r) {
        int actual_max = segtree[x].max + acc_lazy;
        return {l, actual_max};
    }
    int mid = (l + r) / 2;

    int next_acc = acc_lazy + segtree[x].lazy; 

    if (segtree[x * 2 + 1].max + next_acc > cutoff) {
        return rightmost(x * 2 + 1, mid + 1, r, cutoff, next_acc);
    }
    return rightmost(x * 2, l, mid, cutoff, next_acc);
}

void build() {
    for (int i = n - 1; i >= 0; --i) {
        segtree[n_tree + i].max+=1;
        int p = (i == path_begin[i]) ? path_parent[i] : i - 1;
        if (p != -1) {
            segtree[n_tree + p].max += segtree[n_tree + i].max;
        }
    }

    for (int i = n_tree - 1; i > 0; --i) {
        segtree[i].max = max(segtree[i * 2].max, segtree[i * 2 + 1].max);
    }
}

int max_value() {
    return segtree[1].max;
}

vector<pair<int,int>> updates;
int solve(int max_size) {
    int ret = 0;
    updates.clear();
    while (max_value() > max_size) {
        ret++;
        auto [pivot,val] = rightmost(1,0,n_tree-1,max_size);
        updates.emplace_back(pivot,val);
        increment_ancestors(pivot,-val);
    }
    for (auto [u,v] : updates) {
        increment_ancestors(u,v);
    }
    
    return ret;
}

template<class F, class G, class T>
void rec(int from, int to, F& f, G& g, int& i, T& p, T q) {
    if (p == q) return;
    if (from == to) {
        g(i, to, p);
        i = to; p = q;
    } else {
        int mid = (from + to) >> 1;
        int v = (n / (mid+1) <= q) ? q : f(mid);
        rec(from, mid, f, g, i, p, v);
        rec(mid+1, to, f, g, i, p, q);
    }
}
template<class F, class G>
void constantIntervals(int from, int to, F f, G g) {
    if (to <= from) return;
    int i = from; auto p = f(i), q = f(to-1);
    rec(from, to-1, f, g, i, p, q);
    g(i, to, q);
}

alignas(64) int par[MAX_N];
alignas(64) int tsize[MAX_N];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    path_parent[0]=-1;
    memset(segtree,0,sizeof(segtree));

    cin >> n;
    while (n_tree<n) n_tree*=2;

    vector<vector<int>> adj(n);
    par[0]=0;
    rep(i,n-1) {
        int p;
        cin >> p;
        p--;
        par[i+1]=p;
        adj[p].push_back(i+1);
    }

    dfs1(0,adj);
    dfs2(0,-1,0,adj);
    build();
    cerr << "Build time: " << (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count()) << '\n';
    start = chrono::high_resolution_clock::now();


    // int evals = 0;
    auto min_edges = [&](int max_size) {
        memset(tsize,0,sizeof(tsize));
        int cost = 0;

        #pragma GCC unroll 8
        for (int i = n-1; i >= 0; i--) {
            if (tsize[i]+1>max_size) {
                cost++;
            }
            else {
                tsize[par[i]] += tsize[i]+1;
            }
        }

        return cost;
    };

    int prev = n;
    vector<int> ans(n, 1);
    

    int last_i;
    repp(i,1,400) {
        int val = min_edges(i);
        repp(k,val,prev) ans[k] = i;
        prev = val;
        last_i = i;
    }
    cerr << "Phase 1 time: " << (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count()) << '\n';
    start = chrono::high_resolution_clock::now();

    constantIntervals(last_i, n, solve, [&](int lo, int hi, int val) {
        repp(k,val,prev) ans[k] = lo;
        prev = val;
    });
    repp(i,1,n) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
