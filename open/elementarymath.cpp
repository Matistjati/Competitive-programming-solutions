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

bool match(int b, set<int>& vis, map<int, int>& btoa, vvi& edges)
{
	if (btoa.find(b) == btoa.end()) return 1;
	if (vis.find(b) != vis.end()) return 0;
	vis.insert(b);

	int a = btoa[b];
	repe(e, edges[a])
	{
		if (match(e,vis,btoa,edges))
		{
			btoa[e] = a;
			return 1;
		}
	}
	return 0;
}

signed main()
{
	fast();

	int n;
	cin >> n;
	vector<p2> nums(n);
	rep(i, n) cin >> nums[i].first >> nums[i].second;

	vvi edges(n);
	rep(i, n)
	{
		edges[i].push_back(nums[i].first + nums[i].second);
		edges[i].push_back(nums[i].first * nums[i].second);
		edges[i].push_back(nums[i].first - nums[i].second);
	}
	map<int, int> btoa;
	int match_cnt = 0;
	rep(i, n)
	{
		repe(e, edges[i])
		{
			set<int> vis;
			if (match(e, vis,btoa,edges))
			{
				btoa[e] = i;
				match_cnt++;
				break;
			}
		}
	}
	if (match_cnt<n)
	{
		cout << "impossible";
		return 0;
	}
	vi atob(n);
	repe(u, btoa) atob[u.second] = u.first;
	rep(i, n)
	{
		char c='A';
		if (nums[i].first + nums[i].second == atob[i]) c = '+';
		if (nums[i].first * nums[i].second == atob[i]) c = '*';
		if (nums[i].first - nums[i].second == atob[i]) c = '-';

		assert(c != 'A');
		cout << nums[i].first << " " << c << " " << nums[i].second << " = " << atob[i] << "\n";
	}

	return 0;
}
