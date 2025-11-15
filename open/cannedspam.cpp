#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;

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
	int p = stoi(line);
	deque<string> lastposts;

	auto check_no_consec = [](string s)
		{
			string consonants = "bcdfghjklmnpqrstvwxyz";
			rep(i, sz(s))
			{
				repp(j, i, i + 7)
				{
					if (j > sz(s)) break;
					if (find(all(consonants), s[j]) == consonants.end()) break;
					if (j == i + 6) return false;
				}
			}
			return true;
		};

	while (p--)
	{
		getline(cin, line);
        for (char& c : line) c = tolower(c);
		if (!check_no_consec(line))
		{
			cout << "no\n";
			continue;
		}
		if (find(all(lastposts),line) != lastposts.end())
		{
			cout << "no\n";
			continue;
		}
		lastposts.push_back(line);
		if (sz(lastposts) > 10) lastposts.pop_front();
		cout << "yes\n";
	}

	return 0;
}
