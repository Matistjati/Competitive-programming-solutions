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
	while (t--)
	{
		int l, n;
		cin >> l >> n;
		l *= 100;
		int ans = 0;
		queue<int> left;
		queue<int> right;
		rep(i, n)
		{
			int d;
			string s;
			cin >> d >> s;
			if (s=="left")
			{
				left.push(d);
			}
			if (s=="right")
			{
				right.push(d);
			}
		}
		bool leftside = 1;
		while (sz(left)||sz(right))
		{
			int k = l;
			queue<int>& curr = leftside ? left : right;
			while (sz(curr)&&curr.front()<=k)
			{
				k -= curr.front();
				curr.pop();
			}

			leftside = !leftside;
			ans++;
		}

		cout << ans << "\n";
	}

	return 0;
}
