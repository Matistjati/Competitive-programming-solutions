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

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

void solve()
{
	int n, m;
	cin >> n >> m;
	deque<int> nums;
	rep(i, n)
	{
		int x;
		cin >> x;
		nums.push_back(x);
	}

	vi order;
	string moves;
	cin >> moves;
	repe(c, moves)
	{
		if (c == 'L')
		{
			order.push_back(nums.front());
			nums.pop_front();
		}
		else
		{
			order.push_back(nums.back());
			nums.pop_back();
		}
	}

	reverse(order.begin(), order.end());
	vi answers(n);
	int ans = 1;
	rep(i, n)
	{
		ans = (ans * order[i]) % m;
		answers[i] = ans;
	}
	reverse(answers.begin(), answers.end());
	rep(i, n) cout << answers[i] << " ";
	cout << "\n";
}

signed main()
{
	fast();


	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}

	return 0;
}
