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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
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
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
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

signed main()
{
    fast();

	int n;
	cin >> n;

	deque<vector<double>> polys;
	rep(i, n)
	{
		int x;
		cin >> x;
		double p = x / 100.;
		polys.emplace_back(vector<double>({ p, 1 - p }));
	}

	while (sz(polys)>1)
	{
		vector<double> a = polys.front();
		polys.pop_front();
		vector<double> b = polys.front();
		polys.pop_front();
		polys.emplace_back(conv(a, b));
	}

	vector<double> ans = polys.front();
	rep(i, n + 1)
	{
		cout << ans[n-i] << " ";
	}

    return 0;
}
