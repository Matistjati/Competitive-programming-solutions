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
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

int n;
vi unsafe;
vector<p2> pos;
vvi adjmine;
vector<bitset<5000>> seeagain;
void place(int ind, vi& placement, vi& minecnt)
{
	if (ind == sz(adjmine))
	{
		bool good = 1;
		repe(m, minecnt) good &= m == 1;
		if (good) repe(p, placement) unsafe[p] = 1;
		else
		{
			assert(1);
		}
		return;
	}

	bool canplace = 1;
	repe(e, adjmine[ind]) if (minecnt[e]) canplace = 0;

	if (canplace)
	{
		bool anylarge = 0;
		repe(e, adjmine[ind]) minecnt[e]++, anylarge |= minecnt[e] > 1;
		placement.push_back(ind);
		if (!anylarge) place(ind + 1, placement, minecnt);

		repe(e, adjmine[ind]) minecnt[e]--;
		placement.pop_back();
	}

	bool maynotplace = 1;
	if (ind != sz(adjmine) - 1)
	{
		repe(e, adjmine[ind])
		{
			bool anygood = seeagain[ind][e];
			if (!anygood && minecnt[e] == 0) maynotplace = 1;
		}

	}

	if (maynotplace) place(ind + 1, placement, minecnt);
}


signed main()
{
	fast();

	int n;
	cin >> n;
	int t = n;
	if (n == 0)
	{
		cout << 0;
		return 0;
	}
	n -= 2;
	if (n % 3 == 0)
	{
		cout << 0;
		return 0;
	}
	else if (n % 3 == 1)
	{
		vi diffs;
		int k = n / 3;
		rep(i, 3)
		{
			rep(j, k) diffs.push_back(3);
			diffs.push_back(2);
			diffs.push_back(2);
		}
		rep(i, k) diffs.push_back(3);
		diffs.insert(diffs.begin(), 2);
		vi ans = { 1 };
		repe(d, diffs) ans.push_back(ans.back() + d);
		cout << sz(ans) << "\n";
		repe(v, ans) cout << v << " ";
	}
	else if (n % 3 == 2)
	{
		vi diffs;
		int k = n / 3;
		rep(i, 3)
		{
			rep(j, k + 1) diffs.push_back(3);
			diffs.push_back(1);
			diffs.push_back(1);
		}
		rep(j, k + 1) diffs.push_back(3);
		diffs.insert(begin(diffs), 1);
		vi ans;
		ans.push_back(1);
		repe(d, diffs) ans.push_back(ans.back() + d);
		cout << sz(ans) << "\n";
		repe(d, ans) cout << d << " ";
	}
	return 0;

	// bruteforce used for pattern-matching
	n = t;
	adjmine.resize(n * 4 + 4);
	unsafe.resize(n * 4 + 4);
	n += 2;
	vvi grid(n, vi(n, -1));
	vector<p2> dirs = { {-1,0},{0,1},{1,0},{0,-1} };

	p2 pos = { n - 2, 1 };
	int ind = 0;
	int dirind = 0;
	while (true)
	{
		grid[pos.first][pos.second] = ind++;
		if (n == 3) break;
		if (pos.first + dirs[dirind].first < 1 || pos.first + dirs[dirind].first >= n - 1)
		{
			dirind++;
		}
		if (pos.second + dirs[dirind].second < 1 || pos.second + dirs[dirind].second >= n - 1)
		{
			dirind++;
		}
		pos = p2(pos.first + dirs[dirind].first, pos.second + dirs[dirind].second);
		if (pos == p2(n - 2, 1)) break;
	}
	vi minecnt(ind);

	pos = { n - 1, 0 };
	ind = 0;
	dirind = 0;
	vector<p2> dirs2 = { {-1,0},{0,1},{1,0},{0,-1}, {1,1},{1,-1},{-1,1},{-1,-1} };
	while (true)
	{
		repe(dir, dirs2)
		{
			p2 np = p2(pos.first + dir.first, pos.second + dir.second);
			if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= n) continue;
			if (grid[np.first][np.second] != -1) adjmine[ind].push_back(grid[np.first][np.second]);
		}
		if (pos.first + dirs[dirind].first < 0 || pos.first + dirs[dirind].first >= n)
		{
			dirind++;
		}
		if (pos.second + dirs[dirind].second < 0 || pos.second + dirs[dirind].second >= n)
		{
			dirind++;
		}
		pos = p2(pos.first + dirs[dirind].first, pos.second + dirs[dirind].second);
		ind++;
		if (pos == p2(n - 1, 0)) break;
	}

	seeagain.resize(sz(adjmine));
	bitset<5000> seen;
	for (int i = sz(adjmine) - 1; i >= 0; i--)
	{
		seeagain[i] = seen;
		repe(e, adjmine[i]) seen[e] = 1;
	}

	vi placement;
	place(0, placement, minecnt);

	int ans = 0;
	repe(v, unsafe) ans += v == 0;
	cout << ans << "\n";

	rep(i, sz(unsafe))
	{
		if (!unsafe[i])
		{
			cout << i + 1 << " ";
		}
	}

	return 0;
}
