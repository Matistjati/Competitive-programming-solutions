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

bool compare(const pair<int, int>& first, const pair<int, int>& second)
{
	return first.first <= second.first;
}

int n_pairs(vector<int> firstx, vector<int> firsty, vector<int> secondx, vector<int> secondy)
{
	int n_pair = 0;
	rep(i, firstx.size())
	{
		int target = firstx[i];
		auto lower = lower_bound(secondx.begin(), secondx.end(), target);
		int index = lower - secondx.begin();

		if (index < 0)
		{
			continue;
		}

		for (int j = index; j < secondx.size(); j++)
		{
			if (secondx[j] != target)
			{
				break;
			}

			if (firsty[i] == -secondy[j])
			{
				n_pair++;
			}
		}

	}

	return n_pair;
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


	//firstPairs.clear();
	//secondPairs.clear();
	//firstPairs.push_back({ 0, 0 });
	//firstPairs.push_back({ 0, 0 });

	////firstPairs.push_back({ 3,2 });

	//secondPairs.push_back({ 0,0 });
	//secondPairs.push_back({ 0,0 });
	//secondPairs.push_back({ -2,-1 });
	//secondPairs.push_back({ -2,-2 });
	//secondPairs.push_back({ -3,-1 });
	//secondPairs.push_back({ -3,-2 });
	//secondPairs.push_back({ -3,-3 });
	//secondPairs.push_back({ -4,-1 });
	//secondPairs.push_back({ -4,-2 });

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

	/*
	vector<int> secondFirst;
	vector<int> secondSecond;
	rep(i, secondPairs.size())
	{
		secondFirst.push_back(secondPairs[i].first);
		secondSecond.push_back(secondPairs[i].second);
	}

	rep(i, firstPairs.size())
	{
		if (firstPairs[i].first == 0 && firstPairs[i].second == 0)
		{
			n_subsets++;
			continue;
		}

		int target = firstPairs[i].first * -1;

		auto correct = lower_bound(secondFirst.begin(), secondFirst.end(), target);
		int index = correct - secondFirst.begin();

		if (index < 0)
		{
			continue;
		}

		while (true)
		{
			pair<int, int> curr = {secondFirst[index],secondSecond[index]};
			if (curr.first != -firstPairs[i].first)
			{
				break;
			}
			int sumY = curr.second + firstPairs[i].second;
			if (sumY == 0)
			{
				n_subsets++;
			}

			index += 1;
			if (index > secondPairs.size() - 1)
			{
				break;
			}
		}*/

		/*rep(j, secondPairs.size())
		{
			int sumX = secondPairs[j].first + firstPairs[i].first;
			int sumY = secondPairs[j].second + firstPairs[i].second;
			if (sumX == 0 && sumY == 0)
			{
				n_subsets++;
			}
			else if (sumX > 0 && sumY > 0)
			{
				break;
			}
		}*/

	write(n_subsets);
}
