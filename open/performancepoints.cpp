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

const ll mod = 1e9+7;
ll modpow(ll a, ll b) {
	ll ret = 1;
	while (b) {
		if (b % 2) ret = ret * a % mod;
		a = a * a % mod;
		b /= 2;
	}

	return ret;
}

struct Tree { // range add, range sum
    vi tree, lazy;
    Tree(int n) : tree(n * 4), lazy(n * 4, 1) {}
    void put_node(int x, int l, int r, ll v) {
		tree[x] = tree[x] * v % mod;
        lazy[x] = lazy[x] * v % mod;
    }
    void push(int x, int l, int r) {
        int mid = (l + r) / 2;
        put_node(x * 2, l, mid, lazy[x]);
        put_node(x * 2 + 1, mid + 1, r, lazy[x]);
        lazy[x] = 1;
    }
    void add1(int x, int l, int r, int i, int v) {
        if (l == r) {
			//cerr << "tree[" << x << "] = " << v << '\n';
			return void(tree[x] = v);
		}
        push(x, l, r);
        int mid = (l + r) / 2;
        if (i<=mid) add1(x * 2, l, mid, i, v);
        else add1(x * 2 + 1, mid + 1, r, i, v);
		// cerr << "tree[" << x << "] = " << tree[x * 2] + tree[x * 2 + 1] << '\n';
        tree[x] = (tree[x * 2] + tree[x * 2 + 1]) % mod;
    }
    // add v to [l,r]. call add(1,0,n-1,...)
	void add2(int x, int l, int r, int ql, int qr, int v) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) return put_node(x, l, r, v);
        push(x, l, r);
        int mid = (l + r) / 2;
        add2(x * 2, l, mid, ql, qr, v);
        add2(x * 2 + 1, mid + 1, r, ql, qr, v);
        tree[x] = (tree[x * 2] + tree[x * 2 + 1]) % mod;
    }
};

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    
	int n;
	cin >> n;

	vector<p2> vals(n);
	rep(i,n) cin >> vals[i].first, vals[i].second=i;
	sort(all(vals), [](p2 a, p2 b) {
		if (a.first != b.first) return a.first > b.first;
		return a.second > b.second;
	});

	vi loc(n);
	rep(i,n) loc[vals[i].second] = i;
	sort(all(vals), [](p2 a, p2 b) {
		return a.second < b.second;
	});

	Tree tree(n);
	FT ft(n);
	ll ans = 0;
	ll factor = 19 * modpow(20, mod-2) % mod;
	vi ff(n+1);
	ff[0] = 1;
	repp(i,1,n+1) ff[i] = ff[i-1] * factor % mod;
	for (auto [v, ind] : vals) {
		int p = loc[ind];
		tree.add1(1,0,n-1,p,v*ff[ft.query(p)]%mod);
		tree.add2(1,0,n-1,p+1,n-1,factor);
		ft.update(p, 1);
		cout << tree.tree[1]%mod << '\n';
	}

    return 0;
}
