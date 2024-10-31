#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
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

// way overcomplicated
// naive bitset solution: for each side and match, create a bitset
// each player will or the bitsets of opposing teams for each match
// too slow. instead, we will group matches in groups of 8
// for each group, calculate the result of every 2^8 left/right match oring
// then, we gain a factor of 8 for the naive algorithm. now it's fast enough
typedef bitset<int(4e4)> bset;
signed main()
{
	fast();

	int n, m;
	cin >> n >> m;

	vector<bset> leftside(m);
	vector<bset> rightside(m);

	vvi whichside(n);
	rep(i, m)
	{
		bset l;
		rep(_, n / 2)
		{
			int v;
			cin >> v;
			whichside[v - 1].push_back(1);
			l[v - 1] = 1;
		}
		leftside[i] = l;
		bset r;
		rep(_, n / 2)
		{
			int v;
			cin >> v;
			whichside[v - 1].push_back(0);
			r[v - 1] = 1;
		}
		rightside[i] = r;
	}




	const int howmany = 8;
	vector<vector<bset>> precomp;
	int offset = 0;
	int howmanyc = howmany;
	while (offset < m)
	{
		if (offset + howmanyc >= m)
		{
			howmanyc = m - offset;
		}
		vector<bset> pre(1 << howmanyc);
		rep(mask, 1 << howmanyc)
		{
			bset adj;
			rep(i, howmanyc)
			{
				if (mask & (1 << i)) adj |= rightside[offset + i];
				else adj |= leftside[offset + i];
			}
			pre[mask] = adj;
		}
		offset += howmanyc;
		precomp.push_back(pre);
	}

	bool good = 1;

	rep(i, n)
	{
		bset adj;
		int offset = 0;
		int howmanyc = howmany;
		int it = 0;
		while (offset < m)
		{
			if (offset + howmanyc >= m)
			{
				howmanyc = m - offset;
			}
			int mask = 0;
			rep(j, howmanyc)
			{
				if (whichside[i][offset + j]) mask += 1 << j;
			}
			adj |= precomp[it][mask];
			offset += howmanyc;
			it++;
		}
		if (adj.count() != n - 1)
		{
			good = 0;
			break;
		}
	}

	cout << (good ? "YES" : "NO");

	return 0;
}
