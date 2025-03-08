#include <bitset>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <immintrin.h>
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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int n;
int ask(int x)
{
	cout << "? " << x << endl;
	int resp;
	cin >> resp;
	return resp;
}

signed main()
{
	fast();

	cin >> n;
	// find starting guess.
	// we will start at some number, then alternate left/right. find extreme deviation from start and place start
	// based on that
	vi nums;
	{
		int lo = 0;
		int hi = n;
		while (lo + 1 < hi)
		{
			int mid = (lo + hi) / 2;
			nums.push_back(mid);
			lo = mid;
		}
	}
	int mi = n;
	int pref = 0;
	rep(i, sz(nums)) pref += (i % 2 ? 1 : -1) * nums[i], mi = min(mi, pref);

	int start = -mi + 1;
	ask(start);

	// start guessing
	int last = start;
	int lo = 0;
	int hi = n;
	int i = 0;

	int direction = -1;
	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;
		int g;
		if (i % 2) g = last + mid;
		else g = last - mid;

		if (ask(g))
		{
			hi = mid;
		}
		else lo = mid;
		last = g;
		i++;
	}
	cout << "= " << hi << endl;

	return 0;
}
