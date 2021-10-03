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
	read(n);

	set<set<int>> trongles;
	for(int c = 1; c <= n; c++)
	{
		for (int a = 1; a <= n; a++)
		{
			for (int b = 1; b <= n; b++)
			{
				if (c*c==a*a+b*b-a*b)
				{
					set<int> triangle({a,b,c});
					trongles.insert(triangle);
				}
			}
		}
	}
	write(trongles.size());
}