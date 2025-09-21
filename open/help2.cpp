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

struct UF
{
	vi par;
	vi size;
	vector<set<string>> leafs;
	UF() {}
	void add()
	{
		par.push_back(sz(par));
		size.push_back(1);
		leafs.push_back({});
	}
	int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b)return;
		if (size[a] < size[b]) swap(a, b);
		par[b] = a;
		size[a] += size[b];
		repe(u, leafs[b]) leafs[a].insert(u);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	
	auto tokenize = [](const string& x)
		{
			vector<string> ret;
			string cur_word;
			for (char c : x)
			{
				if (c == ' ')
				{
					ret.push_back(cur_word);
					cur_word = "";
				}
				else cur_word += c;
			}
			ret.push_back(cur_word);

			return ret;
		};

	string line;
	getline(cin, line);
	int t = stoi(line);
	while (t--)
	{
		string a, b;
		getline(cin, a);
		getline(cin, b);

		vector<string> ta = tokenize(a);
		vector<string> tb = tokenize(b);

		if (sz(ta)!=sz(tb))
		{
			cout << "-\n";
			continue;
		}

		vector<string> ans(sz(ta), "");

		auto process = [&](vector<string> tokens, vector<string> o)
			{
				map<string, int> patternind;
				UF uf;
				rep(i, sz(tokens))
				{
					string t = tokens[i];
					if (t[0] != '<') continue;
					if (!patternind.count(t)) patternind[t] = sz(patternind), uf.add();

					string to = o[i];
					if (to[0] == '<')
					{
						if (!patternind.count(to)) patternind[to] = sz(patternind), uf.add();
						uf.merge(patternind[t], patternind[to]);
					}
					else
					{
						uf.leafs[uf.find(patternind[t])].insert(to);
					}
				}
				bool good = 1;
				repe(lg, uf.leafs) good &= sz(lg) <= 1;
				if (!good)
				{
					return false;
				}
				rep(i, sz(tokens))
				{
					string t = tokens[i];
					bool is_p = t[0] == '<';
					string o = ans[i];

					string forced_val = "";
					if (!is_p)
					{
						forced_val = t;
					}
					else
					{
						int u = uf.find(patternind[t]);
						if (sz(uf.leafs[u]))
						{
							forced_val = *begin(uf.leafs[u]);
						}
						else
						{
							//ans[i] = "LOL";
						}
					}

					if (sz(forced_val))
					{
						if (sz(o))
						{
							if (o != forced_val) return false;
						}
						ans[i] = forced_val;
					}
				}
				return true;
			};
		if (!process(ta, tb) || !process(tb, ta))
		{
			cout << "-\n";
			continue;
		}

		repe(u, ans)
		{
			if (u.empty()) cout << "x ";
			else cout << u << ' ';
		}
		cout << '\n';


	}

	return 0;
}
