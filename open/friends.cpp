#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

bool done = false;
typedef bitset<128> B;
template<class F>
void cliques(vector<B>& eds, F f, B P = ~B(), B X = {}, B R = {}) {
	if (!P.any()) { if (!X.any()) f(R); return; }
	auto q = (P | X)._Find_first();
	auto cands = P & ~eds[q];
	repp(i, 0, sz(eds)) if (cands[i]) {
		R[i] = 1;
		cliques(eds, f, P & eds[i], X & eds[i], R);
		if (done) return;
		R[i] = P[i] = 0; X[i] = 1;
	}
}

signed main()
{
    fast();

	int n, m;
	while (cin >> n >> m)
	{
		vector<B> adj(n);
		rep(i, m)
		{
			int a, b;
			cin >> a >> b;
			a--; b--;
			adj[a][b] = 1;
			adj[b][a] = 1;
		}

		int ans = 0;
		cliques(adj, [&ans](B r)
			{
				ans++;
				if (ans > 1000)
				{
					cout << "Too many maximal sets of friends.\n";
					done = true;
				}
			});
		if (!done)
		{
			cout << ans << "\n";
		}
		done = false;
	}


    return 0;
}
