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

struct UF
{
	int n;
	vi par;
	vi size;

	UF(int n) : n(n), par(n), size(n, 1)
	{
		rep(i, n) par[i] = i;
	}

	int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }

	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);

		par[b] = a;
		size[a] += size[b];
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int r,c,n;
	cin >> r >> c >> n;

	vector<p2> events(n);
	rep(i, n) cin >> events[i].first >> events[i].second;

	vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

	UF uf(n + 2);

	map<p2, int> added;
	rep(i, n) {
		p2 ev = events[i];

		for (auto [di, dj] : dirs) {
			p2 np = {ev.first+di, ev.second+dj};
			if (added.count(np)) {
				uf.merge(i, added[np]);
			}
			if (np.first == 0) uf.merge(i, n);
			if (np.first == r - 1) uf.merge(i, n + 1);
		}
		added[ev] = i;

		if (uf.find(n) == uf.find(n + 1)) {
			cout << i + 1 << endl;
			return 0;
		}
	}

	cout << "nej\n";
	return 0;
}
