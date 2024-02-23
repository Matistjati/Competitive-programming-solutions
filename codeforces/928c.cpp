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

}

signed main()
{
	fast();

	int maxn = int(2e5 + 10);
	vi pref(maxn);

	repp(i, 1, maxn)
	{
		int v = 0;
		repe(c, to_string(i)) v += (c - '0');
		pref[i] = pref[i - 1] + v;
	}

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		cout << pref[n] << "\n";
	}

	return 0;
}
