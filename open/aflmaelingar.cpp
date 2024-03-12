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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int ask(vi query)
{
	repe(v, query) cout << v << " ";
	cout << endl;
	int v;
	cin >> v;
	return v;
}

signed main()
{
	fast();

	int n = 300;
	int k, q;
	cin >> k >> q;
	if (k == 2)
	{
		assert(n == q);
		vi ans(n);
		rep(i, q)
		{
			vi query(n);
			query[i] = 1;
			int resp = ask(query);
			ans[i] = resp;
		}
		rep(i, n) cout << ans[i] << " ";
		cout << endl;
	}
	if (k == 4)
	{
		vi ans(n);
		rep(i, q)
		{
			vi query(n);
			query[i * 2] = 100;
			query[i * 2 + 1] = 1;
			int resp = ask(query);
			string r = to_string(resp);
			while (r.size() < 4) r.insert(r.begin(), '0');
			ans[i * 2] = stoi(r.substr(0, 2));
			ans[i * 2 + 1] = stoi(r.substr(2, 2));
		}
		rep(i, n) cout << ans[i] << " ";
		cout << endl;
	}
	if (k == 3)
	{
		int a = 10;
		int b = 1;

		map<int, int> seen;
		bool works = 1;
		rep(av, 100) // assume we know av mod 10
		{
			rep(bv, 100)
			{
				int k = a * av + b * bv;
				string s = to_string(k);
				while (s.size() > 3) s.erase(s.begin());
				while (s.size() > 1 && s[0] == '0') s.erase(s.begin());
				int u = stoi(s);
				u -= (av % 10) * a;
				if (seen.find(u) != seen.end())
				{
					if (seen[u] != av / 10)
					{
						works = 0;
						break;
					}

				}
				seen[u] = av / 10;
			}
		}




		vi ans(n);
		vi p1(n / 3);
		vi p2(n / 3);
		vi p3(n / 3);
		rep(i, n / 3)
		{
			vi query(n);
			query[i] = 1;
			query[n / 3 * 2 + i] = 100;
			int resp = ask(query);
			string r = to_string(resp);
			while (r.size() < 3) r.insert(r.begin(), '0');
			p1[i] = stoi(r.substr(1, 2));
			p3[i] = stoi(r.substr(0, 1));
		}

		rep(i, n / 3)
		{
			vi query(n);
			query[n / 3 + i] = 1;
			query[n / 3 * 2 + i] = 10;
			int resp = ask(query);
			int orig = resp;
			resp -= p3[i] * 10;
			//p2[i] = stoi(r.substr(1, 2));
			p3[i] += 10 * seen[resp];
			rep(k, 100)
			{
				string s = to_string(p3[i] * 10 + k);
				while (s.size() > 3) s.erase(s.begin());
				if (stoi(s) == orig)
				{
					p2[i] = k;
					break;
				}
			}

		}

		repe(v, p1) cout << v << " ";
		repe(v, p2) cout << v << " ";
		repe(v, p3) cout << v << " ";
		cout << endl;
	}

	return 0;
}
