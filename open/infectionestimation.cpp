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
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();

	int totpop = int(1e7);
	int p = int(5e6);
	vi points = { 200, 400, 802, 1600, 3210, 6400, 12842, 25000, 51370, 102740, 205482, 410964, 821930, 1643860, 3287722 };
	

	/*repp(i, 100, p + 1)
	{
		bool good = 0;
		repe(t, points) good |= (t <= 2 * i && t >= (i+0.)/2);
		assert(good);
	}*/
	vector<pair<int,double>> prob;
	repe(p, points) prob.emplace_back(p, 1.0 / sz(points));

	auto probyes = [totpop](int samplesize, int numinfected)
	{
		double probinfected = (numinfected + 0.) / totpop;
		double probuninfected = 1 - probinfected;
		double probnoinfectedchosen = pow(probuninfected, samplesize);
		return 1 - probnoinfectedchosen;
	};
	auto probno = [totpop](int samplesize, int numinfected)
	{
		double probinfected = (numinfected + 0.) / totpop;
		double probuninfected = 1 - probinfected;
		return pow(probuninfected, samplesize);
	};

	vi questions = { 1, 5, 10 };
	repe(p, prob) questions.emplace_back(p.first);

	rep(i, 50)
	{
		int besta;
		double closest = 1000;
		repe(a, questions)
		{
			double yesp = 0;
			repe(p, prob)
			{
				yesp += p.second * probyes(a, p.first);
			}
			if (abs(yesp-0.5)<abs(closest-0.5))
			{
				closest = yesp;
				besta = a;
			}
		}
		cerr << "yesp: " << closest << endl;
		cout << "test " << besta << endl;
		int res;
		cin >> res;

		repe(p, prob)
		{
			if (res)
			{
				p.second *= probyes(besta, p.first);
			}
			else
			{
				p.second *= probno(besta,p.first);
			}
		}
		double s = 0;
		repe(p, prob) s += p.second;
		repe(p, prob) p.second *= 1 / s;
	}

	int best = 0;
	rep(i, sz(prob)) if (prob[i].second > prob[best].second)best = i;
	cout << "estimate " << prob[best].first << endl;

	return 0;
}
