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


typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>&a) {
	int n = sz(a), L = 31 - countl_zero((unsigned int)n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		repp(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
	}
	vi rev(n);
	repp(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	repp(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) repp(j, 0, k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];        /// exclude-line
			C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd & a, const vd & b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - countl_zero((unsigned int)sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	repp(i, 0, sz(b)) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	repp(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	repp(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

	int n, m;
	cin >> n >> m;
	const int base = 1e5 + 10;
	vd freqa(base*2+10), freqb(base*2+10);
	rep(i, n)
	{
		int x;
		cin >> x;
		x += base;
		freqa[x]++;
	}
	rep(i, m)
	{
		int x;
		cin >> x;
		x += base;
		freqb[x]++;
	}

	vd res = conv(freqa, freqb);
	int q;
	cin >> q;
	while (q--)
	{
		ll x;
		cin >> x;
		x += base*2;
		if (x<0 || x>sz(res)) cout << "0\n";
		else cout << res[x] << "\n";
	}


    return 0;
}
