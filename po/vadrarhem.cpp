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
	int n;
	int m;
	read(n);
	read(m);
	vector<pair<int, int>> beds;
	rep(i, m)
	{
		int a;
		int b;
		read(a);
		read(b);
		beds.push_back({ a,b });
	}
	sort(beds.begin(), beds.end(), [](const pair<int, int>& lhs, const pair<int, int>& rhs)
		{
			return lhs.first < rhs.first;
		});

	int cost = 0;
	repe(bed, beds)
	{
		if (n > bed.second)
		{
			n -= bed.second;
			cost += bed.first * bed.second;
		}
		else
		{
			cost += bed.first * n;
			n -= n;
		}
		if (n == 0)
		{
			break;
		}
	}
	write(cost);
}