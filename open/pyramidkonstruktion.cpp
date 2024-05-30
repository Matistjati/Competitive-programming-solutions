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

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();

	int h, n, m;
	cin >> h >> n >> m;
	bool top = 0;
	if (n) top = 1, n--;
	m += n / 2;
	n %= 2;

	p2 ans = p2(0, 0);
	
	if (!top)
	{
		ans.first++;
	}
	h--;
	int pieces = 0;
	rep(i, h)
	{
		pieces += 2 * (i + 1);
	}
	if (pieces > m)
	{
		if (n)
		{
			ans.first++;
			m++;
		}
		ans.second = pieces - m;
	}
	cout << ans.first << " " << ans.second << "\n";

	return 0;
}
