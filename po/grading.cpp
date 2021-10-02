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
	int a;
	int b;
	int c;
	int d;
	int e;
	int grade;
	read(a);
	read(b);
	read(c);
	read(d);
	read(e);
	read(grade);
	if (grade >= a)
	{
		write("A");
	}
	else if (grade >= b)
	{
		write("B");
	}
	else if (grade >= c)
	{
		write("C");
	}
	else if (grade >= d)
	{
		write("D");
	}
	else if (grade >= e)
	{
		write("E");
	}
	else
	{
		write("F");
	}
}