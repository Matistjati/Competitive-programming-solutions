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
#define per(i, high) for (int i = high-1; i >= 0; i--)

#define _LOCAL _MSC_VER
#if _LOCAL > 0
#define deb __debugbreak();
#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
#define clz(x) _lzcnt_u32(x)
#else
#define clz(x) __builtin_clz(x)
#define deb ;
#define popcount(x) __builtin_popcountll(x)
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#ifdef _DEBUG
#define debassert(expr) if(!(expr)) deb;
#else
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
//vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0}, {0,0} };

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]


struct PushRelabel {
	struct Edge {
		int dest, back;
		ll f, c;
	};
	vector<vector<Edge>> g;
	vector<ll> ec;
	vector<Edge*> cur;
	vector<vi> hs; vi H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}

	void addEdge(int s, int t, ll cap, ll rcap = 0) {
		if (s == t) return;
		g[s].push_back({ t, sz(g[t]), 0, cap });
		g[t].push_back({ s, sz(g[s]) - 1, 0, rcap });
	}

	void addFlow(Edge& e, ll f) {
		Edge& back = g[e.dest][e.back];
		if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
	ll calc(int s, int t) {
		int v = sz(g); H[s] = v; ec[t] = 1;
		vi co(2 * v); co[0] = v - 1;
		repp(i, 0, v) cur[i] = g[i].data();
		for (Edge& e : g[s]) addFlow(e, e.c);

		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ec[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0)  // discharge u
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = 1e9;
					for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest] + 1)
						H[u] = H[e.dest] + 1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						repp(i, 0, v) if (hi < H[i] && H[i] < v)
						--co[H[i]], H[i] = v + 1;
					hi = H[u];
				}
				else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
					addFlow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
		}
	}
	bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

signed main()
{
	fast();

	int n, k, h;
	cin >> n >> k >> h;
	int numnodes = n * n * (h + 1) * 2 + 2;

	PushRelabel flow(numnodes);
	const int s = numnodes - 1;
	const int t = numnodes - 2;

	vvi grid(n, vi(n));
	rep(i, n) rep(j, n) cin >> grid[i][j];

	vector<p2> cows;
	rep(i, k)
	{
		int a, b;
		cin >> a >> b;
		cows.emplace_back(a, b);
	}

	auto getpos = [&](p2 p)
	{
		return p.first + p.second * n;
	};

	vi heights(h + 1);
	heights[0] = 0;
	rep(i, h)
	{
		cin >> heights[i + 1];
	}


	auto addcow = [&](int base, int target, p2 p)
	{
		repe(dir, dirs)
		{
			p2 np = p2(p.first + dir.first, p.second + dir.second);
			if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= n) continue;
			flow.addEdge(base + getpos(p), target + getpos(np), 1);
		}
	};

	auto adddirect = [&](int base, int target, p2 p)
	{
		flow.addEdge(base + getpos(p), target + getpos(p), 1);
	};

	repe(cow, cows)
	{
		flow.addEdge(s, getpos(cow), 1);
	}


	int gridsz = n * n;
	int base = 0;
	rep(hour, h)
	{
		rep(i, n)
		{
			rep(j, n)
			{
				addcow(base, base + gridsz, p2(i, j));
			}
		}

		base += gridsz;
		rep(i, n)
		{
			rep(j, n)
			{
				if (grid[i][j] > heights[hour + 1]) adddirect(base, base + gridsz, p2(i, j));
			}
		}
		base += gridsz;
	}
	rep(i, n)
	{
		rep(j, n)
		{
			flow.addEdge(base + getpos(p2(i, j)), t, 1);
		}
	}
	cout << flow.calc(s, t);

	return 0;
}