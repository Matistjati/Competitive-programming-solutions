#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
#define inf int(1e18)

typedef vector<int> vi;
typedef vector<vi> vvi;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)

#define all(a) a.begin(),a.end()
#define sz(container) ((int)container.size())

typedef vector<vector<long double>> matrix;

matrix multiply(matrix& a, matrix& b)
{
	matrix res(a.size(), vector<long double>(b[0].size()));

	rep(i, res.size())
	{
		rep(j, res[0].size())
		{
			long double v = 0;

			rep(k, b.size()) v += a[i][k] * b[k][j];

			res[i][j] = v;
		}
	}
	return res;
}

int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);

    int r,c,k;
    cin >> r >> c >> k;
    long double ansp;
    cin >> ansp;

	int n = r * c;
	matrix p(n, vector<long double>(n));

	vi ladder(n, -1);
	rep(i, n) ladder[i] = i;
	rep(i, k)
	{
	    int a,b;
	    cin >> a >> b;
		a--; b--;
		ladder[a] = b;
	}

	rep(i, n)
	{
		int cnt = 0;
		repp(j, i + 1, i + 7) if (j < n) cnt++;
		repp(j, i + 1, i + 7)
		{
			if (j >= n) break;
			p[i][ladder[j]] += 1.0l / 6.0l;
		}
		if (cnt < 6)
		{
			p[i].back() += (6.0l - cnt) / 6.0l;
		}
	}

	matrix pos = { {} };
	rep(i, n) pos[0].push_back(0);
	pos[0][0] = 1;

	int lo = 0;
	int hi = int(1e9);

	auto winprob = [&](int k)
	{
		matrix p2 = p;
		matrix pos2 = pos;
		while (k)
		{
			if (k % 2 == 1)
			{
				pos2 = multiply(pos2, p2);
			}
			k >>= 1;
			p2 = multiply(p2, p2);
		}
		return pos2[0].back();
	};

	while (hi - lo > 1)
	{
		int mid = (hi + lo) / 2;

		if (winprob(mid) >= ansp)
		{
			hi = mid;
		}
		else
		{
			lo = mid;
		}
	}

	cout << hi;

	return 0;
}
