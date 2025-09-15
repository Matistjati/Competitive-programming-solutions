#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

int n, m;
vector<string> grid;
vvi vis;
int visver = 10;
ll cost(int dx, int dy)
{
	ll tiles = 0;
	visver++;
	rep(i, n)
	{
		rep(j, m)
		{
			if (grid[i][j] == '.') continue;
			if (vis[i][j] == visver) continue;
			int num_options = 0;
			int diagsize = 0;
			int y = i;
			int x = j;
			while (y<n&&x>=0&&x<m&&grid[y][x]=='#')
			{
				diagsize++;
				vis[y][x] = visver;
				y += dy;
				x += dx;
			}
			if (diagsize == 1) return inf;
			tiles += (diagsize +1) / 2;
		}
	}
	return tiles;
}


int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> m;
	grid.resize(n);
	repe(v, grid) cin >> v;
	vis.resize(n, vi(m));

	ll dotcount = 0;
	rep(i, n) rep(j, m) dotcount += grid[i][j] == '#';


	ll ans = dotcount;
	rep(dy, n+1)
	{
		repp(dx, -m, m+1)
		{
			if (dx == 0 && dy == 0) continue;
			ll c = cost(dx, dy);
			ans = min(ans, c);
		}
	}
	cout << ans << '\n';


	return 0;
}
