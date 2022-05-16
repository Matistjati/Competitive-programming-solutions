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
	map<int, int> n_segments = { {0,6},{1,2},{2,5},{3,5},{4,4},{5,5},{6,6},{7,3},{8,7},{9,6} };

	vector<int> times;

	int h = 0;
	int sec = 0;
	int m = 0;
	rep(hoursFirst, 3)
	{
		rep(hourSecond, 10)
		{
			h++;
			if (hoursFirst*10+hourSecond>23)
			{
				break;
			}
			rep(minuteFirst, 6)
			{
				rep(minuteSecond, 10)
				{
					m++;
					rep(secondFirst, 6)
					{
						rep(secondSecond, 10)
						{
							sec++;
							times.push_back(n_segments[hoursFirst]+ n_segments[hourSecond]+ n_segments[minuteFirst]+ n_segments[minuteSecond]+ n_segments[secondFirst]+ n_segments[secondSecond]);
						}
					}
				}
			}
		}
	}

	set<int> prefixSumSet;
	vector<int> prefixSum;
	int s = 0;
	rep(i, times.size())
	{
		s += times[i];
		prefixSum.push_back(s);
		prefixSumSet.insert(s);
	}

	int t;
	read(t);

	int occurences = 0;

	rep(i, prefixSum.size())
	{
		if (prefixSum[i] == t)
		{
			occurences++;
		}
		if (setcontains(prefixSumSet, prefixSum[i]-t))
		{
			occurences++;
		}
	}

	write(occurences);
}