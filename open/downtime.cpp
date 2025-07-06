#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, k;
	cin >> n >> k;
	vi times(n);
	repe(v, times) cin >> v;

	int lo = 0;
	int hi = n + 1;
	while (lo+1<hi)
	{
		int mid = (lo + hi) / 2;

		queue<p2> waiting;
		set<int> active;
		rep(i, mid) active.insert(i);
		vi slots(mid, k);
		bool possible = 1;
		rep(i, n)
		{
			int t = times[i];
			while (sz(waiting) && waiting.front().first <= t)
			{
				int u = waiting.front().second;
				waiting.pop();
				slots[u]++;
				if (!active.count(u)) active.insert(u);
			}
			if (active.empty())
			{
				possible = 0;
				break;
			}
			int u = *begin(active);
			slots[u]--;
			waiting.emplace(t + 1000, u);
			if (slots[u] == 0) active.erase(u);
		}
		if (possible) hi = mid;
		else lo = mid;
	}
	cout << hi;

	return 0;
}
