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

vector<double> lgfact;
double lg2 = log(2);

double getprob(int t, int k)
{
	return exp(lgamma(t + 1) - lgamma(k + 1) - lgamma(t - k + 1) - t * lg2);
}

signed main()
{
	fast();

	int n, t;
	double L;
	cin >> n >> t >> L;


	auto distat = [t](int center, int p)
	{
		int finalpos = t + center;
		if (p > finalpos) return 0.;
		int diff = abs(finalpos - p);
		if (diff % 2 == 1) return 0.;
		if (diff / 2 > t) return 0.;
		double prob = getprob(t, diff / 2);
		return prob;
	};

	if (t * n <= int(3e7))
	{
		vector<double> sum(3e7);

		int center = 1e6;
		rep(i, n)
		{
			int x;
			cin >> x;
			x += center;
			repp(j, x - t - 10, x + t + 10)
			{
				sum[j] += distat(x, j);
			}
		}
		int ans = 0;
		repe(u, sum) ans += u > L;

		cout << ans;
	}
	else
	{
		if (n <= 500)
		{
			unordered_map<int, double> sum;
			sum.reserve(int(1e7));

			rep(i, n)
			{
				int x;
				cin >> x;
				repp(j, x - 25000, x + 25000)
				{
					sum[j] += distat(x, j);
				}
			}
			int ans = 0;
			repe(u, sum) ans += u.second > L;

			cout << ans;
		}
		else
		{
			int maxwidth = int(80000);
			int numevents = 500;
			vector<pair<int, double>> events;
			int pos = 0;
			double delta = maxwidth / (numevents / 2);
			auto normalize = [t](int x)
			{
				if (t % 2 == 0)
				{
					x += (x % 2);
					return x;
				}
				else
				{
					if (x % 2 == 0)x++;
					return x;
				}
			};
			rep(i, numevents / 2)
			{
				int nextp = normalize(pos + delta);
				events.emplace_back(pos, (distat(0, pos) + distat(0, nextp)) / 2);
				pos = nextp;
			}
			vector<pair<int, double>> ec(events);
			reverse(all(events));
			repe(e, events) e.first *= -1;
			events.pop_back();
			repe(e, ec) events.push_back(e);

			events.insert(events.begin(), make_pair(-inf, 0));
			vector<pair<int, double>> pevents;
			repp(i, 1, sz(events)) pevents.emplace_back(events[i].first, events[i].second - events[i - 1].second);

			const int pad = maxwidth;
			vi allpoints(n);
			rep(i, n) cin >> allpoints[i];
			auto handle = [allpoints, pevents, L, pad](int parity)
			{
				vi points;
				repe(p, allpoints) if (p % 2 == parity) points.push_back(p);
				if (points.empty()) return 0LL;

				vector<double> pref(int(1e7 + 1e6 + pad));
				repe(p, points)
				{
					repe(e, pevents)
					{
						pref[p + e.first + pad] += e.second;
					}
				}

				double t = 0;
				int ans = 0;
				repe(u, pref)
				{
					t += u;
					ans += t > L;
				}
				return ans / 2;
			};
			cout << handle(0) + handle(1);
		}
	}


	return 0;
}
