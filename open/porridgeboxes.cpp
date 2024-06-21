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

signed main()
{
	fast();

	int a, b, d, n;
	cin >> a >> b >> d >> n;

	vi times(n);
	rep(i, n) cin >> times[i];
	vi can(int(2e5));
	rep(i, n) can[times[i]] = 1;

	int lo = d-2;
	int hi = int(2e5);
	while (lo+1<hi)
	{
		int mid = (hi + lo) / 2;

		int porridge_empty = -1;
		int fridge = 0;
		int porridge_consumed = 0;
		rep(t, b)
		{
			if (can[t])
			{
				fridge--, porridge_consumed++;
				if (fridge + d <= mid) fridge += d;
			}
			else
			{
				if (fridge) fridge--, porridge_consumed++;
			}
		}

		if (porridge_consumed >= a)
		{
			hi = mid;
		}
		else lo = mid;
	}
	if (hi == int(2e5)) cout << "impossible";
	else cout << hi;

	return 0;
}
