
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <iterator>

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)

#define rep(i, high) for (ll i = 0; i < high; i++)


void solve(int n)
{
	vector<string> students;
	map<string, set<string>> hated;
	map<string, int> studentToId;
	rep(i, n)
	{
		readpush(string, students);
		hated[temp] = set<string>();
	}

	int m;
	read(m);

	rep(i, m)
	{
		string a;
		string b;
		read(a);
		read(b);
		hated[a].insert(b);
		hated[a].insert(a);
		hated[b].insert(b);
		hated[b].insert(a);
	}

	map<string, set<string>> okPeople;
	set<string> studentSet = set<string>(students.begin(), students.end());

	rep(i, students.size())
	{
		string student = students[i];
		okPeople[student] = set<string>();
		set_difference(studentSet.begin(), studentSet.end(), hated[student].begin(), hated[student].end(), inserter(okPeople[student], okPeople[student].end()));
	}

	sort(students.begin(), students.end());

	rep(i, students.size())
	{
		studentToId[students[i]] = i;
	}

	vector<vector<bool>> edges;
	edges.resize(n, vector<bool>(n, false));

	for (const auto& x: okPeople)
	{
		for (const auto& ok: x.second)
		{
			edges[studentToId[x.first]][studentToId[ok]] = true;
			edges[studentToId[ok]][studentToId[x.first]] = true;
		}
	}


	vector<int> intStudents;
	rep(i, students.size())
	{
		intStudents.push_back(i);
	}

	bool foundValid = false;
	do
	{
		bool valid = true;
		rep(i, intStudents.size()-1)
		{
			if (!edges[intStudents[i]][intStudents[i+1]])
			{
				valid = false;
				break;
			}
		}
		if (valid)
		{
			foundValid = true;
			break;
		}

	} while (next_permutation(intStudents.begin(), intStudents.end()));


	if (!foundValid)
	{
		write("You all need therapy.");
	}
	else
	{
		rep(i, intStudents.size())
		{
			std::cout << students[intStudents[i]] << " ";
		}
		std::cout << endl;
	}

}

int main()
{
	int n;
	while (cin >> n)
	{
		solve(n);
	}
}