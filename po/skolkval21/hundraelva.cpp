#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <iterator>
#include <queue>

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto const& i : container)
#define inf 1e9


int main()
{
	int n;
	read(n);

	int n_moneys = 0;

	int highest = 1111111111;

	while (n > 0)
	{
		if (n - highest >= 0)
		{
			n -= highest;
			n_moneys++;
		}
		else
		{
			highest = highest / 10;
		}
	}
	write(n_moneys);
}