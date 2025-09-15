#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	typedef vector<string> puzzle;
	set<puzzle> vis;
	puzzle start(2);
	cin >> start[0] >> start[1];

	queue<pair<int, puzzle>> q;
	q.emplace(0, start);
	vector<p2> dirs = { {0,1},{1,0},{-1,0},{0,-1} };
	while (true)
	{
		auto [d, state] = q.front();
		q.pop();
		if (vis.count(state)) continue;
		vis.insert(state);

		if (state[0]=="12" && state[1]=="3-")
		{
			cout << d << '\n';
			return 0;
		}
		p2 hole;
		rep(i, 2) rep(j, 2) if (state[i][j] == '-') hole = p2(i, j);
		for (auto [dx, dy] : dirs)
		{
			p2 np = p2(hole.first + dx, hole.second + dy);
			if (np.first < 0 || np.first >= 2 || np.second < 0 || np.second >= 2) continue;
			puzzle copy = state;
			swap(copy[hole.first][hole.second], copy[np.first][np.second]);
			q.emplace(d + 1, copy);
		}
	}

	return 0;
}
