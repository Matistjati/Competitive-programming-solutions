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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#define ctz(x) _tzcnt_u64(x)
#define clz(x) _lzcnt_u32(x)
#else
#define ctz(x) __builtin_ctz(x)
#define clz(x) __builtin_clz(x)
#endif

struct node
{
	int x,y,v, active=0;
};

const int blocksize = 500;
const int maxn = int(2e5);
const int numblocks = (maxn + blocksize - 1) / blocksize;
int prefxmax[numblocks][blocksize];
int prefymin[numblocks][blocksize];
int sufvmin[numblocks][blocksize];
int mostdom[numblocks];

signed main()
{
    fast();

	rep(i, numblocks) rep(j, blocksize) prefxmax[i][j] = -1;
	rep(i, numblocks) rep(j, blocksize) prefymin[i][j] = inf;
	rep(i, numblocks) rep(j, blocksize) sufvmin[i][j] = inf;
	rep(i, numblocks) mostdom[i] = -1;

	int n;
	cin >> n;
	
	map<int, vi> cols;
	
	vector<p2> coords;
	rep(i, n)
	{
		int x, y;
		cin >> x >> y;
		coords.emplace_back(x, y);
	}
	set<p2> unique(all(coords));
	coords = vector<p2>(all(unique));
	n = sz(coords);
	sort(all(coords), [](p2 a, p2 b)
		{
			if (a.second != b.second) return a.second > b.second;
			return a.first < b.first;
		});

	rep(i, n)
	{
		int x, y;
		tie(x, y) = coords[i];
		cols[x].push_back(i);
	}
	repe(col, cols) sort(all(col.second));
	

	vector<node> hull(n);
	rep(i, n) hull[i].x = coords[i].first, hull[i].y = coords[i].second;

	auto dominates = [](int x1, int y1, int x2, int y2)
		{
			return x1 > x2 && y1 > y2;
		};

	int relevant[blocksize];
	memset(relevant, 0, sizeof(relevant));
	int ver = 10;
	auto insert = [&](int ind, int v)
		{
			hull[ind].active = 1;
			hull[ind].v = v;

			int block = ind / blocksize;
			int base = block * blocksize;

			int yv = inf;
			rep(i, blocksize)
			{
				if (base + i < n && hull[base + i].active)
				{
					yv = min(yv, hull[base + i].y);
				}
				prefymin[block][i] = yv;
			}
			
			int xv = -1;
			rep(i, blocksize)
			{
				if (base + i < n && hull[base + i].active)
				{
					xv = max(xv, hull[base + i].x);
				}
				prefxmax[block][i] = xv;
			}

			ver++;
			p2 start = p2(-1, inf);
			rep(i, blocksize)
			{
				
				if (base + i < n)
				{
					node& h = hull[base + i];
					if (h.active && !dominates(start.first, start.second, h.x, h.y))
					{
						relevant[i] = ver;
						start = p2(h.x, h.y);
						mostdom[block] = i;
					}
				}
			}

			int sufmin = inf;
			for (int i = blocksize - 1; i >= 0; i--)
			{
				if (base + i < n && relevant[i] == ver)
				{
					sufmin = min(sufmin, 1 + hull[base+i].v);
				}
				sufvmin[block][i] = sufmin;
			}
		};




	auto query = [&](int x, int y)
		{
			int cost = inf;

			int first_dominated = -1;
			int b = -1;
			rep(block, numblocks)
			{
				if (prefymin[block][blocksize-1]<y)
				{
					b = block;
					break;
				}
			}
			if (b!=-1)
			{
				int base = b * blocksize;
				rep(i, blocksize)
				{
					if (base + i >= n) break;
					if (hull[base+i].active && hull[base+i].y < y)
					{
						first_dominated = i + base;
						break;
					}
				}
			}

			if (first_dominated!=-1)
			{
				int curr = first_dominated;
				cost = min(cost, 1 + hull[first_dominated].v);
				int block = first_dominated / blocksize;
				repp(i, first_dominated + 1, min(n, (block+1)*blocksize))
				{
					node& h2 = hull[i];
					if (!h2.active) continue;
					if (!dominates(hull[curr].x, hull[curr].y, h2.x, h2.y))
					{
						cost = min(cost, 1 + hull[i].v);
						curr = i;
					}
				}

				repp(b, block + 1, numblocks)
				{
					int base = b * blocksize;

					int lo = -1;
					int hi = blocksize;
					while (lo + 1 < hi)
					{
						int mid = (lo + hi) / 2;
						if (prefxmax[b][mid] < hull[curr].x)
						{
							lo = mid;
						}
						else hi = mid;
					
					}
					
					if (hi != blocksize) cost = min(cost, sufvmin[b][hi]);

					if (mostdom[b] != -1)
					{
						node& h = hull[base+mostdom[b]];
						if (!dominates(hull[curr].x,hull[curr].y, h.x, h.y))
						{
							curr = base + mostdom[b];
						}
						
					}
				}

			}
			
			return cost;
		};

	repe(col, cols)
	{
		int x = col.first;
		vector<p2> newpts;
		repe(i, col.second)
		{
			int y = coords[i].second;
			int cost = query(x, y);

			if (cost == inf) cost = 1;

			newpts.emplace_back(i, cost);
		}
		
		repe(u, newpts)
		{
			insert(u.first, u.second);
		}
	}
	
	cout << query(inf,inf)-1;

    return 0;
}
