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

map<int, int> maxocc;
map<int, int> hv;
map<vi, int> whichp;
vi hashval;
vector<int> from_hashval(int(5e7));
vvi partitions;
vvi transitions;
vi pscore;
int n, m;

void generate_partitions(vi& part, int s)
{
	if (s == n)
	{
		map<int, int> occ;
		repe(u, part) occ[u]++;
		repe(o, occ) maxocc[o.first] = max(maxocc[o.first], o.second);
		whichp[part] = sz(partitions);
		int score = 0;
		repe(u, part) score += u == 1;
		pscore.push_back(score);
		partitions.push_back(part);
		return;
	}
	if (s > n) return;

	int lo = sz(part) ? part.back() : 1;
	repp(i, lo, n + 1)
	{
		part.push_back(i);
		generate_partitions(part, s + i);
		part.pop_back();
	}
}

vi howmany;
int dp[11][5700];

int dp2[32][32][5700];
int dp2ver = 10;
int multiplier = 35;
inline int weird_hash(int x) {
	x = x ^ (x >> 16);
	x = x * multiplier;
	x = x ^ (x >> 16);

	return (x & 0x7FFFFFFF) % sz(from_hashval);
}

void generate_transitions(int splits, int lo, int p, vi& transitions)
{
	int pdp = from_hashval[weird_hash(p)];
	if (dp2[splits][lo][pdp] == dp2ver) return;
	dp2[splits][lo][pdp] = dp2ver;
	if (splits == 0) transitions[pdp] = 1;

	vi& part = partitions[pdp];
	if (!binary_search(all(part), lo))
	{
		auto it = lower_bound(all(part), lo);
		if (it != part.end()) generate_transitions(splits, *it, p, transitions);
		return;
	}
	auto it = lower_bound(all(part), lo);
	auto it_larger = upper_bound(all(part), lo);

	int c = count(all(part), lo);
	rep(i, c + 1) if (splits - i * lo >= 0)
	{
		if (it_larger != part.end()) generate_transitions(splits - i * lo, *it_larger, p, transitions);
		else generate_transitions(splits - i * lo, 31, p, transitions);
	}

	repp(i, 1, *it)
	{
		if (i > splits) break;
		int newp = p;
		newp -= hv[*it];
		newp += hv[i];
		newp += hv[*it - i];

		generate_transitions(splits - i, lo, newp, transitions);
	}
}

int best(int i, int partition)
{
	int& v = dp[i][partition];
	if (v != -1) return v;

	if (i == m)
	{
		return pscore[partition];
	}
	int ret = 0;

	dp2ver++;
	vi transitions(sz(partitions));

	generate_transitions(howmany[i], 1, hashval[partition], transitions);
	vi tr;
	rep(t, sz(transitions))
	{
		if (transitions[t]) tr.push_back(t);
	}
	repe(t, tr)
	{
		ret = max(ret, best(i + 1, t));
	}

	return v = ret;
}

signed main()
{
	fast();
	memset(dp, -1, sizeof(dp));
	memset(dp2, 0, sizeof(dp2));

	cin >> n >> m;
	howmany.resize(m);
	rep(i, m) cin >> howmany[i];
	vi part;
	generate_partitions(part, 0);
	int p = 1;
	repe(o, maxocc)
	{
		hv[o.first] = p;
		p *= o.second + 1;
	}


	repe(p, partitions)
	{

		int h = 0;
		map<int, int> occ;
		repe(u, p) occ[u]++;
		repe(o, occ) h += o.second * hv[o.first];
		if (from_hashval[weird_hash(h)] != 0)
		{
			assert(0);
		}
		from_hashval[weird_hash(h)] = sz(hashval);
		hashval.push_back(h);
	}

	cout << best(0, sz(partitions) - 1);

	return 0;
}
