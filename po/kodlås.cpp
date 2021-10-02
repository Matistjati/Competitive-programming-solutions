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
    ll n;
    ll m;
    read(n);
    read(m);

    vector<string> lock;

    rep(i, n)
    {
        string row;
        read(row);
        lock.push_back(row);
    }

    vector<vector<set<ll>>> opening(m, vector<set<ll>>(n, set<ll>()));

    rep(i, m)
    {
        rep(j, n)
        {
            string s = lock[j];

            rep(k, m)
            {
                if (s[i] == '.')
                {
                    opening[i][j].insert(k);
                }
                std::rotate(s.begin(), s.begin() + 1, s.end());
            }

        }
    }

    ll unionSum = 0;


    vector<vector<vector<ll>>> unions;
    rep(firstHole, m)
    {
        for (ll secondHole = firstHole + 1; secondHole < m; secondHole++)
        {
            ll holeProduct = 1;
            vector<vector<ll>> unionSet;
            rep(row, n)
            {
                vector<ll> rowUnion;
                set_intersection(opening[firstHole][row].begin(), opening[firstHole][row].end(), opening[secondHole][row].begin(), opening[secondHole][row].end(), back_inserter(rowUnion));
                holeProduct *= rowUnion.size();
                unionSet.push_back(rowUnion);
            }
            unions.push_back(unionSet);
            unionSum += holeProduct;
        }
    }

    ll unionIntersectionSum = 0;

    rep(firstHole, unions.size())
    {
        for (ll secondHole = firstHole + 1; secondHole < unions.size(); secondHole++)
        {
            ll holeProduct = 1;

            rep(row, n)
            {
                vector<ll> rowUnion;
                set_intersection(unions[firstHole][row].begin(), unions[firstHole][row].end(), unions[secondHole][row].begin(), unions[secondHole][row].end(), back_inserter(rowUnion));
                holeProduct *= rowUnion.size();
            }

            unionIntersectionSum += holeProduct;
        }
    }


    ll nSum = 0;
    rep(i, m)
    {
        ll prod = 1;
        rep(j, n)
        {
            prod *= opening[i][j].size();
        }
        nSum += prod;
    }

    ll ans = nSum - (unionSum - unionIntersectionSum);

    if (unionIntersectionSum > 0)
    {
        throw new runtime_error("test");
    }
    write(ans);
}