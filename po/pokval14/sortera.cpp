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

	vector<int> nums;
	rep(i, n)
	{
		readpush(int, nums);
	}

	bool sorted = false;
	int n_swaps = 0;
	while (!sorted)
	{
		sorted = true;

		rep(i, n-1)
		{
			if (nums[i] > nums[i+1])
			{
				n_swaps++;
				swap(nums[i], nums[i + 1]);
				sorted = false;
			}
		}
	}

	write(n_swaps);
}