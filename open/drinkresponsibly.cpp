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

vector<string> names;
vi strength;
vi cost;
int vis[10][2000][2000];
void dp(int i, int money, int drunk, vi& howmany)
{
	if (vis[i][drunk][money]) return;
	if (money==0&& drunk==0)
	{
		rep(i, sz(names))
		{
			if (howmany[i]) cout << names[i] << " " << howmany[i] << "\n";
		}
		exit(0);
	}
	if (i == sz(names)) return;
	rep(c,int(1e9))
	{
		if (money - cost[i] * c >= 0 && drunk - strength[i] * c >= 0)
		{
			howmany[i] = c;
			dp(i + 1, money - cost[i] * c, drunk - strength[i] * c, howmany);
		}
		else break;
	}
	vis[i][drunk][money] = 1;
}

signed main()
{
	fast();

	memset(vis, 0, sizeof(vis));
	double md, dd;
	int n;
	cin >> md >> dd >> n;
	int money = int(md * 100);
	int drunk = int(dd * 10)*6;
	rep(i, n)
	{
		string name, size;
		int p;
		double price;
		cin >> name >> p >> size >> price;
		names.push_back(name);
		if (size.back() == '3') p *= 2;
		else if (size.back() == '2') p *= 3;
		else p *= 6;
		strength.push_back(p*10);

		cost.push_back(int(price * 100));
	}
	vi howmany(n);
	dp(0,money, drunk, howmany);
	cout << "IMPOSSIBLE";

	return 0;
}
