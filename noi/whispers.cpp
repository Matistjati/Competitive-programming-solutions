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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define __builtin_clz __lzcnt
#define assert(x) if (!(x)) __debugbreak()
#endif

bool dfs(int u, vi& vis, vi& btoa, vvi& edges)
{
	if (btoa[u] == -1) return 1;
	if (vis[u]) return 0;
	vis[u] = 1;

	int a = btoa[u];
	repe(e, edges[a])
	{
		if (dfs(e,vis,btoa,edges))
		{
			btoa[e] = a;
			return 1;
		}
	}
	return 0;
}

int matching_size(vvi edges, int n)
{
	vi btoa(n, -1);
	vi vis(n);

	int nummatched = 0;
	rep(j, n)
	{
		rep(k, n) vis[k] = 0;
		repe(e, edges[j])
		{
			if (dfs(e, vis, btoa, edges))
			{
				btoa[e] = j;
				nummatched++;
				break;
			}
		}
	}
	return nummatched;
}

vi getviable(int n, int m, vvi edges, int a, bool up)
{
	vi ret(n * m);
	
	vi good(n);
	int start = up ? 0 : n * (m - 1);
	good[a-start] = 1;

	rep(i, m - 1)
	{
		int nextg = start + (up ? n : -n);

		rep(j, n) if (good[j]) ret[start + j] = 1;

		vi nextgood(n);

		rep(j, n)
		{
			if (!good[j]) continue;

			repe(e, edges[start+j])
			{
				if (nextgood[e - nextg]) continue;
				vvi localgraph(n);
				rep(k, n)
				{
					if (k == j) continue;
					repe(e2, edges[start + k]) if(e2!=e) localgraph[k].push_back(e2 - nextg);
				}

				if (matching_size(localgraph, n)==n-1)
				{
					nextgood[e - nextg] = 1;
				}
			}
		}

		good = nextgood;
		start = nextg;
	}
	rep(j, n) if (good[j]) ret[start + j] = 1;

	return ret;
}

signed main()
{
	fast();

	int n, m, a, b;
	cin >> n >> m >> a >> b;
	vvi graphup(n * (m-1));
	vvi graphdown(n * m);
	rep(i, n)
	{
		rep(j, m-1)
		{
			int deg;
			cin >> deg;
			rep(k, deg)
			{
				int b;
				cin >> b;
				graphup[j + i * (m-1)].push_back(b);
				graphdown[b].push_back(j + i * (m - 1));
			}
		}
	}

	vi l = getviable(n, m, graphup, a, 1);
	vi r = getviable(n, m, graphdown, b, 0);

	int ans = 0;
	rep(i, sz(l)) ans += l[i] && r[i];
	cout << ans << "\n";
	rep(i, sz(l))
	{
		if (l[i] && r[i]) cout << i << "\n";
	}

	return 0;
}
