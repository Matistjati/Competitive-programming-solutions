#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

typedef double ld;
ld p;

typedef vector<vector<ld>> mat;
mat build_mat()
{
	ld DIV_STEP = 1.L / (1.L - powl(1.L - p, 100));

	vector<vector<ld>> mat(102);
	vector<ld> weights(102);

	repp(i, 1, 101)
	{
		rep(j, 102)
		{
			weights[j] *= (1 - p);
		}
		weights[i - 1] += p;
	}
	weights.back() += 5;
	rep(i, 102) weights[i] *= DIV_STEP;
	mat[0] = weights;

	repp(i, 1, 101)
	{
		rep(j, 102) weights[j] *= (1 - p);
		weights[i - 1] += p;
		mat[i] = weights;
	}
	vector<ld> row(102);
	row.back() = 1;
	mat.back() = row;
	return mat;
}

mat matmul(mat a, mat b)
{
	mat ret(sz(a), vector<ld>(sz(b[0])));
	rep(i, sz(a)) rep(j, sz(b[0])) rep(k, sz(a[0])) ret[i][j] += a[i][k] * b[k][j];
	return ret;
}

ld solve(int n)
{
	mat m = build_mat();
	mat cum(102, vector<ld>(102));
	rep(i, 102)cum[i][i] = 1;

	while (n)
	{
		if (n % 2) cum = matmul(cum, m);
		m = matmul(m, m);
		n >>= 1;
	}

	return accumulate(all(cum[100]), 0.L) - 1;
}


int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n >> p;
	cout << fixed << setprecision(15) << solve(n) << '\n';

	return 0;
}
