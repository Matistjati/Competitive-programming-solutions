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
	int r;
	int k;
	read(r);
	read(k);
	vector<vector<int>> heights;
	rep(i, r)
	{
		vector<int> row;
		rep(j, k)
		{
			readpush(int, row);
		}
		heights.push_back(row);
	}
	int n_seen = 0;
	int y_minus = 0;
	int x_minus = 0;
	int z_minus = 0;
	rep(x, r)
	{
		rep(z, k)
		{
			for(int y = 1; y <= heights[x][z]; y++)
			{
				int n = 6;
				if (y > 1)
				{
					n--;
					y_minus++;
				}
				if (y < heights[x][z])
				{
					n--;
					y_minus++;
				}
				if (x - 1 >= 0)
				{
					if (heights[x - 1][z] >= y)
					{
						n--;
						x_minus++;
					}
				}
				if (x + 1 < r)
				{
					if (heights[x + 1][z] >= y)
					{
						n--;
						x_minus++;
					}
				}
				if (z + 1 < k)
				{
					if (heights[x][z+1] >= y)
					{
						n--;
						z_minus++;
					}
				}
				if (z - 1 >= 0)
				{
					if (heights[x][z - 1] >= y)
					{
						n--;
						z_minus++;
					}
				}
				n_seen += n;
			}

		}
	}
	write(n_seen);
}