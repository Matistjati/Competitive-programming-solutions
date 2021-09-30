
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <iterator>

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)

#define rep(i, high) for (ll i = 0; i < high; i++)

int main()
{
	int n;
	read(n);

	int s;
	read(s);

	int r;
	read(r);

	set<int> damagedTemp;
	set<int> reserveTemp;

	rep(i, s)
	{
		readinsert(int, damagedTemp);
	}

	rep(i, r)
	{
		readinsert(int, reserveTemp);
	}


	set<int> reserve;
	set<int> damaged;
	set_difference(damagedTemp.begin(), damagedTemp.end(), reserveTemp.begin(), reserveTemp.end(), inserter(damaged, damaged.end()));
	set_difference(reserveTemp.begin(), reserveTemp.end(), damagedTemp.begin(), damagedTemp.end(), inserter(reserve, reserve.end()));

	for (const int &x : reserve)
	{
		if (damaged.find(x - 1) != damaged.end())
		{
			damaged.erase(x - 1);
		}
		else if (damaged.find(x + 1) != damaged.end())
		{
			damaged.erase(x + 1);
		}
	}

	std::cout << damaged.size();
}