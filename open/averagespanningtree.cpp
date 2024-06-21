#include <bits/stdc++.h>
using namespace std;

#define enablell 1

typedef long long ll;
#if enablell
#define int ll
#endif

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;
typedef vector<p2> vp2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

#define _LOCAL _MSC_VER > 0
#if _LOCAL

#define popcount(x) __popcnt(x)
#else
#define popcount(x) __builtin_popcountll(x)
#endif


#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())


random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]


double det(vector<vector<double>>& a) {
	int n = sz(a); double res = 1;
	repp(i, 0, n) {
		int b = i;
		repp(j, i + 1, n) if (fabs(a[j][i]) > fabs(a[b][i])) b = j;
		if (i != b) swap(a[i], a[b]), res *= -1;
		res *= a[i][i];
		if (res == 0) return 0;
		repp(j, i + 1, n) {
			double v = a[j][i] / a[i][i];
			if (v != 0) repp(k, i + 1, n) a[j][k] -= v * a[i][k];
		}
	}
	return res;
}

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

double countspanningtrees(vp2 edgelist, int n, int m)
{
	vector<vector<double>> laplace(n - 1, vector<double>(n - 1));
	vi deg(n);
	repe(e, edgelist) deg[e.first]++, deg[e.second]++;
	rep(i, n - 1)
	{
		laplace[i][i] = deg[i];
	}
	repe(e, edgelist)
	{
		int a, b;
		tie(a, b) = e;
		if (a == n - 1 || b == n - 1) continue;
		laplace[a][b]--;
		laplace[b][a]--;
	}

	double detv = det(laplace);
	return detv;
}

double totalweight(vp2 edgelist, vi weights, int n, int m)
{
	double tot = 0;
	rep(j, edgelist.size())
	{
		p2 t = edgelist[j];
		vp2 newedge;
		repe(e, edgelist)
		{
			p2 v = e;
			if (v == t) continue;
			if (v.second == t.second) v.second = t.first;
			if (v.first == t.second) v.first = t.first;
			if (v.second > t.second)v.second--;
			if (v.first > t.second)v.first--;
			newedge.push_back(v);
		}
		double num_spanning = countspanningtrees(newedge, n - 1, newedge.size());
		tot += weights[j] * num_spanning;
	}
	return tot;
}

signed main()
{
	int n, m;
	cin >> n >> m;
	vp2 edgelist;
	vi weights;
	rep(i, m)
	{
		int a, b, w;
		cin >> a >> b >> w;
		a--; b--;
		edgelist.emplace_back(a, b);
		weights.push_back(w);
	}

	cout << fixed << setprecision(15) << totalweight(edgelist, weights, n, m) / countspanningtrees(edgelist, n, m) << endl;



	return 0;
}
