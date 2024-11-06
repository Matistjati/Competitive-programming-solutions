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


signed main()
{
	fast();

	int _;
	string key;
	cin >> _ >> key;

	auto get_score = [&](string seq)
	{
		int ret = 0;
		rep(i, sz(key)) ret += seq[i] == key[i];
		return ret;
	};

	string a, b, c;
	rep(i, 1000) a += "ABC";
	rep(i, 1000) b += "BABC";
	rep(i, 1000) c += "CCAABB";

	vector<pair<int, string>> scores;
	scores.emplace_back(-get_score(a), "Adrian");
	scores.emplace_back(-get_score(b), "Bruno");
	scores.emplace_back(-get_score(c), "Goran");
	sort(all(scores));
	int best = -scores[0].first;
	cout << best << "\n";
	repe(u, scores) if (-u.first == best) cout << u.second << "\n";

	return 0;
}
