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

	int n, c, b;
	cin >> n >> c >> b;
	vi is_broken(n);
	rep(i, b)
	{
		int p;
		cin >> p;
		p--;
		is_broken[p] = 1;
	}

	vector<p2> locs;
	p2 curr_inter = p2(-1,-1);
	repp(i, 1, n)
	{
		if (is_broken[i])
		{
			if (curr_inter.first!=-1)
			{
				locs.push_back(curr_inter);
			}
			curr_inter = p2(-1,-1);
		}
		else
		{
			if (curr_inter.first == -1) curr_inter = p2(i, i);
			else curr_inter.second++;
		}
	}
	if (curr_inter.first != -1)
	{
		locs.push_back(curr_inter);
	}

	string ans(n, '0');
	bool odd = c%2;
	if (odd) c--;
	if (odd)
	{
		if (sz(locs) && locs[0].first == 1) locs[0].first++;
	}
	else
	{
		if (sz(locs) && locs[0].first == 1) locs[0].first--;
	}
	while (c)
	{
		p2 p = locs.back();
		locs.pop_back();
		for (int i = p.second; i >= p.first; i -= 2)
		{
			ans[i] = '1';
			c -= 2;
			if (c == 0) break;
		}
	}
	if (odd)
	{
		ans[0] = '1';
	}
	cout << ans << '\n';

	return 0;
}
