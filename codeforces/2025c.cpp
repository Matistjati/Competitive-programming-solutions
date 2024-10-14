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

void solve()
{
	
}

int binpow(int a, int b, int m) // a^b mod m
{
	int ret = 1;
	int e = a;
	while (b)
	{
		if (b % 2) ret = (ret * e) % m;
		e = (e * e) % m;
		b >>= 1;
	}

	return ret;
}

signed main()
{
	fast();

	int t;
	cin >> t;
	vi nq(t);
	vi kq(t);
	rep(i, t) cin >> nq[i];
	rep(i, t) cin >> kq[i];

	rep(i, t)
	{
		cout << binpow(2, kq[i], int(1e9 + 7)) << "\n";
	}
	
	


	return 0;
}
