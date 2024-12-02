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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Tree {
	typedef int T;
	static constexpr T unit = inf;
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e]
		e++;
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

vi contribr(vector<tuple<int, int, int>> points)
{
	sort(all(points), [](const auto& a, const auto& b) {
		if (get<1>(a) != get<1>(b)) {
			return get<1>(a) > get<1>(b);
		}
		return get<0>(a) < get<0>(b);
		});

	Tree tree(sz(points)+10);
	map<int, int> remap;
	vi lc;
	repe(inter, points)
	{
		int l, r, i;
		tie(l, r, i) = inter;
		lc.push_back(l);
	}
	sort(all(lc));
	repe(l, lc)
	{
		if (remap.find(l) == remap.end()) remap[l] = sz(remap);
	}

	vi ret(sz(points));
	repe(inter, points)
	{
		int l, r, i;
		tie(l, r, i) = inter;
		l = remap[l];
		int x = tree.query(0, l);
		if (x != inf) ret[i] += x - r;
		tree.update(l, r);
	}
	return ret;
}

vi contribl(vector<tuple<int, int, int>> points)
{
	sort(all(points), [](const auto& a, const auto& b) {
		if (get<0>(a) != get<0>(b)) {
			return get<0>(a) < get<0>(b);
		}
		return get<1>(a) > get<1>(b);
		});

	Tree tree(sz(points) + 10);
	map<int, int> remap;
	vi rc;
	repe(inter, points)
	{
		int l, r, i;
		tie(l, r, i) = inter;
		rc.push_back(r);
	}
	sort(all(rc));
	repe(r, rc)
	{
		if (remap.find(r) == remap.end()) remap[r] = sz(remap);
	}

	vi ret(sz(points));
	repe(inter, points)
	{
		int l, r, i;
		tie(l, r, i) = inter;
		r = remap[r];
		int x = tree.query(r, sz(points)+9);
		if (x != inf) ret[i] += l - (-x);
		tree.update(r, -l);
	}
	return ret;
}

void solve()
{
    int n;
    cin >> n;

	vector<tuple<int,int,int>> points;
	vi zero(n);
	map<p2, int> seen;
	rep(i, n)
	{
		int l, r;
		cin >> l >> r;
		seen[p2(l, r)]++;
		points.emplace_back(l, r, i);
	}
	rep(i, n)
	{
		int l, r,_;
		tie(l, r, _) = points[i];
		if (seen[p2(l,r)]>1)
		{
			zero[i] = 1;
		}
	}
	


	vi p1 = contribr(points);
	vi p3 = contribl(points);
	rep(i, n)
	{
		if (zero[i]) cout << "0\n";
		else cout << p1[i] + p3[i] << "\n";
	}

}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
