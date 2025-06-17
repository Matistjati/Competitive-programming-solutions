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
#define repe(i, container) for (auto const& i : container)
#define inf 1e9

void allsums(int n, vector<pair<int, int>>& pairs, pair<int, int> value, vector<pair<int, int>>& finalPairs)
{
	if (n == pairs.size())
	{
		finalPairs.push_back(value);
		return;
	}

	pair<int, int> added = value;
	value.first += pairs[n].first;
	value.second += pairs[n].second;

	allsums(n + 1, pairs, value, finalPairs);
	allsums(n + 1, pairs, added, finalPairs);
}

int main()
{
	int n;
	read(n);

	vector<pair<int, int>> pairs;

	rep(i, n)
	{
		int a;
		int b;
		read(a);
		read(b);

		pairs.push_back({ a,b });
	}

	vector<pair<int, int>> firstPairs;
	vector<pair<int, int>> firstHalf;
	rep(i, pairs.size() / 2)
	{
		firstHalf.push_back(pairs[i]);
	}
	allsums(0, firstHalf, { 0,0 }, firstPairs);


	vector<pair<int, int>> secondPairs;
	vector<pair<int, int>> secondHalf;
	for (int i = pairs.size() / 2; i < pairs.size(); i++)
	{
		secondHalf.push_back(pairs[i]);
	}
	allsums(0, secondHalf, { 0,0 }, secondPairs);

	int num_zero = 0;
	int zero_index = -1;
	rep(i, firstPairs.size())
	{
		if (firstPairs[i].first == 0 && firstPairs[i].second == 0)
		{
			num_zero += 1;
			zero_index = i;
		}
	}

	firstPairs.erase(next(firstPairs.begin(), zero_index));

	rep(i, secondPairs.size())
	{
		if (secondPairs[i].first == 0 && secondPairs[i].second == 0)
		{
			num_zero += 1;
			zero_index = i;
		}
	}

	secondPairs.erase(next(secondPairs.begin(), zero_index));

	map<pair<int, int>, int> firstSet;
	map<pair<int, int>, int> secondSet;
	ll n_subsets = 0;

	rep(i, firstPairs.size())
	{
		if (firstPairs[i].first == 0 && firstPairs[i].second == 0)
		{
			n_subsets++;
		}
		firstSet[firstPairs[i]]++;
	}

	rep(i, secondPairs.size())
	{
		if (secondPairs[i].first == 0 && secondPairs[i].second == 0)
		{
			n_subsets++;
		}
		secondSet[secondPairs[i]]++;
	}

	repe(coord, firstSet)
	{
		pair<int, int> target = { -coord.first.first,-coord.first.second };

		if (secondSet.find(target) != secondSet.end())
		{
			n_subsets += secondSet[target]*coord.second;
		}
	}

	write(n_subsets);
}