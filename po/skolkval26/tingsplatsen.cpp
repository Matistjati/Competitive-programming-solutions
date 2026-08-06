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

	int r, c;
	cin >> r >> c;
	vector<string> grid(r);
	repe(row, grid) cin >> row;

	rep(i, r) rep(j, c)
	{
		vi dists;
		rep(k, r) rep(l, c) if (grid[k][l] == '*') dists.push_back(abs(i - k) + abs(j - l));

		if (sz(set<int>(all(dists))) == 1) grid[i][j] = 'X';
	}
	repe(row, grid) cout << row << '\n';

	return 0;
}
