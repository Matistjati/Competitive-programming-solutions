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


struct Tree {
	using T = p2;
	static constexpr T unit = {0,0};
	T f(T a, T b) { return {a.first+b.first, max(a.second,a.first+b.second)}; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, ll val) {
		for (s[pos+=n].first+=val, s[pos].second += val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n, w, h;
	cin >> n >> w >> h;
	Tree tree(n+1);

	vector<array<int, 3>> trash(n);
	vi xcoord;
	rep(i, n) {
		int x, y, w;
		cin >> x >> y >> w;
		trash[i] = { x,y,w };
		xcoord.push_back(x);
	}
	sort(all(xcoord));
	sort(all(trash), [](array<int, 3> a, array<int, 3> b) {
        return a[1] < b[1];
    });

	ll ans = 0;
	int p = 0;
	rep(i, n)
	{
		while (p<n&&trash[i][1] + h - 1 >= trash[p][1])
		{
			int lpos = lower_bound(all(xcoord), trash[p][0] - w + 1) - begin(xcoord);
			int rpos = prev(upper_bound(all(xcoord), trash[p][0])) - begin(xcoord);
			tree.update(lpos,trash[p][2]);
			tree.update(rpos+1,-trash[p][2]);
			p++;
		}

		ans = max(ans, tree.query(0,n+1).second);
		int myx = trash[i][0];
		int lpos = lower_bound(all(xcoord), myx - w + 1) - begin(xcoord);
		int rpos = prev(upper_bound(all(xcoord), myx)) - begin(xcoord);
		tree.update(lpos, -trash[i][2]);
		tree.update(rpos+1, trash[i][2]);
	}
	cout << ans << '\n';

	return 0;
}
