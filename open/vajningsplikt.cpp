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

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();

	map<string, int> dirs;
	dirs["North"] = 0;
	dirs["East"] = 1;
	dirs["South"] = 2;
	dirs["West"] = 3;

	string arr, leave, other;
	cin >> arr >> leave >> other;
	int ai, li, oi;
	ai = dirs[arr];
	li = dirs[leave];
	oi = dirs[other];

	if ((ai + 2) % 4 == li && (oi + 1) % 4 == ai)
	{
		cout << "Yes";
	}
	else if ((ai + 1) % 4 == li && ((oi + 2) % 4 == ai || (oi + 1) % 4 == ai))
	{
		cout << "Yes";
	}
	else cout << "No";

	return 0;
}
