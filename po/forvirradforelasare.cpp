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
	vector<int> lectures;
	rep(i, n)
	{
		readpush(int, lectures);
	}

	int missed = 0;
	int extra = 0;

	for(int i = 0; i < n-1; i += 1)
	{
		if (lectures[i] < lectures[i+1])
		{
			missed += lectures[i+1] - lectures[i];
		}
		if (lectures[i] > lectures[i + 1])
		{
			extra += lectures[i] - lectures[i + 1];
		}
	}

	cout << extra << " " << missed;
}