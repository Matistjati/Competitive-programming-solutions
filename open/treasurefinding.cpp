#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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

using Real = double;
template<int N = 2>
Real solve(const vector<ll>& poly_in)
{
    if constexpr (N > 7) return -1; // impossible
    else {
        if (N < sz(poly_in)) return solve<N + 1>(poly_in);

        array<ll, N> poly;
        rep(i,N) poly[i] = poly_in[i];
        array<ll,N-1> derivative;
        rep(i,N-1) derivative[i] = poly[i+1];
        rep(i, sz(derivative)) derivative[i] *= (i+1);

        Real curr_guess = 0;
        repp(i,1,N) curr_guess = max(curr_guess, pow(abs(Real(poly[N-1-i]/poly[N-1])), 1.0 / i));
        curr_guess = 2 * curr_guess + 1;
        rep(i, 17)
        {
            Real num = 0, denom = 0;
            for (int i = N-1; i >= 0; i--) num = num * curr_guess + poly[i];
            for (int i = N-2; i >= 0; i--) denom = denom * curr_guess + derivative[i];
            curr_guess -= num / denom;
        }
        return curr_guess;
    }
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;

		vector<ll> poly(n+1);
		repe(v, poly) cin >> v;

		if (n == 1) {
			cout << int(round(-double(poly[0]) / poly[1])) << '\n';
			continue;
		}

		cout << int(round(solve(poly))) << '\n';
	}

	return 0;
}
