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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
	fast();

	//ifstream in("C:\\users\\matis\\desktop\\comp_prog\\x64\\debug\\in.txt");
	//cin.rdbuf(in.rdbuf());

	int n;
	cin >> n;
	vi nums;
	rep(i, 1 << n)
	{
		int v;
		cin >> v;
		nums.push_back(v);
	}
	multiset<int> numset;
	repe(v, nums)numset.insert(v);

	vi ans;
	while (numset.size() > 1)
	{
		auto it = next(begin(numset));
		ans.push_back(*it);
		int v = *it;

		multiset<int> newitems;
		while (numset.size())
		{
			auto it2 = begin(numset);
			int k = *it2;
			newitems.insert(k);
			auto it3 = numset.find(*it2 + v);
			if (it3 == numset.end())
			{
				cout << "impossible";
				return 0;
			}
			numset.erase(it3);
			auto it4 = numset.find(k);
			if (it4 == numset.end())
			{
				cout << "impossible";
				return 0;
			}
			numset.erase(it4);
		}
		numset = newitems;
	}
	repe(v, ans) cout << v << "\n";

	return 0;
}
