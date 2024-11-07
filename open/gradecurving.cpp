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

	int y, ylo, yhi;
	cin >> y >> ylo >> yhi;

	const int its = 1000000;
	vector<long double> evals(its);
	evals[0] = y;
	long double v = y;
	repp(i, 1, its) evals[i] = 10 * sqrtl(evals[i - 1]);

	int indlo = -1;
	int indhi = -1;
	rep(i, its)
	{
		if (ceil(evals[i]) >= ylo && ceil(evals[i]) <= yhi)
		{
			indlo = i;
			break;
		}
	}

	for (int i = its - 1; i >= 0; i--)
	{
		if (ceil(evals[i]) >= ylo && ceil(evals[i]) <= yhi)
		{
			indhi = i;
			break;
		}
	}

	if (indlo==-1||indhi==-1)
	{
		cout << "impossible";
	}
	else
	{
		cout << indlo << " " << (yhi==100?"inf":to_string(indhi));
	}

	return 0;
}
