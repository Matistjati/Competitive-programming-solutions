
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <iterator>

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)

#define rep(i, high) for (ll i = 0; i < high; i++)

int value(vector<pair<int, int>> ingredients, int i, vector<bool> chosen, bool enabled)
{
	chosen[i] = enabled;

	if (i == ingredients.size() - 1)
	{
		int bittervalue = 0;
		int sourvalue = 1;
		bool any = false;
		rep(j, ingredients.size())
		{
			if (chosen[j])
			{
				any = true;
				sourvalue *= ingredients[j].first;
				bittervalue += ingredients[j].second;
			}
		}
		if (!any)
		{
			return 1e7;
		}
		return abs(sourvalue-bittervalue);
	}

	

	int truediff = value(ingredients, i + 1, chosen, true);
	int falsediff = value(ingredients, i + 1, chosen, false);

	return min(truediff, falsediff);
}

int main()
{
	int n;
	read(n);
	vector<pair<int, int>> ingredients;
	vector<bool> chosen;
	rep(i, n)
	{
		int a;
		int b;
		read(a);
		read(b);
		ingredients.push_back({ a,b });
		chosen.push_back(false);
	}

	write(min(value(ingredients,0,chosen,true), value(ingredients, 0, chosen, false)));
}