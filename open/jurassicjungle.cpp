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


	int n, m;
	while (cin >> n >> m && n!=-1)
	{
		if (n == m)
		{
			cout << "YES\n";
			rep(i, n)
			{
				cout << i + 1 << " " << (i + 1) % n + 1 << "\n";
			}
			continue;
		}
		if (m == n * (n - 1) / 2)
		{
			cout << "YES\n";
			rep(i, n)
			{
				repp(j, i + 1, n)
				{
					cout << i + 1 << " " << j + 1 << "\n";
				}
			}
			continue;
		}
		if (n%2==0&&(n/2)*(n/2)==m)
		{
			cout << "YES\n";
			rep(i, n/2)
			{
				repp(j, n / 2, n)
				{
					cout << i + 1 << " " << j + 1 << "\n";
				}
			}
			continue;
		}
		cout << "NO\n";

	}

	return 0;
}