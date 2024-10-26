#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
//const int inf = int(1e18);

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

const int mod = int(1e9 + 7);
int modpow(int b, int e)
{
	int ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}



signed main()
{
	fast();

	vi factorial(int(2e5));
	vi invfactorial(int(2e5));
	factorial[0] = 1;
	repp(i, 1, sz(factorial)) factorial[i] = factorial[i - 1] * i % mod;
	rep(i, sz(invfactorial)) invfactorial[i] = modpow(factorial[i], mod - 2);

	auto binomial = [&](int n, int k)
	{
		if (n < 0 || k < 0 || n - k < 0) return 0LL;
		return factorial[n] * invfactorial[k] % mod * invfactorial[n - k] % mod;
	};

	int r, c;
	cin >> c >> r;
	int n;
	cin >> n;
	vector<p2> cheese;
	rep(i, n)
	{
		int a, b;
		cin >> b >> a;
		a--; b--;
		cheese.emplace_back(a, b);
	}
	sort(all(cheese));

	int ans = 0;
	repp(mask, 1, 1 << n)
	{
		int cnt = 1;

		vector<p2> positions;
		positions.emplace_back(0, 0);
		rep(i, n)
		{
			if (mask&(1<<i)) positions.push_back(cheese[i]);
		}
		positions.emplace_back(r - 1, c - 1);

		
		cnt = 1;
		repp(i, 1, sz(positions))
		{
			int nc = positions[i].first - positions[i - 1].first + positions[i].second - positions[i - 1].second;
			cnt = cnt * binomial(nc, positions[i].first-positions[i-1].first) % mod;
		}
		

		ans += (popcount((unsigned long long)mask) % 2 ? 1 : -1) * cnt;
		ans %= mod;
		ans += mod;
		ans %= mod;
	}
	cout << ans;

	return 0;
}
