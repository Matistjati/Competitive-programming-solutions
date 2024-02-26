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

#define _LOCAL _DEBUG
#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct change
{
	int a, b;
	int oldpar, oldxor, oldsize;
};

struct UF
{
	vector<change> updates;
	vi size;
	vi par;
	vi parity;

	UF(int n) : size(n, 1), parity(n), par(n)
	{
		rep(i, n)par[i] = i;
	}

	int find(int x) { return x == par[x] ? x : find(par[x]); }
	int getparity(int x) { return x == par[x] ? parity[x] : parity[x] ^ getparity(par[x]); }
	bool oddcycle(int a, int b)
	{
		return getparity(a) == getparity(b);
	}

	void merge(int a, int b)
	{
		if (size[find(a)] < size[find(b)]) swap(a, b);
		int childa = a;
		int childb = b;
		a = find(a); b = find(b);
		change c({ a,b,par[b],parity[b],size[a] });
		updates.push_back(c);

		if (a != b)
		{
			parity[b] = getparity(childb) ^ getparity(childa) ^ 1;
			size[a] += size[b];
			par[b] = a;
		}
	}

	void rollback()
	{
		change c = updates.back();
		updates.pop_back();
		par[c.b] = c.oldpar;
		parity[c.b] = c.oldxor;
		size[c.a] = c.oldsize;
	}
};

UF uf(0);
vector<p2> edgelist;
bool add(int i)
{
	int a, b;
	tie(a, b) = edgelist[i];
	int ret = 0;
	if (uf.find(a) == uf.find(b)) ret = uf.oddcycle(a, b);
	uf.merge(a, b);
	return ret;
};

vi rightp;
void dc(int l, int r, int hr, bool yes) // we have added edges [0,i) and (hr, M)
{
	if (l == r)
	{
		rightp[l] = (yes ? inf : hr);
		return;
	}
	int mid = (l + r) / 2;


	// left side
	// update hr
	repp(i, l, mid) add(i);

	int cnt = 0;
	int newhr = hr;
	for (int i = hr; i >= mid; i--)
	{
		cnt++;
		newhr = i;
		if (add(i))
		{
			break;
		}
	}
	rep(i, cnt) uf.rollback();
	repp(i, l, mid) uf.rollback();

	for (int i = hr, j = cnt - 1; j > 0; i--, j--) add(i);
	dc(l, mid, newhr, yes);
	rep(i, cnt - 1) uf.rollback();

	// right side
	bool newyes = yes;
	int newhl = newhr;
	repp(i, l, mid + 1) newyes |= add(i);
	dc(mid + 1, r, hr, newyes);

	repp(i, l, mid + 1) uf.rollback();

}

signed main()
{
	fast();


	int n, m, q;
	cin >> n >> m >> q;

	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		edgelist.emplace_back(a, b);
	}

	uf = UF(n);
	rightp.resize(m);
	dc(0, m - 1, m - 1, 0);

	while (q--)
	{
		int l, r;
		cin >> l >> r;
		l--; r--;

		cout << (r + 1 <= rightp[l] ? "YES" : "NO") << "\n";
	}

	return 0;
}
