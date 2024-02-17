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

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

signed main()
{
	fast();

	int n;
	cin >> n;
	vi nums(n);
	rep(i, n)cin >> nums[i];
	int m = -1;
	int c = 0;
	rep(i, n)
	{
		if (nums[i] < m)
		{
			c += m - nums[i];
			nums[i] = m;
		}
		m = nums[i];
	}

	cout << c;
	return 0;
}
