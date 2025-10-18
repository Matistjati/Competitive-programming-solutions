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

	int n, m, k;
	cin >> n >> m >> k;
	const int maxn = 2001;
	using bset = bitset<maxn>;
	vector<bset> adj(n);
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		adj[a][b] = 1;
		adj[b][a] = 1;
	}

	rep(i, n)
	{
		repp(j, i + 1, n)
		{
			bset res = adj[i] & adj[j];
			res[i] = 0;
			res[j] = 0;
			if (res.count()>=k)
			{
				cout << "YES";
				return 0;
			}
		}
	}
	cout << "NO\n";

	return 0;
}
