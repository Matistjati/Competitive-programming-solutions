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

	auto ismia = [](int a, int b)
	{
		return (a == 1 && b == 2) || (b == 1 && a == 2);
	};

	auto getscore = [&](int a, int b)
	{
		if (ismia(a, b)) return inf;
		if (a == b) return 1000 + a;
		if (a < b) swap(a, b);
		return a * 10 + b;
	};

	int a, b, c, d;
	while (cin >> a >> b >> c >> d)
	{
		if (a+b+c+d==0) break;
		int sa = getscore(a,b);
		int sb = getscore(c,d);
		if (sa == sb) cout << "Tie.";
		if (sa > sb) cout << "Player 1 wins.";
		if (sa < sb) cout << "Player 2 wins.";
		cout << "\n";
		
	}
	

	return 0;
}
