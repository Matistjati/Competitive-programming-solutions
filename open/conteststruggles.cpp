#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, k;
	cin >> n >> k;
	int d, s;
	cin >> d >> s;
	int totreal = n * d;
	int tottheirs = k * s;
	if (tottheirs>totreal)
	{
		cout << "impossible\n";
	}
	else
	{
		double ans = (totreal - tottheirs) / double(n - k);
		if (ans > 100)
		{
			cout << "impossible\n";
		}
		else cout << fixed << setprecision(15) << ans << "\n";
	}

	return 0;
}
