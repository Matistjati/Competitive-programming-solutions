#include <bits/stdc++.h>
#include <bits/extc++.h>
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

const int mod = int(1e9 + 7);

void solve()
{
	int n, k;
	cin >> n >> k;


	p2 state = p2(1, 1);
	if (k == 1)
	{
		if (n == 1)
		{
			cout << 1 << "\n";
			return;
		}
		if (n == 2)
		{
			cout << 2 << "\n";
			return;
		}
		n -= 2;
	}
	int ans = 2;
	repp(i, 2, k*10)
	{
		ans++;
		int f = state.first + state.second;
		f %= k;
		if (f == 0)
		{
			n--;
			if (n == 0)
			{
				cout << ans << "\n";
				return;
			}
		}
		state.second = state.first;
		state.first = f;
		int h = state.first * int(1e6) + state.second;
	}

	vi cycle;
	p2 start = state;
	do
	{
		int f = state.first + state.second;
		f %= k;
		cycle.push_back(f);
		state.second = state.first;
		state.first = f;
	} while (state!=start);
	int numzero = 0;
	rep(i, sz(cycle)) numzero += cycle[i] == 0;

	if (n>numzero)
	{
		int num_fullcycle = (n-numzero) / numzero;
		n -= numzero * num_fullcycle;
		num_fullcycle %= mod;
		ans += num_fullcycle * sz(cycle);
	}
	

	while (n)
	{
		int f = state.first + state.second;
		f %= k;
		ans++;
		if (f == 0) n--;
		state.second = state.first;
		state.first = f;
	}
	cout << ans%mod << "\n";

}

signed main()
{
	fast();

	int t;
	cin >> t;
	auto start = chrono::high_resolution_clock::now();
	while (t--)
	{
		solve();
	}

	return 0;
}
