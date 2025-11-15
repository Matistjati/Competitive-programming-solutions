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

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	string line;
	getline(cin, line);

	deque<char> s(all(line));
	auto next_parenthesis_index = [&]() // read one testcase
		{
			s.pop_front();
			string index;
			while (isdigit(s.front())) {
				index += s.front();
				s.pop_front();
			}
			s.pop_front(); // , or )
			if (index.empty()) {
				return make_pair(-1, string(1,'-'));
			}
			string moves;
			while (s.front() == 'L' || s.front() == 'R') {
				moves += s.front();
				s.pop_front();
			}
			s.pop_front();
			return make_pair(stoi(index), moves);
		};

	auto read_testcase = [&]()
		{
			if (s.empty()) exit(0);
			vector<pair<int, string>> seqs;
			while (true)
			{
				auto [index, path] = next_parenthesis_index();
				if (s.empty()) break;
				s.pop_front();
				if (index == -1) break;
				seqs.emplace_back(index, path);
			}
			return seqs;
		};

	auto die = []()
		{
			cout << "incomplete\n";
		};

	auto solve = [&]()
		{
			vector<pair<int, string>> seqs = read_testcase();
			sort(all(seqs), [](pair<int, string>& a, pair<int, string>& b)
				{
					if (sz(a.second)!=sz(b.second)) return sz(a.second) < sz(b.second);
					return a.second < b.second;
				});
			vector<p2> children(256, p2(-1, -1));
			vi ans;
			if (seqs[0].second != "") return die();
			ans.push_back(seqs[0].first);
			map<string, int> seen;
			seen[""] = 0;
			repp(i, 1, sz(seqs))
			{
				auto [index, moves] = seqs[i];
				ans.push_back(index);
				string c = moves;
				c.pop_back();
				if (!seen.count(c)) return die();
				seen[moves] = sz(seen);
				int my_ind = seen[moves];
				if (moves.back()=='L')
				{
					children[seen[c]].first = my_ind;
				}
				else
				{
					children[seen[c]].second = my_ind;
				}
			}

			repe(v, ans) cout << v << " ";
			cout << '\n';
		};

	while (true)
	{
		solve();
	}

	return 0;
}
