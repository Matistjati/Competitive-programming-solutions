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

struct UF
{
	vi par;
	vi size;
	UF(int n) : par(n), size(n, 1)
	{
		rep(i, n)par[i] = i;
	}
	int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }

	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		par[b] = a;
		size[a] += size[b];
	}
};

signed main()
{
	fast();

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		UF uf(n + 1);
		map<string, int> names;
		rep(i, n)
		{
			string a, b;
			cin >> a >> b;
			if (names.find(a) == names.end()) names[a] = names.size();
			if (names.find(b) == names.end()) names[b] = names.size();
			uf.merge(names[a], names[b]);
			cout << uf.size[uf.find(names[a])] << "\n";
		}
	}

	return 0;
}
