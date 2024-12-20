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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int dfs(vi& to, vi& incycle, vi& dp, int u)
{
	if (incycle[u])
	{
		return 0;
	}
	int& v = dp[u];
	if (v != -1) return v;

	return v = 1+dfs(to, incycle, dp, to[u]);
}

void solve()
{
    int n;
    cin >> n;

    vi to(n);
    rep(i, n) cin >> to[i], to[i]--;

	UF uf(n);
	vi cyclehead;
	rep(i, n)
	{
		if (uf.sameSet(i, to[i]))
		{
			cyclehead.push_back(i);
		}
		else uf.join(i, to[i]);
	}
	vi incycle(n);
	repe(h, cyclehead)
	{
		int u = h;
		do
		{
			incycle[u] = 1;
			u = to[u];
		} while (u!=h);
	}

	vi dp(n, -1);
	int ans = 0;
	rep(i, n) ans = max(ans, dfs(to, incycle, dp, i));
	cout << 2+ans << "\n";
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
