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




void solve()
{
	int n;
	cin >> n;

	auto ask = [](int i, int j)
	{
		cout << "? " << i << " " << j << endl;
		int res;
		cin >> res;
		return res;
	};

	auto respond = [](int a)
	{
		cout << "! " << a << endl;
	};

	for (int i = 1; i < n; i += 2)
	{
		int j = i + 1;
		int a = ask(i, j);
		int b = ask(j, i);
		if (a+b==1)
		{
			int t = i > 1 ? 1 : n;
			int za = ask(j, t);
			int zb = ask(i, t);
			if (za==zb) // knave, impostor
			{
				respond(a == 0 ? j : i);
			}
			else // knight, impostor
			{
				respond(a == 0 ? i : j);
			}
			return;
		}
	}
	// if n is odd, it's the last one
	respond(n);
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
