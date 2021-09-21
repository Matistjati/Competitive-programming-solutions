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
#define setcontains(set, x) set.find(x) != set.end()
#define notsetcontains(set, x) set.find(x) == set.end()

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto const& i : container)
#define inf 1e9

void make_query(set<int>& nums, vector<int>& queries)
{
	rep(i, queries.size())
	{
		int query = queries[i];

		int upper = inf;
		auto upper_ptr = nums.lower_bound(query);
		if (upper_ptr != nums.end())
		{
			upper = *upper_ptr;
		}
		auto lower_ptr = (nums.lower_bound(query));

		int lower = inf;
		lower_ptr = prev(lower_ptr);
		if (lower_ptr != nums.end())
		{
			lower = *lower_ptr;
		}



		int best = -1;
		if (abs(query-upper) < abs(query-lower))
		{
			best = upper;
		}
		else
		{
			best = lower;
		}

		cout << "Closest sum to " << query << " is " << best << "." << endl;
	}
}

int main()
{



	int case_n = 1;
	int n;
	while (cin >> n)
	{

		vector<int> nums(n);
		for (int& num : nums)
		{
			cin >> num;
		}

		set<int> sumSet;
		rep(i, n)
		{
			rep(j, n)
			{
				if (i == j)
				{
					continue;
				}

				sumSet.insert(nums[i] + nums[j]);
			}
		}
		int m;
		cin >> m;
		vector<int> queries;
		rep(i, m)
		{
			readpush(int, queries);
		}
		cout << "Case " << case_n << ":" << endl;
		case_n++;
		make_query(sumSet, queries);
	}
}