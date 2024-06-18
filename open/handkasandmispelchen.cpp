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

	int k, n;
	cin >> k >> n;

	typedef tuple<int, int, int> p3;
	vector<p3> bars(n);
	rep(i, n) cin >> get<0>(bars[i]) >> get<1>(bars[i]);
	rep(i, n)get<2>(bars[i]) = i;
	sort(bars.rbegin(), bars.rend());
	vector<p3> barsdrink(bars);
	sort(all(barsdrink), [](p3 a, p3 b)
		{
			return get<1>(a) > get<1>(b);
		});

	int ans = inf;
	rep(i, n)
	{
		int t = k;
		t -= get<0>(bars[i]);
		int c = 0;
		rep(j, n)
		{
			if (t <= 0) break;
			if (i == j) continue;
			c++;
			t -= get<0>(bars[j]);
		}
		if (t > 0) continue;
		int d = k;
		d -= get<1>(bars[i]);
		rep(j, n)
		{
			if (get<2>(barsdrink[j]) == get<2>(bars[i])) continue;
			if (d <= 0) break;
			c++;
			d -= get<1>(barsdrink[j]);
		}
		if (d > 0) continue;
		ans = min(ans, c);
	}
	cout << ans;

	return 0;
}
