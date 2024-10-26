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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();

	int t;
	cin >> t;
	int FUCKTC = 1;
	while (t--)
	{

		int n, r, k;
		cin >> r >> k >> n;
		vi people(n);
		rep(i, n) cin >> people[i];

		vi dist(n);
		auto apply_once = [&](int p)
		{
			dist[p]++;
			int left = k;
			int cp = p;
			do
			{
				if (left < people[cp]) break;
				left -= people[cp];
				cp++;
				cp %= n;
			} while (cp != p);
			return cp;
		};

		if (r<=n*2)
		{
			int p = 0;
			rep(i, r)
			{
				p = apply_once(p);
			}
		}
		else
		{
			int p = 0;
			while (dist[p]==0)
			{
				r--;
				dist[p]++;
				int left = k;
				int cp = p;
				do
				{
					if (left < people[cp]) break;
					left -= people[cp];
					cp++;
					cp %= n;
				} while (cp != p);
				p = cp;
			}
			int percycle = 0;
			while (dist[p] == 1)
			{
				r--;
				dist[p]++;
				int left = k;
				int cp = p;
				do
				{
					if (left < people[cp]) break;
					left -= people[cp];
					cp++;
					cp %= n;
				} while (cp != p);
				p = cp;
			}
			rep(i, n) percycle += dist[i]==2;
			int times = r / percycle;
			rep(i, n) if (dist[i] == 2) dist[i] += times;
			r %= percycle;
			rep(i, r) p = apply_once(p);
		}
		int u = 0;
		
		int ans = 0;
		rep(i, n)
		{
			int cnt = 0;
			int p = i;
			int left = k;
			do
			{
				if (left < people[p]) break;
				left -= people[p];
				cnt += people[p];
				p++;
				p %= n;
			} while (p != i);

			ans += cnt * dist[i];
		}

		cout << "Case #" << FUCKTC << ": " << ans << "\n";
		FUCKTC++;
	}

	return 0;
}
