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
#include <tuple>
#include <numeric>

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define notsetcontains(set, x) set.find(x) == set.end()

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto const& i : container)
#define inf 1e9

int main()
{
	int moneys;
	read(moneys);
	int n = 0;
	while (moneys > 0)
	{
		if (moneys - 500 > -100)
		{
			moneys -= 500;
		}
		else if (moneys - 200 > -100 )
		{
			moneys -= 200;
		}
		else
		{
			moneys -= 100;
		}
		n++;
	}
	write(n);
}