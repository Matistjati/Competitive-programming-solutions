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

int check(vector<int> & colors, vector<bool> & usedColors, int n, int color, int distinctColors, map<int, set<int>>& neighbours, int bestSoFar)
{
	if (distinctColors > 4 || distinctColors > bestSoFar)
	{
		return 5;
	}


	repe(neighbour, neighbours[n])
	{
		if (color == colors[neighbour])
		{
			return inf;
		}
	}

	if (n == colors.size() - 1)
	{
		return distinctColors;
	}

	int least = inf;
	for (int i = 0; i < 5; i++)
	{
		bool before = usedColors[i];
		if (!before)
		{
			distinctColors++;
		}
		usedColors[i] = true;
		colors[n + 1] = i;
		least = min(least, check(colors, usedColors, n+1, i, distinctColors, neighbours, least));

		if (!before)
		{
			distinctColors--;
		}
		colors[n + 1] = -1;
		usedColors[i] = before;

	}

	return least;
}

int how_many(int n, vector<pair<int, int>> borders)
{

	int least = inf;

	map<int, set<int>> neighbours;

	repe(border, borders)
	{
		if (notsetcontains(neighbours, border.first))
		{
			neighbours[border.first] = set<int>();
		}
		if (notsetcontains(neighbours, border.second))
		{
			neighbours[border.second] = set<int>();
		}
		neighbours[border.first].insert(border.second);
		neighbours[border.second].insert(border.first);

	}

	rep(i, 1)
	{
		vector<bool> usedColors(5, false);
		vector<int> colors(n, -1);
		colors[0] = i;
		usedColors[i] = true;
		least = min(least, check(colors, usedColors, 0, i, 1, neighbours, inf));
	}

	return least;
}

int main()
{
	int t;
	read(t);

	rep(test, t)
	{
		int c;
		int b;
		read(c);
		read(b);

		vector<pair<int, int>> borders;

		rep(i, b)
		{
			int first;
			int second;
			read(first);
			read(second);

			borders.push_back({ first,second });
		}

		int n_colors = how_many(c, borders);

		if (n_colors > 4)
		{
			write("many");
		}
		else
		{
			write(n_colors);
		}

	}

}