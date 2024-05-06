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
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

vvi transpose(vvi arr)
{
	vvi ret(sz(arr[0]), vi(sz(arr)));
	rep(i, sz(arr[0])) rep(j, sz(arr)) ret[i][j] = arr[j][i];

	return ret;
}

void die()
{
	cout << "impossible";
	exit(0);
}

signed main()
{
	fast();

	int n, m;
	cin >> n >> m;
	vvi in(n, vi(m));
	bool t = 0;

	rep(i, n)
	{
		string r;
		cin >> r;
		rep(j, m) in[i][j] = r[j] - '0';
	}

	if (n > m)
	{
		swap(n, m);
		in = transpose(in);
		t = 1;
	}

	// n is smaller dimension

	vvi a(n, vi(m));
	vvi b(n, vi(m));
	vvi c(n, vi(m));
	if (n == 1)
	{
		if (m == 1)
		{
			if (in[0][0] == 1) die();
			else
			{
				a[0][0] = 1;
				b[0][0] = 1;
				c[0][0] = 1;
			}
		}
		else if (m == 2)
		{
			if (in[0][0] == 1 && in[0][1] == 1) die();
			{
				a[0][0] = 1;
				b[0][1] = 1;
				if (in[0][0] == 2) c[0][0] = 1;
				if (in[0][1] == 2) c[0][1] = 1;
			}
		}
		else
		{
			int num2interval = 0;
			rep(i, m) if (in[0][i] == 2 && (i == 0 || in[0][i - 1] == 1)) num2interval++;
			if (num2interval == 0)
			{
				rep(i, m - 2) a[0][i] = 1;
				b[0][m - 2] = 1;
				c[0][m - 1] = 1;
			}
			else if (num2interval == 1)
			{
				rep(i, m - 1) a[0][i] = 1;
				b[0][m - 1] = 1;
				rep(i, m) if (in[0][i] == 2) c[0][i] = 2;
			}
			else if (num2interval == 2)
			{
				rep(i, m)
				{
					if (i)
					{
						if (in[0][i] == 1 && in[0][i - 1] == 2) break;
					}
					a[0][i] = 1;
				}
				bool on = 0;
				rep(i, m)
				{
					if (in[0][i] == 2) on = 1;
					if (on) b[0][i] = 1;
				}

				for (int i = m - 1; i >= 0; i--)
				{
					if (in[0][i] == 2) c[0][i] = 1;
					if (i != m - 1 && in[0][i] == 1 && in[0][i + 1] == 2) break;
				}
			}
			else
			{
				die();
			}
		}
	}
	else if (n == 2)
	{
		a[0][0] = 1;
		a[1][0] = 1;
		repp(i, 1, m) b[0][i] = 1;
		repp(i, 1, m) c[1][i] = 1;
		if (in[0][0] == 2) b[0][0] = 1;
		if (in[1][0] == 2) b[1][0] = 1;
		repp(i, 1, m) if (in[0][i] == 2) c[0][i] = 1;
		repp(i, 1, m) if (in[1][i] == 2) b[1][i] = 1;
	}
	else if (n == 3)
	{
		a[0][0] = 1;
		a[1][0] = 1;
		a[2][0] = 1;
		repp(i, 1, m) b[0][i] = 1;
		repp(i, 1, m) b[2][i] = 1;
		b[1][1] = 1;
		repp(i, 2, m) c[1][i] = 1;
		rep(i, n) if (in[i][0] == 2) b[i][0] = 1;
		rep(i, n) if (in[i][1] == 2) a[i][1] = 1;
		rep(i, n)
		{
			repp(j, 2, m)
			{
				if (in[i][j] == 2)
				{
					if (b[i][j] == 0) b[i][j] = 1;
					else c[i][j] = 1;
				}
			}
		}
	}
	else
	{
		rep(i, n) a[i][0] = 1;
		vector<p2> dirs = { {1,0}, {0,1}, {-1,0}, {0,-1} };
		int cd = 3;
		p2 p = { 0,m - 1 };
		rep(_, n * m * 10)
		{
			b[p.first][p.second] = 1;
			p2 np = { p.first + dirs[cd % 4].first, p.second + dirs[cd % 4].second };
			if (np.first >= n || np.second >= m - 1 || np.first < 0 || np.second < 1)
			{
				cd++;
				continue;
			}
			bool good = 1;
			repe(dir, dirs)
			{
				if (dir == dirs[(cd + 2) % 4]) continue;
				p2 np2 = { np.first + dir.first,np.second + dir.second };
				if (np2.first >= n || np2.second >= m || np2.first < 0 || np2.second < 0) continue;
				if (b[np2.first][np2.second])
				{
					good = 0;
				}
			}
			if (good)
			{
				p = np;
			}
			else
			{
				cd++;
			}
		}

		rep(i, n)
		{
			repp(j, 1, m)
			{
				if (b[i][j] == 0) c[i][j] = 1;
			}
		}

		rep(i, n)
		{
			if (in[i][0] == 2) b[i][0] = 1;
			if (in[i][1] == 2) a[i][1] = 1;
			repp(j, 2, m)
			{
				if (in[i][j] == 2)
				{
					if (b[i][j] == 0) b[i][j] = 1;
					else c[i][j] = 1;
				}
			}
		}
	}

	if (t)
	{
		swap(n, m);
		a = transpose(a);
		b = transpose(b);
		c = transpose(c);
	}

	rep(i, n)
	{
		rep(j, m)
		{
			cout << (a[i][j] ? 'A' : '.');
		}
		cout << "\n";
	}
	cout << "\n";
	rep(i, n)
	{
		rep(j, m)
		{
			cout << (b[i][j] ? 'B' : '.');
		}
		cout << "\n";
	}
	cout << "\n"; rep(i, n)
	{
		rep(j, m)
		{
			cout << (c[i][j] ? 'C' : '.');
		}
		cout << "\n";
	}


	return 0;
}