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
#define assert(x) if (!(x)) __debugbreak()
#endif

typedef bitset<501> bset;
typedef tuple<int, vi, vi, bset> team;
struct compare {
	bool operator()(const team& a, const team& b)
	{
		return get<0>(a) < get<0>(b);
	}

};


signed main()
{
	fast();

	int n, k, c;
	cin >> n >> k >> c;

	vvi strength(n, vi(k));
	rep(i, n)
	{
		rep(j, k)
		{
			cin >> strength[i][j];
		}
	}

	priority_queue<team, vector<team>, compare> teams;
	vi start;
	rep(j, k)
	{
		int best = 0;
		int bestv = -1;
		rep(i, n)
		{
			if (strength[i][j] > bestv && find(all(start), i) == start.end())
			{
				best = i;
				bestv = strength[i][j];
			}
		}
		start.push_back(best);
	}

	auto getsum = [&](vi& team, vi& team2)
	{
		vi best(k, 0);
		repe(v, team)
		{
			rep(j, k)
			{
				best[j] = max(best[j], strength[v][j]);
			}
		}
		repe(v, team2)
		{
			rep(j, k)
			{
				best[j] = max(best[j], strength[v][j]);
			}
		}
		return accumulate(all(best), 0LL);
	};

	vi forced;
	teams.emplace(getsum(start, forced), start, forced, bset());

	rep(it, c - 1)
	{
		int s;
		vi curr, forced;
		bset banned;
		tie(s, curr, forced, banned) = teams.top();
		teams.pop();

		while (curr.size())
		{
			vi newcurr(curr);
			bset newbanned(banned);
			newbanned[newcurr.back()] = 1;
			newcurr.pop_back();
			int bestv = -1;
			int best = -1;
			rep(j, n)
			{
				if (find(all(newcurr), j) == newcurr.end() && !newbanned[j])
				{
					newcurr.push_back(j);
					if (getsum(newcurr, forced) > bestv)
					{
						best = j;
						bestv = getsum(newcurr, forced);
					}
					newcurr.pop_back();
				}
			}
			if (best == -1) break;
			newcurr.push_back(best);

			teams.emplace(getsum(newcurr, forced), newcurr, forced, newbanned);
			banned[curr.back()] = 1;
			forced.push_back(curr.back());
			curr.pop_back();
		}
	}

	cout << get<0>(teams.top());

	return 0;
}