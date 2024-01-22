// 3k from tree+2k from cycle
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

#if _MSC_VER > 0
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
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

vvi nodeindex;

struct UF
{
	vi par;
	vi size;
	UF(int n) : par(n), size(n, 1)
	{
		rep(i, n) par[i] = i;
	}
	int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		par[b] = a;
		size[a] += size[b];
	}
};

void dfs(int u, int p, vvi& treeadj, vi& color, vi& nodes)
{
	if (u != p)
	{
		color[u] ^= 1;
		nodes.push_back(u);
	}

	repe(e, treeadj[u])
	{
		if (e == p) continue;
		dfs(e, u, treeadj, color, nodes);
		nodes.push_back(u);
		color[u] ^= 1;
	}

	if (color[u] != 1 && u != p)
	{
		color[p] ^= 1;
		nodes.push_back(p);
		color[u] ^= 1;
		nodes.push_back(u);
	}
}

int sign(int x)
{
	if (x == 0) return 0;
	if (x > 0) return 1;
	return -1;
}

string getans(vi& nodes, vector<p2>& position)
{
	map<p2, string> difftodir;
	difftodir[p2(1, 0)] = 'v';
	difftodir[p2(-1, 0)] = '^';
	difftodir[p2(0, 1)] = '>';
	difftodir[p2(0, -1)] = '<';
	difftodir[p2(0, 0)] = "";
	string ans = "";
	rep(i, sz(nodes) - 1)
	{
		p2 curr = position[nodes[i]];
		p2 nextu = position[nodes[i + 1]];
		p2 diff = p2(sign(nextu.first - curr.first), sign(nextu.second - curr.second));
		ans += difftodir[diff];
	}
	return ans;
}

bool findcycle(int u, int p, vi& color, vvi& adj, vi& cycle)
{
	if (color[u] != -1)
	{
		if (color[u] != color[p]) return 0;
		cycle.push_back(u);
		return 1;
	}
	if (u == p) color[u] = 0;
	else color[u] = !color[p];
	repe(e, adj[u])
	{
		bool k = findcycle(e, u, color, adj, cycle);
		if (cycle.size())
		{
			k &= (cycle[0] != u);
			if (k) cycle.push_back(u);

			return k;
		}
	}
	return 0;
}

void dfs2(int u, int p, int d, vi& depth, vvi& treeadj)
{
	depth[u] = d;
	repe(e, treeadj[u]) if (e != p)dfs2(e, u, d + 1, depth, treeadj);
}

bool walkto(int u, int p, int t, vvi& treeadj, vi& color, vi& nodes)
{
	if (u != p)
	{
		nodes.push_back(u);
		color[u] ^= 1;
	}
	if (u == t) return 1;

	repe(e, treeadj[u])
	{
		if (e == p) continue;
		if (walkto(e, u, t, treeadj, color, nodes)) return 1;
	}

	if (u != p)
	{
		nodes.pop_back();
		color[u] ^= 1;
	}
	return 0;
}



signed main()
{
	fast();

	int n, m;
	cin >> n >> m;
	int r, c;
	r = c = -1;
	int retstart;
	cin >> retstart;
	vector<string> grid(n);
	rep(i, n) cin >> grid[i];
	nodeindex.resize(n, vector<int>(m));
	int ind = 0;
	vector<p2> position;
	rep(i, n) rep(j, m)
	{
		if (grid[i][j] == 'S') r = i, c = j, grid[i][j] = 'X';
	}
	rep(i, n) rep(j, m)
	{
		if (grid[i][j] == 'X') nodeindex[i][j] = ind++, position.emplace_back(i, j);
	}

	vvi edges(ind);
	vector<p2> edgelist;
	rep(i, n) rep(j, m)
	{
		if (grid[i][j] != 'X') continue;
		repe(dir, dirs)
		{
			p2 p = p2(i, j);
			p.first += dir.first;
			p.second += dir.second;
			while (p.first >= 0 && p.second >= 0 && p.first < n && p.second < m)
			{
				if (grid[p.first][p.second] == 'X')
				{
					edgelist.emplace_back(nodeindex[i][j], nodeindex[p.first][p.second]);
					edges[nodeindex[i][j]].push_back(nodeindex[p.first][p.second]);
					break;
				}
				p.first += dir.first;
				p.second += dir.second;
			}
		}
	}

	int qcnt = edges.size();
	UF uf(edges.size());
	vector<p2> treeedges;
	vvi treeadj(edges.size());
	repe(e, edgelist)
	{
		if (uf.find(e.first) != uf.find(e.second))
		{
			uf.merge(e.first, e.second);
			treeedges.emplace_back(e);
			treeadj[e.first].emplace_back(e.second);
			treeadj[e.second].emplace_back(e.first);
		}
	}
	if (uf.size[uf.find(0)] != sz(edges))
	{
		cout << "-1\n";
		return 0;
	}

	assert(r >= 0 && c >= 0);
	int start = nodeindex[r][c];
	auto getsol = [&](vi& color, vi& nodes)
	{

		int currp = start;

		nodes.push_back(currp);

		dfs(currp, currp, treeadj, color, nodes);

		assert(nodes.back() == start);

	};

	auto print = [&](vi& color, vi& nodes)
	{
		rep(i, qcnt) assert(color[i] == 1);
		string ans = getans(nodes, position);
		cout << ans.size() << "\n";
		cout << ans << "\n";
	};

	vi nodes;
	vi color(qcnt);
	getsol(color, nodes);
	if (color[start] == 0)
	{
		rep(i, qcnt) if (i != start)assert(color[i] == 1);
		if (retstart)
		{
			// try to change parity of root
			nodes.resize(0);
			color = vi(qcnt);

			vi depth(qcnt);
			dfs2(start, start, 0, depth, treeadj);

			vi coloring(qcnt, -1);
			vi cycle;
			findcycle(start, start, coloring, edges, cycle);

			bool bipartite = cycle.empty();
			if (bipartite && qcnt % 2 == 1)
			{
				cout << "-1\n";
				return 0;
			}

			assert(!bipartite);
			int best = 0;
			rep(i, sz(cycle)) if (depth[cycle[i]] < depth[cycle[best]])best = i;

			nodes.push_back(start);
			walkto(start, start, cycle[best], treeadj, color, nodes);

			int k = cycle.size() / 2;
			vi moves;
			rep(i, k)
			{
				moves.push_back(-1);
				moves.push_back(-1);
				moves.push_back(1);
				moves.push_back(-1);
			}
			moves.push_back(-1);
			int curr = best;


			repe(v, moves)
			{
				curr += v;
				curr += cycle.size();
				curr %= cycle.size();
				color[cycle[curr]] ^= 1;
				nodes.push_back(cycle[curr]);
			}


			walkto(cycle[best], cycle[best], start, treeadj, color, nodes);
			assert(color[start] == 1);
			rep(i, qcnt)if (i != start)assert(color[i] == 0);

			nodes.pop_back();

			getsol(color, nodes);
		}
		else
		{
			nodes.pop_back();
			color[start] = 1;
		}
	}
	print(color, nodes);

	return 0;
}
