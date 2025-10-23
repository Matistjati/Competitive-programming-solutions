#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vector<string> words(n);
	repe(w, words) cin >> w;
	reverse(all(words));

	string vowels = "aeiouy";
	auto is_consonant = [&](char c)
	{
		return find(all(vowels),c) == vowels.end();
	};
	repe(w, words)
	{
		vi del(sz(w));
		rep(i, sz(w)-2)
		{
			if (!is_consonant(w[i]) && is_consonant(w[i + 1]) && is_consonant(w[i + 2])) del[i] = 1;
		}

		for (int i = sz(w) - 1; i >= 0; i--) if (!del[i]) cout << w[i];
		cout << " ";
	}

	return 0;
}
