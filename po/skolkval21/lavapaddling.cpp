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
#define rrep(i, start) for (ll i = start; i >= 0; i--)
#define repe(i, container) for (auto const& i : container)
#define inf 1e9


int main()
{
	ll n;
	ll k;
	ll h;
	read(n);
	read(k);
	read(h);

	vector<ll> islands;
	rep(i, n-1)
	{
		ll island;
		read(island);
		island *= h;
		islands.push_back(island);
	}


	ll prevPaddles = 0;

	rrep(i, n - 2)
	{
		ll travelDistance = (islands[i] - (prevPaddles * (k - 1)));
		if (travelDistance <= 0)
		{
			continue;
		}
		else
		{
			ll required = (travelDistance / k) + (travelDistance % k != 0);
			prevPaddles += required;
		}

	}

	write(prevPaddles);
}