#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct UF
{
	vi par;
	vi size;
	UF(int n) : par(n), size(n, 1)
	{
		rep(i, n) par[i] = i;
	}
	int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		par[b] = a;
		size[a] += size[b];
	}
};



signed main()
{
    fast();

	int n;
	cin >> n;

	vi deg(n);
	rep(i, n) cin >> deg[i];
	int t = 0;
	rep(i, n) t += deg[i];
	if (t%2==1)
	{
		cout << "IMPOSSIBLE";
		return 0;
	}
	UF uf(n);

	vector<p2> ans;
	rep(_, t / 2)
	{
		vector<pair<int, p2>> candidates;
		rep(i, n)
		{
			rep(j, n)
			{
				if (deg[i]==0||deg[j] == 0) continue;
				candidates.emplace_back(deg[i]+deg[j], p2(i,j));
			}
		}
		sort(candidates.rbegin(), candidates.rend());
		repe(c, candidates)
		{
			int a, b;
			tie(a,b) = c.second;
			if (uf.find(a)!=uf.find(b))
			{
				uf.merge(a, b);
				deg[a]--;
				deg[b]--;
				ans.emplace_back(a, b);
				break;
			}
		}
	end:;
	}
	if (sz(ans) * 2 == t)
	{
		cout << "POSSIBLE\n";
		repe(e, ans) cout << e.first + 1 << " " << e.second + 1 << "\n";
	}
	else cout << "IMPOSSIBLE";

    return 0;
}
