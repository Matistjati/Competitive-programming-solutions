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
#define per(i, high) for (int i = high-1; i >= 0; i--)

#if _MSC_VER > 0
#define deb __debugbreak();
#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
#define clz(x) _lzcnt_u32(x)
#else
#define clz(x) __builtin_clz(x)
#define deb ;
#define popcount(x) __builtin_popcountll(x)
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#ifdef _DEBUG
#define debassert(expr) if(!(expr)) deb;
#else
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]

struct query {
	int value;
	int weight;
	int index;

	bool operator<(const query& other) const {
		if (weight != other.weight) return weight < other.weight;
		return index < other.index;
	}

};

signed main()
{
	fast();

	int n, c;
	cin >> n >> c;
	vector<p2> items(n);
	rep(i, n) cin >> items[i].first;
	rep(i, n) cin >> items[i].second;

	vi ans(n);

	int maxc = int(1e9);
	vi sizes = { 0 };
	vi lazyprofit = { 0 };
	vi lazycap = { 0 };

	vector<set<query>> sets;
	sets.push_back({});
	int s = 1;
	while (s <= maxc)
	{
		sizes.push_back(s);
		sets.push_back({});
		lazyprofit.push_back(0);
		lazycap.push_back(0);
		s *= 2;
	}

	auto whichset = [&](int c)
	{
		auto it = lower_bound(all(sizes), c);
		if (*it == c) return it - sizes.begin();
		return it - sizes.begin() - 1;
	};

	auto insert = [&](query& qu)
	{
		int where = whichset(qu.weight);

		qu.value -= lazyprofit[where];
		qu.weight += lazycap[where];
		sets[where].insert(qu);
	};

	auto pop = [&](int where, auto location)
	{
		query qu = *location;
		sets[where].erase(location);
		qu.value += lazyprofit[where];
		qu.weight -= lazycap[where];
		return qu;
	};

	rep(i, n)
	{
		query qu = { 0,c,i };
		insert(qu);

		int cap = items[i].second;
		int ind = whichset(cap);

		while (sets[ind].size() && prev(sets[ind].end())->weight - lazycap[ind] >= cap)
		{
			query qu = pop(ind, prev(sets[ind].end()));
			qu.value += items[i].first;
			qu.weight -= cap;
			assert(qu.weight >= 0);
			insert(qu);
		}

		repp(j, ind + 1, sz(sizes))
		{
			lazyprofit[j] += items[i].first;
			lazycap[j] += cap;
			while (sets[j].size() && begin(sets[j])->weight - lazycap[j] < sizes[j])
			{
				query qu = pop(j, begin(sets[j]));
				assert(qu.weight >= 0);
				insert(qu);
			}
		}
	}

	rep(i, sz(sets))
	{
		set<query>& s = sets[i];
		repe(qu, s)
		{
			ans[qu.index] = qu.value + lazyprofit[i];
		}
	}

	rep(i, n)
	{
		cout << ans[i] << " ";
	}
	cout << "\n";

	return 0;
}
