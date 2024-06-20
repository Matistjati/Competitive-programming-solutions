#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e10);

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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


pair<double, vi> hungarian(const vector<vector<double>>& a) {
	if (a.empty()) return { 0, {} };
	int n = sz(a) + 1, m = sz(a[0]) + 1;
	vector<double> u(n), v(m), p(m);
	vi ans(n - 1);
	repp(i, 1, n) {
		p[0] = i;
		int j0 = 0; // add "dummy" worker 0
		vector<double> dist(m, 1e14); vi pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			double i0 = p[j0], j1, delta = 1e14;
			repp(j, 1, m) if (!done[j]) {
				auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			repp(j, 0, m) {
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0) { // update alternating path
			int j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	repp(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
	return { -v[0], ans }; // min cost
}

signed main()
{
	fast();

	int n, s, t, q;
	cin >> n >> s >> t >> q;
	q *= q;

	vector<vector<double>> cost(t, vector<double>(s, inf));
	vector<p2> pos;
	vi height;
	rep(i, n)
	{
		int x, y, h;
		cin >> x >> y >> h;
		pos.emplace_back(x, y);
		height.push_back(h);
	}
	vi istown(n);
	vi is_spring(n);
	vi spring_ind(n);
	int ind = 0;
	rep(i, s)
	{
		int spr_ind;
		cin >> spr_ind;
		spr_ind--;
		is_spring[spr_ind] = 1;
		spring_ind[spr_ind] = ind++;
	}
	rep(i, t)
	{
		int town_ind;
		cin >> town_ind;
		town_ind--;
		istown[town_ind] = 1;
	}

	ind = 0;
	rep(i, n)
	{
		if (istown[i])
		{
			priority_queue<pair<double, int>> pq;
			vi vis(n);
			pq.emplace(0, i);
			while (pq.size())
			{
				double d;
				int u;
				tie(d, u) = pq.top();
				pq.pop();

				if (vis[u]) continue;
				vis[u] = 1;
				if (is_spring[u]) cost[ind][spring_ind[u]] = -d;

				rep(j, n)
				{
					if (height[u] >= height[j]) continue;
					double dist = pow(pos[u].first - pos[j].first, 2) + pow(pos[u].second-pos[j].second, 2)+pow(height[u]-height[j],2);
					if (dist > q) continue;
					pq.emplace(d - sqrt(dist), j);
				}
			}
			ind++;
		}
	}
	double c = hungarian(cost).first;
	if (c >= inf) cout << "IMPOSSIBLE";
	else cout << fixed << setprecision(15) << c;

	return 0;
}
