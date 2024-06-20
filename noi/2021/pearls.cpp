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

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define __builtin_clz __lzcnt
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();

	int al, bl, k, q;
	cin >> al >> bl >> k >> q;
	string a, b;
	cin >> a >> b;

	vvi bad(26,vi(26));
	rep(i, k)
	{
		char a, b;
		cin >> a >> b;
		a -= 'a';
		b -= 'a';
		bad[a][b] = 1;
	}

	vector<string> charparts;
	rep(i, 26)
	{
		char c = i + 'a';
		charparts.push_back("");
		repe(bc, b)
		{
			if (!bad[c-'a'][bc-'a'])
			{
				charparts.back() += c;
				charparts.back() += bc;
			}
		}
	}

	vi lpref(al);
	rep(i, al) lpref[i] = sz(charparts[a[i]-'a']);
	repp(i, 1, al) lpref[i] += lpref[i - 1];

	while (q--)
	{
		int p;
		cin >> p;
		auto it = upper_bound(all(lpref), p);
		if (it != lpref.begin()) p -= *prev(it);
		cout << charparts[a[it - lpref.begin()] - 'a'][p] << "\n";
	}

	return 0;
}
