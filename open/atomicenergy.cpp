// comp_prog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>

using namespace std;
typedef long long ll;
#define rep(i,n) for(int i = 0; i < n; i++)

int main()
{
	int n, q;
	cin >> n >> q;

	vector<ll> cost(n+1);
	rep(i, n)
	{
		cin >> cost[i+1];
	}
	pair<double, pair<ll, ll>> dababy = { 1e15, {ll(1e15), -1} };
	rep(i, n + 1)
	{
		if (!i) continue;
		if (cost[i] / (i + 0.) < dababy.first) dababy = { cost[i] / (i + 0.), {cost[i],i}};
	}
	pair<ll, ll> best = dababy.second;

	const int dpsize = 15000;
	vector<ll> dp(dpsize, ll(1e15));
	rep(i, n+1) dp[i] = cost[i];
	dp[0] = ll(1e15);

	rep(i, dpsize)
	{
		if (i <= n) continue;

		rep(j, i)
		{
			int k = i - j;
			if (k < 1 || j < 1) continue;
			dp[i] = min(dp[i], dp[j] + dp[k]);
		}
	}

	rep(i, q)
	{
		ll v;
		cin >> v;

		ll cost = 0;
		/*for (int i = 31; i >= 0; i--)
		{
			ll t = 1LL << i;
			if ((v - t*best.second) >= ((ll)dp.size()))
			{
				cost += best.first * (t);
				v -= t*best.second;
			}
		}*/
		ll dababy2 = (v - dpsize) / best.second-10;
		dababy2 = max(0LL, dababy2);
		v -= best.second * dababy2;
		cost += best.first * dababy2;
		while (v>=dp.size())
		{
			v -= best.second;
			cost += best.first;
		}
		cout << dp[v]+cost << "\n";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
