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


int main()
{
	string number;
	read(number);

	int age = number[1]-'0'+(number[0]-'0')*10;

	if (number.find("+")!=string::npos)
	{
		if (age < 20)
		{
			number = "19" + number;
		}
		else
		{
			number = "18" + number;
		}

		number.erase(std::remove(number.begin(), number.end(), '-'), number.end());
		number.erase(std::remove(number.begin(), number.end(), '+'), number.end());

		write(number);
	}
	else
	{
		if (age < 20)
		{
			number = "20" + number;
		}
		else
		{
			number = "19" + number;
		}

		number.erase(std::remove(number.begin(), number.end(), '-'), number.end());


		write(number);
	}
}