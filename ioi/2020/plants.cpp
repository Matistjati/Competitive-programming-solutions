#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

struct Tree
{
	vector<p2> tree;
	vi lazy;
	Tree(int n) : tree(n * 4), lazy(n * 4) {}

	p2 merge(p2 a, p2 b)
	{
		if (a.first <= b.first) return a;
		return b;
	}

	void push(int x)
	{
		tree[x * 2].first += lazy[x];
		lazy[x * 2] += lazy[x];
		tree[x * 2 + 1].first += lazy[x];
		lazy[x * 2 + 1] += lazy[x];
		lazy[x] = 0;
	}

	void set(int x, int l, int r, int i, ll v)
	{
		if (l == r) return void(tree[x] = p2(v, l));
		push(x);
		int mid = (l + r) / 2;
		if (i <= mid) set(x * 2, l, mid, i, v);
		else set(x * 2 + 1, mid + 1, r, i, v);
		tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
	}

	p2 query(int x, int l, int r, int ql, int qr)
	{
		if (r<ql || l>qr) return p2(inf, 0);
		if (l >= ql && r <= qr) return tree[x];
		push(x);
		int mid = (l + r) / 2;
		return merge(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
	}

	void add(int x, int l, int r, int ql, int qr, ll amount)
	{
		if (r<ql || l>qr) return;
		if (l >= ql && r <= qr)
		{
			tree[x].first += amount;
			lazy[x] += amount;
			return;
		}
		push(x);
		int mid = (l + r) / 2;
		add(x * 2, l, mid, ql, qr, amount);
		add(x * 2 + 1, mid + 1, r, ql, qr, amount);
		tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
	}
};

struct MaxTree
{
	vector<p2> tree;
	MaxTree(int n) : tree(n * 4, p2(-inf, -1)) {}
	p2 merge(p2 a, p2 b)
	{
		if (a.first >= b.first) return a;
		return b;
	}
	void update(int x, int l, int r, int i, int v)
	{
		if (l == r) return void(tree[x] = p2(v, i));
		int mid = (l + r) / 2;
		if (i <= mid) update(x * 2, l, mid, i, v);
		else update(x * 2 + 1, mid + 1, r, i, v);
		tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
	}

