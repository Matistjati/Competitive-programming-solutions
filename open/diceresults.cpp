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


const ll mod = (119 << 23) + 1, root = 62; // = 998244353

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void ntt(vl & a) {
	int n = sz(a), L = 31 - countl_zero((unsigned int)n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = { 1, modpow(root, mod >> s) };
		repp(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	repp(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	repp(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) repp(j, 0, k) {
			ll z = rt[j + k] * a[i + j + k] % mod, & ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}
vl conv(const vl & a, const vl & b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - countl_zero((unsigned int)s),
		n = 1 << B;
	int inv = modpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	repp(i, 0, n)
		out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return { out.begin(), out.begin() + s };
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vi nums(n);
	int t = 0;
	repe(v, nums) cin >> v, t += v;
	sort(all(nums));
	deque<vl> dice;
	repe(v, nums)
	{
		vl dist;
		rep(i, v) dist.push_back(1);
		dice.push_back(dist);
	}
	while (sz(dice)>1)
	{
		vl a = dice.front(); dice.pop_front();
		vl b = dice.front(); dice.pop_front();
		dice.push_back(conv(a, b));
	}
	vl ans = dice[0];
	while (sz(ans) < t) ans.push_back(0);
	reverse(all(ans));
	repe(v, ans) cout << v << '\n';

    return 0;
}
