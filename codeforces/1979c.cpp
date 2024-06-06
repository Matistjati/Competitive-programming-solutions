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
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vi nums(n);
		rep(i, n) cin >> nums[i];

		int mid = int(1e9) - 10;
		int t = 0;
		rep(i, n)
		{
			t += (nums[i] - 1 + mid) / nums[i];
		}
		if (t < mid)
		{
			rep(i, n)
			{
				cout << (nums[i] - 1 + mid) / nums[i] << " ";
			}
			cout << "\n";
			continue;
		}

		cout << "-1\n";
	}




	return 0;
}
