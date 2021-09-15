#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <iterator>

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)

#define rep(i, high) for (ll i = 0; i < high; i++)

void difference(set<int> &a, set<int> &b, set<int> &result)
{
	set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(result, result.end()));
}

int num_ingredients(int n, map<int, set<int>> hated, vector<bool> &used)
{
	if (n == used.size())
	{
		return 1;
	}

	bool hatedAny = false;
	for (const int& hate : hated[n])
	{
		if (used[hate])
		{
			hatedAny = true;
		}
	}

	int sum = 0;

	if (!hatedAny)
	{
		vector<bool> copy(used);
		copy[n] = true;
		sum += num_ingredients(n + 1, hated, copy);
	}

	sum += num_ingredients(n + 1, hated, used);

	return sum;
}

int main()
{
	int n;
	read(n);
	int m;
	read(m);

	map<int, set<int>> hated;
	map<int, set<int>> ok;

	rep(i, m)
	{
		int a;
		int b;
		read(a);
		read(b);
		a--;
		b--;

		if (!hated.count(a))
		{
			hated[a] = set<int>();
		}
		if (!hated.count(b))
		{
			hated[b] = set<int>();
		}

		hated[a].insert(b);
		hated[b].insert(a);
	}



	int sum = 0;

	vector<bool> used;
	used.resize(n, false);

	sum += num_ingredients(0, hated, used);
	write(sum);
}