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

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define __builtin_clz __lzcnt
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
	fast();

	int t;
	cin >> t;
	while (t--)
	{
		int w, n;
		cin >> w >> n;
		w *= 1000;

		vi sizes(5000);
		rep(i, n)
		{
			int lo, hi;
			cin >> lo >> hi;
			repp(j, lo, hi + 1) sizes[j] = 1;
		}
		vi deltas;
		rep(i, 5000) if (sizes[i]) deltas.push_back(i);
		sort(all(deltas));
		int k = w / deltas[0];
		w -= k * deltas[0];
		assert(w >= 0);

		vi dp(10000, inf);
		vvi pq(int(1e4));
		pq[0].push_back(w);
		int smol = w;
		rep(r, min(sz(pq),k+1))
		{
			assert(r <= k);
			vi& q = pq[r];
			while (q.size())
			{
				int u = q.back();
				q.pop_back();

				if (dp[u] != inf) continue;
				dp[u] = 1;
				smol = min(smol, u);

				rep(i, sz(deltas))
				{
					int d = deltas[i];
					if (i == 0)
					{
						if (u + d >= sz(dp)) continue;
						pq[r+1].emplace_back(u + d);
					}
					else
					{
						if (u - d < 0) break;
						pq[r].emplace_back(u - d);
					}
				}
			}
		}

		cout << smol << "\n";
	}
	
	return 0;
}
