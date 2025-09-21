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

const ll mod = 1e9+7;
// assumes that a*b does not overflow, where a,b<mod
namespace linear_recurrence {
	ll modpow(ll b, ll e) {
		ll ans = 1;
		for (; e; b = b * b % mod, e /= 2)
			if (e & 1) ans = ans * b % mod;
		return ans;
	}

	vector<ll> berlekampMassey(vector<ll> s) {
		int n = sz(s), L = 0, m = 0;
		vector<ll> C(n), B(n), T;
		C[0] = B[0] = 1;

		ll b = 1;
		repp(i, 0, n) {
			++m;
			ll d = s[i] % mod;
			repp(j, 1, L + 1) d = (d + C[j] * s[i - j]) % mod;
			if (!d) continue;
			T = C; ll coef = d * modpow(b, mod - 2) % mod;
			repp(j, m, n) C[j] = (C[j] - coef * B[j - m]) % mod;
			if (2 * L > i) continue;
			L = i + 1 - L; B = T; b = d; m = 0;
		}

		C.resize(L + 1); C.erase(C.begin());
		for (ll& x : C) x = (mod - x) % mod;
		return C;
	}

	int m;
	vector<ll> a, h, t_, s, t;
	void mull(ll* p, ll* q) {
		rep(i,2*m) t_[i] = 0;
		rep(i,m) if (p[i]) rep(j,m)
				t_[i + j] = (t_[i + j] + p[i] * q[j]) % mod;
		for (int i = m + m - 1; i >= m; --i) if (t_[i])
			for (int j = m - 1; ~j; --j)
				t_[i - j - 1] = (t_[i - j - 1] + t_[i] * h[j]) % mod;
		rep(i,m) p[i] = t_[i];
	}
	ll calc(ll K) {
		for (int i = m; ~i; --i)
			s[i] = t[i] = 0;
		s[0] = 1; if (m != 1) t[1] = 1; else t[0] = h[0];
		while (K)
		{
			if (K & 1) mull(&s[0], &t[0]);
			mull(&t[0], &t[0]); K >>= 1;
		}
		ll su = 0;
		for (int i = 0; i < m; ++i) su = (su + s[i] * a[i]) % mod;
		return (su % mod + mod) % mod;
	}
	ll nth_term(vector<ll> x, ll n) { // n-th term 0-indexed
		if (n<int(x.size())) return x[n];
		vector<ll> v = berlekampMassey(x);
		m = v.size(); if (!m) return 0;
		if (2 * m >= sz(x)) cerr << "WARNING: probably need more terms" << endl;
		a.resize(m); h.resize(m); t_.resize(m * 2); s.resize(m + 1); t.resize(m + 1);
		for (int i = 0; i < m; ++i) h[i] = v[i], a[i] = x[i];
		return calc(n);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	ll k, n;
	cin >> k >> n;

	vi masks;
	rep(mask, 1 << k)
	{
		bool good = 1;
		rep(j, k-1)
		{
			if ((mask&(1<<j)) && (mask&(1<<(j+1))))
			{
				good = 0;
			}
		}
		if (good) masks.push_back(mask);
	}

	vector<pair<ll,ll>> dp;
	repe(mask, masks) dp.emplace_back(1, mask);

	vi terms;
	rep(i, 200)
	{
		ll s = 0;
		repe(m, dp) s += m.first;
		s %= mod;
		terms.push_back(s);
		vector<p2> newdp;

		repe(m, masks)
		{
			ll cnt = 0;
			repe(v, dp)
			{
				cnt += v.first * ((v.second & m) == 0);
			}

			newdp.emplace_back(cnt%mod, m);
		}

		dp = newdp;
	}

	cout << linear_recurrence::nth_term(terms, n-1);

	return 0;
}
