#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
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
void fft(vector<C>& a) {
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
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - countl_zero(res.size()), n = 1 << L;
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

vi contr;
int n;
vi av;
vi bv;
vd AA;
vd BB;
void dc(int l, int r, vi& a, vi& b)
{
	if (l == r) return;
	int mid = (l + r) / 2;

	int d = r - l;
	if (d > 26000)
	{

		repp(i, l, mid + 1) if (b[i] != -1) BB[b[i]] = 1;
		repp(i, mid + 1, r + 1) if (a[i] != -1) AA[n-1-a[i]] = 1, AA[2*n - 1 - a[i]] = 1;

		vd res = conv(AA, BB);
		repp(i, sz(BB) - 1, sz(BB) * 2 - 1) contr[i - sz(BB) + 1] += round(res[i]);
		repp(i, l, mid + 1) if (b[i] != -1) BB[b[i]] = 0;
		repp(i, mid + 1, r + 1) if (a[i] != -1) AA[n - 1 - a[i]] = 0, AA[2 * n - 1 - a[i]] = 0;

	}
	else
	{
		int bcnt = 0;
		int acnt = 0;
		repp(i, mid + 1, r + 1) if (a[i] != -1) av[acnt++] = a[i];
		repp(j, l, mid + 1) if (b[j] != -1) bv[bcnt++] = b[j];

		rep(i, acnt) rep(j, bcnt)
		{
			int k = -av[i] + bv[j];
			contr[n + k]++;
		}
	}

	dc(l, mid, a, b);
	dc(mid + 1, r, a, b);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

#if 0
	n = 2e5;
	vector<int> a(n), b(n);
	uniform_int_distribution<int> dist(0, 1e9);
	mt19937 rng;
	rep(i, n) a[i] = dist(rng);
	rep(i, n) b[i] = dist(rng);
#else
	cin >> n;
	vector<int> a(n), b(n);
	repe(v, a) cin >> v;
	repe(v, b) cin >> v;
#endif
	map<int, int> compress;
	set<int> seen;
	repe(v, a) seen.insert(v);
	repe(v, b) seen.insert(v);

	repe(v, seen) compress[v] = sz(compress);
	repe(v, a) v = compress[v];
	repe(v, b) v = compress[v];

	contr.resize(n*3);
	av.resize(n);
	bv.resize(n);
	AA.resize(2 * n);
	BB.resize(n);
	int uniq = sz(seen);
	vi aa(uniq, -1);
	vi bb(uniq, -1);
	rep(i, sz(a)) aa[a[i]] = i;
	rep(i, sz(b)) bb[b[i]] = i;

	dc(0, uniq - 1, aa, bb);

	int ans = 0;
	for (int i = sz(contr) - 1; i >= 0; i--) if (i - n >= 0) contr[i] += contr[i - n];
	rep(i, n) ans += contr[i+n] * 2 > n;
	cout << ans << '\n';
	rep(i, n) if (contr[i+n] * 2 > n) cout << i << ' ';

	return 0;
}
