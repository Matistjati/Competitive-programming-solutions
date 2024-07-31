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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

bool isvalid(vi& nums, int val, int n)
{
	int smol = nums[0] - val;

	multiset<int> b(all(nums));
	vi known;
	known.push_back(smol);
	while (sz(b))
	{
		int k = *begin(b);
		int v = k - smol;
		repe(u, known)
		{
			if (b.find(v + u) == b.end()) return 0;
			b.erase(b.find(v + u));
		}
		known.push_back(v);
	}

	if (sz(known) != n) return 0;
	multiset<int> sums;
	rep(i, n) repp(j, i + 1, n) sums.insert(known[i] + known[j]);
	if (sums != multiset<int>(all(nums))) return 0;
	repe(u, known)
	{
		cout << u << " ";
	}
	return 1;
}

signed main()
{
    fast();

	int n;
	cin >> n;
	int m = n * (n - 1) / 2;
	vi nums(m);
	rep(i, m) cin >> nums[i];
	sort(all(nums));

	repp(i, 1, m)
	{
		// nums[0] = A[0]+A[1]
		// nums[1] = A[0]+A[2]
		// nums[0]-nums[1]=A[1]-A[2]
		// 
		int v = nums[0] - nums[1] + nums[i];
		if (v % 2 == 1) continue;
		v /= 2;
		if (isvalid(nums,v, n))
		{
			return 0;
		}
	}

    return 0;
}