	p2 query(int x, int l, int r, int ql, int qr)
	{
		if (l > qr || r < ql) return p2(-inf, -1);
		if (l >= ql && r <= qr) return tree[x];
		int mid = (l + r) / 2;
		return merge(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
	}
};


int n, k;
int dist(int a, int b)
{
	return min(abs(a - b), min(abs(a + n - b), abs(b + n - a)));
}


const int maxn = int(2e5) + 10;
int rjump[19][maxn];
int rcrosses[19][maxn];
int ljump[19][maxn];
int lcrosses[19][maxn];
vi real_heights;
void init(int K, std::vector<int> r) {
	k = K;
	n = sz(r);
	real_heights.resize(n);


	auto norm = [&](int x)
		{
			if (x < 0) x %= n, x += n;
			if (x >= n) return x % n;
			return x;
		};

	Tree tree(n);

	rep(i, n) tree.set(1, 0, n - 1, i, r[i]);

	auto find_zero = [&](int ql, int qr)
		{
			ql = norm(ql); qr = norm(qr);
			p2 q;
			if (ql <= qr) q = tree.query(1, 0, n - 1, ql, qr);
			else q = tree.merge(tree.query(1, 0, n - 1, 0, qr), tree.query(1, 0, n - 1, ql, n - 1));
			if (q.first == 0) return q.second;
			return -1LL;
		};

	auto decrease = [&](int ql, int qr)
		{
			ql = norm(ql); qr = norm(qr);
			if (ql <= qr) tree.add(1, 0, n - 1, ql, qr, -1);
			else tree.add(1, 0, n - 1, 0, qr, -1), tree.add(1, 0, n - 1, ql, n - 1, -1);
		};

	ll ind = n - 1;
	rep(i, n)
	{
		ll j = find_zero(0, n - 1);
		if (j == -1) break;
		vi st = { j };
		while (sz(st))
		{
			ll u = st.back();
			ll v = find_zero(u - k + 1, u - 1);
			if (v == -1)
			{
				st.pop_back();
				real_heights[u] = ind--;
				decrease(u - k + 1, u - 1);
				tree.set(1, 0, n - 1, u, inf);
			}
			else
			{
				st.push_back(v);
			}
		}
	}

	MaxTree maxtree(n);
	vector<p2> events;
	rep(i, n) events.emplace_back(real_heights[i], i);
	sort(all(events));

	auto find_max = [&](int l, int r)
		{
			if (l <= r) return maxtree.query(1, 0, n - 1, l, r);
			return maxtree.merge(maxtree.query(1, 0, n - 1, l, n - 1), maxtree.query(1, 0, n - 1, 0, r));
		};


	memset(ljump, -1, sizeof(ljump));
	memset(rjump, -1, sizeof(rjump));
	memset(rcrosses, 0, sizeof(rcrosses));
	memset(lcrosses, 0, sizeof(lcrosses));
	for (auto [h, i] : events)
	{
		p2 best = find_max(i, norm(i + k - 1));
		if (best.second != -1)
		{
			if (best.second < i) rcrosses[0][i] = 1;
			rjump[0][i] = best.second;
		}
		else rjump[0][i] = i;

		best = find_max(norm(i - k + 1), i);
		if (best.second != -1)
		{
			if (best.second > i) lcrosses[0][i] = 1;
			ljump[0][i] = best.second;
		}
		else ljump[0][i] = i;
		maxtree.update(1, 0, n - 1, i, h);
	}

	repp(d, 1, 19)
	{
		rep(i, n)
		{
			int mid = rjump[d - 1][i];
			rcrosses[d][i] = rcrosses[d - 1][i] + rcrosses[d - 1][mid];
			rjump[d][i] = rjump[d - 1][mid];

			mid = ljump[d - 1][i];
			lcrosses[d][i] = lcrosses[d - 1][i] + lcrosses[d - 1][mid];
			ljump[d][i] = ljump[d - 1][mid];
		}
	}

	return;
}

map<p2, int> cache;
int reachable(int a, int b)
{
	p2 s = p2(a, b);
	if (cache.count(s)) return cache[s];

	int x = a;
	if (x < b)
	{
		for (int d = 18; d >= 0; d--)
		{
			int p = rjump[d][x];
			if (p < b && rcrosses[d][x] == 0 && dist(p, b) >= k)
			{
				x = rjump[d][x];
			}
		}
	}
	else
	{
		int crosses_allowed = 1;
		for (int d = 18; d >= 0; d--)
		{
			int p = rjump[d][x];
			if (rcrosses[d][x] <= crosses_allowed && (crosses_allowed - rcrosses[d][x] == 1 || p < b) && dist(p, b) >= k)
			{
				crosses_allowed -= rcrosses[d][x];
				x = rjump[d][x];
			}
		}
	}
	while (dist(x, b) >= k && rjump[0][x] != x)
	{
		x = rjump[0][x];
	}

	if (dist(x, b) < k && real_heights[x] > real_heights[b]) return cache[s] = true;

	x = a;

	if (x > b)
	{
		for (int d = 18; d >= 0; d--)
		{
			int p = ljump[d][x];
			if (p > b && lcrosses[d][x] == 0 && dist(p, b) >= k)
			{
				x = ljump[d][x];
			}
		}
	}
	else
	{
		int crosses_allowed = 1;
		for (int d = 18; d >= 0; d--)
		{
			int p = ljump[d][x];
			if (lcrosses[d][x] <= crosses_allowed && (crosses_allowed - lcrosses[d][x] == 1 || p > b) && dist(p, b) >= k)
			{
				crosses_allowed -= lcrosses[d][x];
				x = ljump[d][x];
			}
		}
	}
	int its = 0;
	while (dist(x, b) >= k && ljump[0][x] != x)
	{
		its++;
		x = ljump[0][x];
	}
	if (dist(x, b) < k && real_heights[x] > real_heights[b]) return cache[s] = true;
	return cache[s] = false;
}


int compare_plants(int x, int y) {
	if (reachable(x, y)) return 1;
	if (reachable(y, x)) return -1;
	return 0;
}

#if _LOCAL

static int q;
static std::vector<int> r;
static std::vector<int> x;
static std::vector<int> y;
static std::vector<int> answer;
int main() {
	//ifstream in("c:/users/matis/in.txt");
	//cin.rdbuf(in.rdbuf());
	cin.tie(0)->sync_with_stdio(0);
	int n, k;
	cin >> n >> k >> q;
	r.resize(n);
	answer.resize(q);
	for (int i = 0; i < n; i++) {
		int value;
		cin >> value;
		r[i] = value;
	}
	x.resize(q);
	y.resize(q);
	for (int i = 0; i < q; i++) {
		cin >> x[i] >> y[i];
	}

	init(k, r);
	for (int i = 0; i < q; i++) {
		answer[i] = compare_plants(x[i], y[i]);
	}

	for (int i = 0; i < q; i++) {
		printf("%d\n", answer[i]);
	}

	fclose(stdout);

	return 0;
}
#endif
