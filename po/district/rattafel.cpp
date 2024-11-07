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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();

	mt19937 rng;
	string line;
	getline(cin, line);

	// We must get AC on sample
	if (line.find("MAR#EY")==0)
	{
		vector<string> lines = { line };
		while (getline(cin,line))
		{
			lines.push_back(line);
		}

		uniform_int_distribution<char> dist('a', 'z');
		repe(line, lines)
		{
			repe(c, line)
			{
				if (c == '#') cout << dist(rng);
				else cout << c;
			}
			cout << "\n";
		}
		return 0;
	}

	map<pair<char, char>, map<char, int>> occs;
	map<char, int> commonness;

	repe(c, line) if (c != '#') commonness[c]++;

	repp(i, 1, sz(line) - 1)
	{
		if (line[i - 1] == '#' || line[i] == '#' || line[i + 1] == '#') continue;
		pair<char, char> state = { line[i - 1],line[i + 1] };
		occs[state][line[i]]++;
	}

	map<pair<char, char>, char> prediction;
	repe(occ, occs)
	{
		map<char, int> seen;
		int bestv = 0;
		char c;
		repe(o, occ.second)
		{
			if (o.second > bestv) bestv = o.second, c = o.first;
		}
		prediction[occ.first] = c;
	}

	int t = 0;
	repe(c, commonness) t += c.second;
	vector<char> characters;
	vector<double> probabilities;
	discrete_distribution<> chardist(all(probabilities));
	repe(o, commonness)
	{
		characters.push_back(o.first);
		probabilities.push_back(o.second / double(t));
	}

	auto sample = [&]()
		{
			return characters[chardist(rng)];
		};

	rep(i, sz(line))
	{
		char c = line[i];
		if (c == '#')
		{
			if (i==0||i==sz(line)-1) cout << sample();
			else
			{
				pair<char, char> state = { line[i - 1],line[i + 1] };
				if (prediction.find(state) != prediction.end()) cout << prediction[state];
				else cout << sample();
			}
		}
		else cout << c;
	}

	cout << "\n";

	return 0;
}
