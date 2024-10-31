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



struct hashFunction
{
	size_t operator()(const vector<int>& myVector) const
	{
		std::hash<int> hasher;
		size_t answer = 0;
		for (int i : myVector)
		{
			answer ^= hasher(i) + 0x9e3779b9 +
				(answer << 6) + (answer >> 2);
		}
		return answer;
	}
};

int TOP = 0;
int BOTTOM = 1;
int FRONT = 2;
int BACK = 3;
int LEFT = 4;
int RIGHT = 5;
unordered_set<vi, hashFunction> vis;

vi normalize(vi die)
{
	vis.clear();
	queue<vi> q;
	q.emplace(die);
	while (sz(q))
	{
		vi d = q.front();
		q.pop();

		if (vis.find(d) != vis.end()) continue;
		vis.insert(d);

		// top, bottom, front, back, left and right faces
		vi rot = { d[BACK], d[FRONT], d[TOP], d[BOTTOM], d[LEFT], d[RIGHT] };
		q.emplace(rot);
		rot = { d[FRONT], d[BACK], d[BOTTOM], d[TOP], d[LEFT], d[RIGHT] };
		q.emplace(rot);
		rot = { d[TOP],d[BOTTOM],d[LEFT],d[RIGHT],d[BACK],d[FRONT] };
		q.emplace(rot);
		rot = { d[TOP],d[BOTTOM],d[RIGHT],d[LEFT],d[FRONT],d[BACK] };
		q.emplace(rot);
	}

	vi ret = *begin(vis);
	repe(u, vis)
	{
		if (u < ret) ret = u;
	}

	return ret;
}

signed main()
{
	fast();

	int n;
	cin >> n;
	vvi all_dice;
	rep(i, n)
	{
		vi die(6);
		rep(j, 6) cin >> die[j];
		all_dice.push_back(normalize(die));
	}
	sort(all(all_dice));

	int s = 1;
	int ans = 0;
	repp(i, 1, n)
	{
		if (all_dice[i]==all_dice[i-1])
		{
			s++;
		}
		else
		{
			ans = max(ans, s);
			s = 1;
		}
	}
	cout << max(ans, s);

	return 0;
}
