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

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


struct state
{
	int cost;
	p2 prev;
};

static constexpr state unit = state({ -inf,p2(-1,-1) });

inline state merge(const state& a, const state& b)
{
	if (a.cost > b.cost) return move(a);
	return move(b);
}

struct FT {
	vector<state> s;
	FT(int n) : s(n) {}
	void update(int pos, state dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] = merge(s[pos], dif);
	}
	state query(int pos) { // sum of values in [0, pos)
		state res = unit;
		for (; pos > 0; pos &= pos - 1) res = merge(res, s[pos - 1]);
		return res;
	}
};

struct cmp
{
	bool operator()(const  p2& l, const p2& r) const
	{
		return l.second > r.second;
	}
};

signed main()
{
	fast();

	int n, k;
	cin >> n >> k;
	vi nums(n);
	rep(i, n) cin >> nums[i];
	rep(i, n) nums[i]--;

	vector<vector<state>> dp(2, vector<state>(n));



	vi disabled(n);
	multiset<p2, cmp> backedges;
	int ans = 0;

	FT top(0);
	rep(_, 4)
	{
		rep(i, n) dp[0][i] = state({ 0, p2(i, 0) });
		rep(i, n) dp[1][i] = state({ 0, p2(i, 1) });

		bool any = 1;
		while (any)
		{
			any = 0;

			top = FT(n);
			rep(i, n)
			{
				state best = top.query(nums[i]-k+1);

				if (best.cost > dp[0][i].cost) dp[0][i] = best;


				if (!disabled[i] && dp[0][i].cost + 1 > dp[1][i].cost)
				{
					dp[1][i] = state({ dp[0][i].cost + 1, p2(i, 0) });
				}
				if (disabled[i] && dp[1][i].cost - 1 > dp[0][i].cost) dp[0][i] = state({ dp[1][i].cost - 1, p2(i, 1) });

				top.update(nums[i], state({ dp[1][i].cost, p2(i,1) }));
			}

			repe(b, backedges)
			{
				if (dp[1][b.second].cost < dp[0][b.first].cost)
				{
					dp[1][b.second] = state({ dp[0][b.first].cost, p2(b.first,0) });
					if (dp[1][b.second].cost - 1 > dp[0][b.second].cost) dp[0][b.second] = state({ dp[1][b.second].cost - 1, p2(b.second, 1) });
					any = 1;
				}
			}
		}

		int best = 0;
		rep(i, n)
		{
			if (dp[1][i].cost > dp[1][best].cost) best = i;
		}
		// found no augmenting path
		if (dp[1][best].cost < 0)
		{
			break;
		}
		ans += dp[1][best].cost;

		p2 pos = p2(best, 1);
		while (1)
		{
			p2 from = dp[pos.second][pos.first].prev;
			if (pos == from) break;
			p2 to = pos;
			if (from.first == to.first)
			{
				if (from.second == 0)
				{
					disabled[from.first] = 1;
				}
				else disabled[from.first] = 0;
			}
			else
			{
				if (to.first > from.first)
				{
					backedges.emplace(to.first, from.first);
				}
				else backedges.erase(backedges.find(p2(from.first, to.first)));
			}
			if (pos == from) break;
			pos = from;
		}
	}
	cout << ans << "\n";



	return 0;
}

