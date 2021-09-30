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

int main()
{
	int n;
	read(n);
	int m;
	read(m);

	vector<int> masks;

	rep(i, m)
	{
		int a;
		int b;
		read(a);
		read(b);
		a--;
		b--;

		masks.push_back((1 << a) + (1 << b));
	}

	int tot = 0;
	for (int i = 0; i < (1 << n); i++)
	{
		bool valid = true;
		for (const int& mask : masks)
		{
			if ((mask & i) == mask)
			{
				valid = false;
				break;
			}
		}

		if (valid)
		{
			tot++;
		}
	}

	write(tot);
}