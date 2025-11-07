#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int max_coord = 2250 + 10;
	int side_len = max_coord * 2;
	vector<vector<int>> rowsum(side_len, vector<int>(side_len));
	vector<vector<int>> colsum(side_len, vector<int>(side_len));

	auto index_rowsum = [&](int i, int j) -> int&
	{
		return rowsum[i + max_coord][j + max_coord];
	};
	auto index_colsum = [&](int i, int j) -> int&
	{
		return colsum[i + max_coord][j + max_coord];
	};

	int R, q;
	cin >> R >> q;
	while (R--)
	{
		int c, r, dc, dr, g;
		cin >> c >> r >> dc >> dr >> g;
		if (dc < 0)
		{
			c += dc;
			dc = -dc;
		}
		if (dr < 0)
		{
			r += dr;
			dr = -dr;
		}

		index_rowsum(r - 1, c) += g;
		index_rowsum(r-1, c+dc) -= g;

		index_rowsum(r + dr - 1, c) += g;
		index_rowsum(r + dr - 1, c + dc) -= g;

		index_colsum(r, c + dc) += g;
		index_colsum(r + dr, c + dc) -= g;

		index_colsum(r + dr, c) -= g;
		index_colsum(r, c) += g;
	}

	rep(i, sz(rowsum)) repp(j, 1, sz(rowsum[0])) rowsum[i][j] += rowsum[i][j - 1];
	repp(i, 1, sz(colsum)) rep(j, sz(colsum[0])) colsum[i][j] += colsum[i - 1][j];

	vvi prefrow(side_len, vi(side_len));
	vvi prefcol(side_len, vi(side_len));
	rep(i, sz(prefrow)) rep(j, sz(prefrow))
	{
		ll val = rowsum[i][j];
		if (i) val += prefrow[i - 1][j];
		if (j) val += prefrow[i][j - 1];
		if (i>0 && j>0) val -= prefrow[i-1][j-1];
		prefrow[i][j] = val;
	}

	rep(i, sz(prefcol)) rep(j, sz(prefcol))
	{
		ll val = colsum[i][j];
		if (i) val += prefcol[i - 1][j];
		if (j) val += prefcol[i][j - 1];
		if (i > 0 && j > 0) val -= prefcol[i - 1][j - 1];
		prefcol[i][j] = val;
	}

	auto rect_query = [&](vvi& pref, int rl, int rh, int cl, int ch)
	{
		ll ret = pref[rh+max_coord][ch+max_coord];
		ret -= pref[rl - 1 + max_coord][ch + max_coord];
		ret -= pref[rh + max_coord][cl - 1 + max_coord];
		ret += pref[rl-1+max_coord][cl - 1 + max_coord];
		return ret;
	};

	while (q--)
	{
		int c, r, dc, dr;
		cin >> c >> r >> dc >> dr;
		if (dc < 0)
		{
			c += dc;
			dc = -dc;
		}
		if (dr < 0)
		{
			r += dr;
			dr = -dr;
		}

		ll naive = 0;
		naive += rect_query(prefrow, r - 1, r + dr - 1, c, c + dc - 1);

		naive += rect_query(prefcol, r, r + dr - 1, c, c + dc);

		cout << naive << '\n';
	}

	return 0;
}
