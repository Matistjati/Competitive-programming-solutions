#pragma GCC optimize("Ofast")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include <immintrin.h>

#define dbg(...)


using namespace std;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define sz(c) ((int)c.size())

typedef unsigned long long ull;

struct Pipe {
  int u, v, a, b;

  Pipe(int u, int v, int a, int b) : u(u), v(v), a(a), b(b) {}

  friend std::ostream& operator<<(std::ostream& os, const Pipe& pipe) {
    os << "Pipe(" << pipe.u << ", " << pipe.v << ", " << pipe.a << ", "
       << pipe.b << ")";
    return os;
  }
};

auto Start = chrono::high_resolution_clock::now();
void rst() {
  Start = chrono::high_resolution_clock::now();
}
int gttm() {
  return chrono::duration_cast<chrono::milliseconds>(
             chrono::high_resolution_clock::now() - Start
  )
      .count();
}

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  rst();

  int n, m, q;
  cin >> n >> m >> q;

  vector<Pipe> pipes;
  vvpi adj(n);
  vvpi adj2(n);

  rep(i, m) {
    int u, v, a, b;
    cin >> u >> v >> a >> b;
    u--, v--, a--, b--;

    adj[u].emplace_back(v, sz(pipes));
    adj[v].emplace_back(u, sz(pipes));

    adj2[u].emplace_back(v, a);
    adj2[v].emplace_back(u, b);

    pipes.emplace_back(u, v, a, b);
  }

  dbg(gttm());
  rst();

  int num_bcc = 0;
  vi bcc_id(m, -1);

  {
    vi num(n), low(n);
    int time = 0;
    stack<int> st;

    function<void(int, int)> dfs;
    dfs = [&](int u, int e) {
      num[u] = low[u] = ++time;
      int c = 0;

      for (auto [v, ve] : adj[u]) {
        if (ve == e)
          continue;
        if (num[v] == 0) {
          c++;
          st.push(ve);
          dfs(v, ve);

          low[u] = min(low[u], low[v]);

          if ((e == -1 && c > 1) || (e != -1 && low[v] >= num[u])) {
            while (!st.empty()) {
              int edge = st.top();
              st.pop();

              bcc_id[edge] = num_bcc;
              if (edge == ve)
                break;
            }
            num_bcc++;
          }
        } else if (num[v] < num[u]) {
          st.push(ve);
          low[u] = min(low[u], num[v]);
        }
      }
    };

    for (int u = 0; u < n; u++) {
      if (num[u] == 0) {
        dfs(u, -1);
        if (sz(st)) {
          while (!st.empty()) {
            int edge = st.top();
            st.pop();

            bcc_id[edge] = num_bcc;
          }
          num_bcc++;
        }
      }
    }
  }

  dbg(gttm());
  rst();

  // dbg(pipes);
  // dbg(bcc_id);

  unordered_map<ll, int> trans;
  trans.max_load_factor(0.25);
  trans.reserve(1 << 19);
  auto hashp = [](int a, int b) -> ll {
    return (static_cast<ll>(a) << 20) + b;
  };
  auto get_ind = [&](int a, int b) {
    ll x = hashp(a, b);
    return trans.emplace(x, sz(trans)).first->second;
  };

  vvi ratg(4 * (m + 1));
  // vvi gtar(6 * m);

  // int maxu = -1;
  auto add_edge = [&](int a, int b, int c, int d) {
    int u = get_ind(a, b);
    int v = get_ind(c, d);
    // dbg(u, v);
    ratg[u].push_back(v);
    // maxu = max(maxu, u);
    // gtar[v].push_back(u);
  };

  vi transp(n, -1);

  {
    int l = n;
    for (int u = 0; u < n; u++) {
      transp[u] = get_ind(l, u);
      for (auto [v, _] : adj[u])
        add_edge(v, u, l, u);
      l++;
    }

    for (int u = 0; u < n; u++) {
      for (auto [v, e] : adj2[u])
        add_edge(u, v, v, e);
    }

    for (int u = 0; u < n; u++) {
      unordered_map<int, vi> g;
      for (auto [v, e] : adj[u])
        g[bcc_id[e]].push_back(v);

      for (auto gg : g) {
        if (sz(gg.second) <= 1)
          continue;
        for (auto x : gg.second) {
          add_edge(x, u, l, u);
          add_edge(l, u, x, u);
        }
        l++;
      }
    }
  }

  dbg(sz(trans));

  ratg.resize(sz(trans));

  dbg(gttm());
  rst();

  // for (auto i : ratg)
  // dbg(i);
  // dbg(ratg);

  vvi span(n);
  vi par(n);
  vi tin(n), tout(n);
  int l = __bit_width(n);
  vvi up(n, vi(l + 1));
  {
    {
      vi vis(n);
      function<void(int)> dfs;
      dfs = [&](int u) {
        for (auto [v, _] : adj[u]) {
          if (vis[v])
            continue;
          span[u].push_back(v);
          span[v].push_back(u);
          vis[v] = 1;
          dfs(v);
        }
      };
      vis[0] = 1;
      dfs(0);
    }

    dbg(gttm());
    rst();

    // for (auto i : span)
    // dbg(i);
    // dbg(span);

    int time = 0;
    function<void(int, int)> dfs;
    dfs = [&](int u, int p) {
      par[u] = p;
      tin[u] = ++time;
      up[u][0] = p;
      for (int i = 1; i <= l; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
      }

      for (auto v : span[u]) {
        if (v == p)
          continue;
        dfs(v, u);
      }
      tout[u] = ++time;
    };
    dfs(0, 0);
  }

  dbg(gttm());
  rst();

  // dbg(up, par);

  auto is_ancestor = [&](int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  };

  auto get_besides = [&](int u, int v) {
    if (is_ancestor(u, v)) {
      int vc = v;

      for (int i = l; i >= 0; i--) {
        if (!is_ancestor(up[v][i], u)) {
          v = up[v][i];
        }
      }

      // dbg(u, vc, v);
      return v;
    }

    // dbg(u, v, par[u]);
    return par[u];
  };

  vvi cond;
  vi roots(sz(ratg));

  {
    vvi comps;
    int root = 0;

    vi num(sz(ratg), -1), low(sz(ratg));
    vi vis(sz(ratg));
    stack<int> st;

    int time = 0;
    function<void(int)> scc;
    scc = [&](int u) {
      low[u] = num[u] = time++;

      st.push(u);
      vis[u] = 1;

      for (auto v : ratg[u]) {
        if (num[v] == -1)
          scc(v);

        if (vis[v])
          low[u] = min(low[u], low[v]);
      }

      if (low[u] == num[u]) {
        comps.push_back({});
        while (1) {
          int v = st.top();
          st.pop();
          vis[v] = 0;
          comps.back().push_back(v);
          roots[v] = root;
          if (u == v)
            break;
        }
        root++;
      }
    };

    for (int i = 0; i < sz(ratg); i++)
      if (num[i] == -1)
        scc(i);

    assert(sz(comps) == root);
    cond.resize(sz(comps));
    for (int u = 0; u < sz(ratg); u++) {
      for (auto v : ratg[u]) {
        if (roots[u] == roots[v])
          continue;
        cond[roots[u]].push_back(roots[v]);
      }
    }
  }

  dbg(gttm());
  rst();

  // for (auto i : roots)
  // dbg(i);
  // dbg(cond, roots);

  dbg(sz(cond));

  vi order;
  {
    vi vis(sz(cond));
    function<void(int)> dfs;
    dfs = [&](int u) {
      vis[u] = 1;

      for (auto v : cond[u]) {
        if (!vis[v])
          dfs(v);
      }
      order.push_back(u);
    };
    for (int i = 0; i < sz(cond); i++)
      if (!vis[i])
        dfs(i);
  }

  static const int SIZE = 1 << 14;
  using bs = bitset<SIZE>;
  using bsv = array<unsigned ll,256>;
  vector<bsv> reach(sz(cond));

  auto get_part = [&](int round) {
    for (auto u : order) {
      {
        ull* curr = (ull*)&reach[u];
        memset(curr, 0, 256*8);
        if (SIZE * round <= u && u < SIZE * (round + 1))
            curr[(u%SIZE)/64] |= 1ull<<(u%64);
      }

      __m256i* targets = (__m256i*)&reach[u][0];
      int k = 0;
      for(; k+2 <= sz(cond[u]); k+=2) {
        __m256i* v1 = (__m256i*)&reach[cond[u][k]][0];
        __m256i* v2 = (__m256i*)&reach[cond[u][k+1]][0];
        for (int i = 0; i < 64; i++) {
            __m256i other1 = _mm256_loadu_si256(&v1[i]);
            __m256i other2 = _mm256_loadu_si256(&v2[i]);
            __m256i target = _mm256_loadu_si256(&targets[i]);
            target = _mm256_or_si256(target, other1);
            target = _mm256_or_si256(target, other2);
            _mm256_storeu_si256(&targets[i], target);
        }
      }
      for(; k+1 <= sz(cond[u]); k+=1) {
        __m256i* v1 = (__m256i*)&reach[cond[u][k]][0];
        for (int i = 0; i < 64; i++) {
            __m256i other1 = _mm256_loadu_si256(&v1[i]);
            __m256i target = _mm256_loadu_si256(&targets[i]);
            target = _mm256_or_si256(target, other1);
            _mm256_storeu_si256(&targets[i], target);
        }
      }
    }
  };

  dbg(gttm());
  rst();

  vector<vector<tuple<int, int, int, int>>> queries(
      (sz(cond) + SIZE - 1) / SIZE
  );

  for (int i = 0; i < q; i++) {
    int s, r, t;
    cin >> s >> r >> t;
    s--, r--, t--;

    int quer = roots[transp[t]];

    queries[quer / SIZE].emplace_back(s, r, t, i);
  }

  vi ans(q);

  dbg(gttm());
  rst();
  for (int round = 0; round < sz(queries); round++) {
    // rst();
    if (sz(queries[round]) == 0)
      continue;

    // dbg(gttm());
    get_part(round);
    // dbg(gttm());

    for (auto [s, r, t, i] : queries[round]) {
      s = get_besides(r, s);

      // dbg(s, r, t);
      int ed = roots[get_ind(s, r)];

      // dbg(rated);

      int quer = roots[transp[t]];
      int pos = (reach[ed][(quer % SIZE)/64] >> (quer%64)) & 1;
      ans[i] = pos;
    }
  }

  dbg(gttm());
  rst();

  for (auto i : ans)
    cout << i << '\n';

  for (int u = 0; u < n; u++) {
    for (auto [v, _] : adj[u]) {
      // dbg(u, v, get_ind(u, v));
    }
  }
}
