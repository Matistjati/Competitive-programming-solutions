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

void solve()
{
	int n, q;
	cin >> n >> q;
	q--;
	int k = 0;

	int i = 0;
	while (k < n)
	{
		int num = (n - (1 << i)) / (1 << (i + 1)) + 1;
		if (q < num) break;
		i++;
		k += num;
		q -= num;
	}
	cout << (1 << i) * (q * 2 + 1) << "\n";
}

signed main()
{
	fast();


	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}

	return 0;
}
