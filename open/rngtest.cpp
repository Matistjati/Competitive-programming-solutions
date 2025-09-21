#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	
	ll a, b, x, n, m;
	cin >> a >> b >> x >> n >> m;

	
	auto matmul = [m](vvi a, vvi b)
		{
			vvi res(sz(a), vi(sz(b[0])));
			rep(i, sz(a)) rep(j, sz(b[0]))
			{
				rep(k, sz(a[0])) res[i][j] += (a[i][k] * b[k][j]) % m;
			}

			return res;
		};

	vvi mat(2, vi(2));
	mat[0][0] = a;
	mat[1][0] = b;
	mat[1][1] = 1;

	vvi ans = mat;

	vvi state({ { x, 1 } });
	while (n)
	{
		if (n % 2) state = matmul(state, ans);
		ans = matmul(ans, ans);
		n >>= 1;
	}

	cout << (state[0][0]) % m << '\n';

	return 0;
}
