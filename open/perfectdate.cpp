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

struct poly
{
	int squaresum, linearsum;
	int numvariables;
	int sum;
	poly() : squaresum(0), linearsum(0), numvariables(0), sum(0) {}

	void increment(int val)
	{
		sum += val * val * val * numvariables;
		sum += 3 * val * val * linearsum;
		sum += 3 * val * squaresum;
		squaresum += 2 * linearsum * val + numvariables * val * val;
		linearsum += val * numvariables;
	}
};

poly merge(poly a, poly b)
{
	poly ret;
	ret.linearsum = a.linearsum + b.linearsum;
	ret.squaresum = a.squaresum + b.squaresum;
	ret.sum = a.sum + b.sum;
	ret.numvariables = a.numvariables + b.numvariables;
	return ret;
}

namespace reroot {
	const auto exclusive = [](const auto& a, const auto& base, const auto& merge_into, int vertex) {
		int n = (int)a.size();
		using Aggregate = std::decay_t<decltype(base)>;
		std::vector<Aggregate> b(n, base);
		for (int bit = (int)std::__lg(n); bit >= 0; --bit) {
			for (int i = n - 1; i >= 0; --i) b[i] = b[i >> 1];
			int sz = n - (n & !bit);
			for (int i = 0; i < sz; ++i) {
				int index = (i >> bit) ^ 1;
				b[index] = merge_into(b[index], a[i], vertex, i);
			}
		}
		return b;
	};
	// MergeInto : Aggregate * Value * Vertex(int) * EdgeIndex(int) -> Aggregate
	// Base : Vertex(int) -> Aggregate
	// FinalizeMerge : Aggregate * Vertex(int) * EdgeIndex(int) -> Value
	const auto rerooter = [](const auto& g, const auto& base, const auto& merge_into, const auto& finalize_merge) {
		int n = (int)g.size();
		using Aggregate = std::decay_t<decltype(base(0))>;
		using Value = std::decay_t<decltype(finalize_merge(base(0), 0, 0))>;
		std::vector<Value> root_dp(n), dp(n);
		std::vector<std::vector<Value>> edge_dp(n), redge_dp(n);

		std::vector<int> bfs, parent(n);
		bfs.reserve(n);
		bfs.push_back(0);
		for (int i = 0; i < n; ++i) {
			int u = bfs[i];
			for (auto v : g[u]) {
				if (parent[u] == v) continue;
				parent[v] = u;
				bfs.push_back(v);
			}
		}

		for (int i = n - 1; i >= 0; --i) {
			int u = bfs[i];
			int p_edge_index = -1;
			Aggregate aggregate = base(u);
			for (int edge_index = 0; edge_index < (int)g[u].size(); ++edge_index) {
				int v = g[u][edge_index];
				if (parent[u] == v) {
					p_edge_index = edge_index;
					continue;
				}
				aggregate = merge_into(aggregate, dp[v], u, edge_index);
			}
			dp[u] = finalize_merge(aggregate, u, p_edge_index);
		}

		for (auto u : bfs) {
			dp[parent[u]] = dp[u];
			edge_dp[u].reserve(g[u].size());
			for (auto v : g[u]) edge_dp[u].push_back(dp[v]);
			auto dp_exclusive = exclusive(edge_dp[u], base(u), merge_into, u);
			redge_dp[u].reserve(g[u].size());
			for (int i = 0; i < (int)dp_exclusive.size(); ++i) redge_dp[u].push_back(finalize_merge(dp_exclusive[i], u, i));
			root_dp[u] = finalize_merge(n > 1 ? merge_into(dp_exclusive[0], edge_dp[u][0], u, 0) : base(u), u, -1);
			for (int i = 0; i < (int)g[u].size(); ++i) {
				dp[g[u][i]] = redge_dp[u][i];
			}
		}

		return std::make_tuple(std::move(root_dp), std::move(edge_dp), std::move(redge_dp));
	};
}  // namespace reroot

poly dfs(int u, int p, vvp2& edges)
{
	poly ret;
	ret.numvariables = 1;

	repe(e, edges[u])
	{
		if (e.first == p) continue;
		poly r = dfs(e.first, u, edges);
		r.increment(e.second);
		ret = merge(ret, r);
	}
	return ret;
}

int32_t main()
{
	fast();

#if 0 && _LOCAL
	ifstream instream("C:\\users\\matis\\source\\repos\\comp_prog\\x64\\debug\\in.txt");
	cin.rdbuf(instream.rdbuf());
#endif

	/*poly p;
	p.numvariables = 1;
	p.increment(1);
	cout << p.sum << "\n";
	p.numvariables++;
	p.increment(1);
	cout << p.sum;*/

	dread(int, n);
	vvi edges(n);
	vvi edgeweight(n);
	vp3 edgelist(n);
	rep(i, n - 1)
	{
		dread(int, a, b, w);
		a--; b--;
		edges[a].emplace_back(b);
		edges[b].emplace_back(a);
		edgeweight[a].push_back(w);
		edgeweight[b].push_back(w);
	}

	using Aggregate = poly;
	using Value = poly;

	auto base = [](int vertex) -> Aggregate {
		poly p;
		p.numvariables = 1;
		return p;
	};
	auto merge_into = [&](Aggregate vertex_dp, Value neighbor_dp, int vertex, int edge_index) -> Aggregate {
		neighbor_dp.increment(edgeweight[vertex][edge_index]);
		return merge(vertex_dp, neighbor_dp);
	};
	auto finalize_merge = [&](Aggregate vertex_dp, int vertex, int edge_index) -> Value {
		return vertex_dp;
	};

	auto [reroot_result, edge_dp, redge_dp] = reroot::rerooter(edges, base, merge_into, finalize_merge);

	int ans = inf;
	repe(v, reroot_result) ans = min(ans, v.sum);
	cout << ans * 2;


	quit;
}