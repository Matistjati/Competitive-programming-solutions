#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int BIG = int(2e9);

signed main()
{
	fast();

	vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
	int n, m, t;
	cin >> n >> m >> t;
	vector<p2> start(n);
	vector<p2> blocked(m);
	rep(i, n) cin >> start[i].first >> start[i].second;
	rep(i, m) cin >> blocked[i].first >> blocked[i].second;
	sort(all(blocked));

	set<int> xc;
	set<int> yc;
	xc.insert(BIG);
	xc.insert(-BIG);
	yc.insert(BIG);
	yc.insert(-BIG);
	repe(p, start) xc.insert(p.first), yc.insert(p.second);
	repe(p, blocked) xc.insert(p.first), yc.insert(p.second);

	map<p2, vi> whichrectangles;

	auto getp = [](set<int>& nums)
		{
			vector<p2> ret;
			int prev = -BIG;
			repe(u, nums)
			{
				if (prev+1 <= u-1) ret.push_back(p2(prev+1, u-1));
				if (u!=-BIG) ret.push_back(p2(u,u));

				prev = u;
			}
			return ret;
		};

	vector<p2> xp = getp(xc);
	vector<p2> yp = getp(yc);

	vector<p2> positions;
	map<p2, int> coordind;
	vector<vector<p2>> rects;

	repe(x, xp)
	{
		repe(y, yp)
		{
			rects.push_back({});
			vi X = { x.first,x.second };
			vi Y = { y.first,y.second };

			repe(x1, X) repe(y1, Y)
			{
				p2 p = p2(x1, y1);
				if (coordind.find(p)== coordind.end())
				{
					positions.push_back(p);
					coordind[p] = sz(coordind);
				}
				rects.back().emplace_back(x1, y1);
			}
		}
	}
	vector<vector<p2>> adj(sz(positions));


	auto isblocked = [&](p2 p)
		{
			return binary_search(all(blocked), p);
		};

	auto addedge = [&](p2 a, p2 b)
		{
			int d = abs(a.first - b.first) + abs(a.second - b.second);
			int ai = coordind[a];
			int bi = coordind[b];
			adj[ai].emplace_back(bi, d);
			adj[bi].emplace_back(ai, d);
		};

	repe(rect, rects)
	{
		rep(i, 4)
		{
			addedge(rect[i], rect[(i + 1) % 4]);
		}
	}

	map<int, vi> row;
	map<int, vi> col;
	repe(p, positions) row[p.first].push_back(p.second), col[p.second].push_back(p.first);
	repe(r, row) sort(all(r.second));
	repe(c, col) sort(all(c.second));

	repe(p, positions)
	{
		if (isblocked(p)) continue;
		auto it = upper_bound(all(row[p.first]), p.second);
		if (it!=row[p.first].end() && !isblocked(p2(p.first,*it)))
		{
			addedge(p, p2(p.first, *it));
		}
		it = lower_bound(all(row[p.first]), p.second);
		if (it!=row[p.first].begin() && !isblocked(p2(p.first,*prev(it))))
		{
			addedge(p, p2(p.first, *prev(it)));
		}

		it = upper_bound(all(col[p.second]), p.first);
		if (it != col[p.second].end() && !isblocked(p2(*it, p.second)))
		{
			addedge(p, p2(*it, p.second));
		}
		it = lower_bound(all(col[p.second]), p.first);
		if (it != col[p.second].begin() && !isblocked(p2(*prev(it), p.second)))
		{
			addedge(p, p2(*prev(it), p.second));
		}
	}

	priority_queue<p2> pq;
	vi dist(sz(positions), inf);
	repe(s, start)
	{
		int ind = coordind[s];
		pq.emplace(0, ind);
		dist[ind] = 0;
	}

	while (sz(pq))
	{
		int d, u;
		tie(d, u) = pq.top();
		pq.pop();

		d = -d;
		if (d > dist[u]) continue;

		repe(e, adj[u])
		{
			int nd = d + e.second;
			if (nd<dist[e.first])
			{
				dist[e.first] = nd;
				pq.emplace(-nd, e.first);
			}
		}
	}

	auto pd = [](p2 a, p2 b)
		{
			return abs(a.first - b.first) + abs(a.second - b.second);
		};
	int ans = 0;
	rep(i, sz(rects))
	{
		int d1 = t - dist[coordind[rects[i][0]]];
		int d2 = t - dist[coordind[rects[i][1]]];
		int d3 = t - dist[coordind[rects[i][2]]];
		int d4 = t - dist[coordind[rects[i][3]]];
		// tl tr bl br
		int width = rects[i][1].second - rects[i][0].second;
		int height = rects[i][2].first - rects[i][0].first;

		// big bounding box. at most one corner will have gas
		if (width>int(4e5)&&height>int(4e5))
		{
			int m = max(d1, max(d2, max(d3, d4)));
			if (m >= 0) ans += (m+1) * (m + 2) / 2;
		}
		else
		{
			// rotate 90 degrees
			if (width>height)
			{
				p2 tl = rects[i][0];
				rects[i][1] = p2(tl.first, tl.second + height);
				rects[i][2] = p2(tl.first+width, tl.second);
				rects[i][3] = p2(tl.first+width, tl.second+height);
				vi oldd = {d1, d2, d3, d4};
				d1 = oldd[2];
				d2 = oldd[0];
				d3 = oldd[3];
				d4 = oldd[1];
				width = rects[i][1].second - rects[i][0].second;
				height = rects[i][2].first - rects[i][0].first;
			}
			repp(j, rects[i][0].second, rects[i][1].second + 1)
			{
				p2 p = p2(rects[i][0].first, j);
				p2 pt = p2(rects[i][2].first, j);
				int botgas = max(d1 - pd(p, rects[i][0]), d2 - pd(p, rects[i][1]));
				int topgas = max(d3 - pd(pt, rects[i][2]), d4 - pd(pt, rects[i][3]));
				int downer = p.first + max(0LL, botgas);
				int upper = pt.first - max(0LL, topgas);

				if (botgas >= 0 && topgas >= 0)
				{
					if (downer >= upper) ans += height+1;
					else ans += topgas + botgas+2;
				}
				else if (botgas >= 0)
				{
					ans += botgas+1;
				}
				else if (topgas >= 0)
				{
					ans += topgas+1;
				}
			}
		}
	}
	cout << ans;

	return 0;
}
