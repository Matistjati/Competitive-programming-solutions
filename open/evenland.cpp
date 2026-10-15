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

struct UF {
	vector<int> par;
	UF(int n) : par(n) { iota(all(par),0); }
	int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
	int merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return 0;
		par[b] = a;
        return 1;
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	UF uf(n);
    int ncomps = n;
	rep(i, m) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		ncomps -= uf.merge(a, b);
	}
	int ans = 1;
	const int mod = 1e9 + 9;
	rep(i, m - n + ncomps)
	{
		ans = (ans * 2) % mod;
	}
	cout << ans << '\n';

	return 0;
}
