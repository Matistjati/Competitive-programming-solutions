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

ll sumrecur(vector<ll> weights, ll n, ll sum)
{
	if (sum >= 200)
	{
		return 0;
	}
	if (n == weights.size())
	{
		return sum;
	}

	return sumrecur(weights, n + 1, sum + weights[n]) + sumrecur(weights, n + 1, sum);
}

int main()
{
	ll n;
	read(n);

	vector<ll> weights(n);
	for(auto& weight : weights)
	{
		cin >> weight;
	}

 	ll tinyBaskets = (sumrecur(weights, 0, 0));

	ll sum = 0;
	repe(weight, weights)
	{
		sum += pow(2, weights.size() - 1) * weight;
	}
	write(sum-tinyBaskets);

}