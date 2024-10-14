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

double maxArea(double a, double b, double c, double d)
{
    double semiperimeter = (a + b + c + d) / 2;

    return sqrt((semiperimeter - a) *
        (semiperimeter - b) *
        (semiperimeter - c) *
        (semiperimeter - d));
}

signed main()
{
	fast();

	int a, b, c, d;
	cin >> a >> b >> c >> d;

    cout << fixed << setprecision(15) << maxArea(a, b, c, d);

	return 0;
}
