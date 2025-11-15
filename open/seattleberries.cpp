#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)


template<class I> vi lis(const vector<I>&S) {
	if (S.empty()) return {};
	vi prev(sz(S));
	typedef pair<I, int> p;
	vector<p> res;
	repp(i, 0, sz(S)) {
		// change 0 -> i for longest non-decreasing subsequence
		auto it = lower_bound(all(res), p{ S[i], 0 });
		if (it == res.end()) res.emplace_back(), it = res.end() - 1;
		*it = { S[i], i };
		prev[i] = it == res.begin() ? 0 : (it - 1)->second;
	}
	int L = sz(res), cur = res.back().second;
	vi ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vi ref(n);
	repe(v, ref) cin >> v, v--;
	vi rocc(n);
	rep(i, n) rocc[ref[i]] = i;
	rep(i, m - 1)
	{
		vi arr(n);
		repe(v, arr)cin >> v, v--;
		rep(i, n) arr[i] = rocc[arr[i]];
		cout << sz(lis(arr)) << '\n';
	}

	return 0;
}
