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

int main() {
	cin.tie(0)->sync_with_stdio(0);

    int l;
    cin >> l;

	vi cars;
	int k = 0;
	while (cin>>k&&k!=0)
	{
		cars.push_back(k);
	}

	int n = cars.size();
	int ans = 0;
    using vp2 = vector<p2>;
    using vvp2 = vector<vp2>;
	vvp2 dp(n+1, vp2(l * 100 + 1, p2(-inf, -1)));
	dp[0][0] = p2(0,-1);
	int t = 0;
	repp(i, 1, n+1)
	{
		rep(j, dp[0].size())
		{
			int otherlane = t - j;
			if (otherlane + cars[i-1] < dp[0].size())
			{
				if (dp[i - 1][j].first + 1 > dp[i][j].first) dp[i][j] = p2(dp[i - 1][j].first + 1, j);
			}

			if (j + cars[i-1] < dp[0].size())
			{
				if (dp[i - 1][j].first + 1 > dp[i][j + cars[i-1]].first) dp[i][j + cars[i-1]] = p2(dp[i - 1][j].first+1, j);
			}
		}
		t += cars[i-1];
	}

	vi dir;
	p2 best = p2(-inf,-inf);
	int j = -1;
	int i = -1;
	for (int k = sz(dp)-1; k>=0; k--)
	{
		rep(l, dp[k].size())
		{
			if (dp[k][l].first > best.first)
			{
				best = dp[k][l];
				j = l;
			}
		}
		if (best.first>=0)
		{
			i = k;
			break;
		}
	}

	while (best.second!=-1)
	{
		if (j == best.second) dir.push_back(0);
		else dir.push_back(1);
		j = best.second;
		best = dp[i - 1][best.second];
		i--;
	}

	cout << dir.size() << "\n";
	reverse(all(dir));
	rep(i, dir.size())
	{
		cout << (dir[i] ? "port" : "starboard");
		cout << "\n";
	}


	return 0;
}
