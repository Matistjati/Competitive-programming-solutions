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

struct delta
{
	int dx, dy, dz;
};
struct edge
{
	int to;
	delta d;
};

signed main()
{
	fast();

	int n, m;
	cin >> n >> m;
	vector<vector<edge>> edges(n);
	rep(i, m)
	{
		int a, b, dx, dy, dz;
		cin >> a >> b >> dx >> dy >> dz;
		a--; b--;

		edges[a].push_back(edge({ b,delta({dx,dy,dz}) }));
		edges[b].push_back(edge({ a,delta({-dx,-dy,-dz}) }));
	}
	vector<delta> deltas(n, delta({-inf,-1,-1}));
	vi vis(n);
	rep(i, n)
	{
		if (vis[i]) continue;
		
		queue<int> q;
		q.emplace(i);
		deltas[i] = delta({ 0,0,0 });
		while (q.size())
		{
			int u = q.front();
			q.pop();

			if (vis[u]) continue;
			vis[u] = 1;

			delta cd = deltas[u];
			assert(cd.dx != -inf);
			repe(edg, edges[u])
			{
				int e=edg.to;
				delta d=edg.d;
				delta edgeres = delta({ cd.dx + d.dx,cd.dy + d.dy,cd.dz + d.dz });
				if (deltas[e].dx!=-inf)
				{
					delta t = deltas[e];
					assert(t.dx != -inf);
					if (edgeres.dx != t.dx || edgeres.dy != t.dy || edgeres.dz != t.dz)
					{
						cout << "Neibb";
						return 0;
					}
				}
				else
				{
					deltas[e] = edgeres;
					q.emplace(e);
				}
			}
		}
	}
	cout << "Jebb";

	return 0;
}
