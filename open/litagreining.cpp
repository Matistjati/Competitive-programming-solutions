#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int r, g, b;
	cin >> r >> g >> b;
	if (r>max(g,b))
	{
		cout << "raudur\n";
	}
	else if (g>max(r,b))
	{
		cout << "graenn\n";
	}
	else if (b>max(r,g))
	{
		cout << "blar\n";
	}
	else if (r==g&&b<r)
	{
		cout << "gulur\n";
	}
	else if (r==b&&g<r)
	{
		cout << "fjolubleikur\n";
	}
	else if (g==b&&r<g)
	{
		cout << "blagraenn\n";
	}
	else if (r==g&&g==b&&r==0)
	{
		cout << "svartur\n";
	}
	else if (r==g&&g==b&&r==255)
	{
		cout << "hvitur\n";
	}
	else if (r==g&&g==b)
	{
		cout << "grar\n";
	}
	else
	{
		cout << "othekkt\n";
	}

	return 0;
}
