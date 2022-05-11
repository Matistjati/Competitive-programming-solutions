#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>
#include <string>
#include <iterator>
#include <queue>
#include <tuple>
#include <numeric>
#include <random>
#include <time.h>
#include <stack>
#include <chrono>
#include <unordered_map>
#include <iomanip>

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define inf 2e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define deb __debugbreak();

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)


inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

double bestvalue(vector<double>& ratios, map<tuple<int, bool, double>, double>& memo, int index, bool liquid, double moneys, double& c)
{
    tuple<int, bool, double> state = { index,liquid,moneys };
    if (setcontains(memo, state))
    {
        return moneys + memo[state];
    }
    if (index == ratios.size())
    {
        return moneys - ((liquid) ? 0 : c);
    }


    double best = -inf;

    double ratio = ratios[index];
    if (ratio > 1)
    {
        if (!liquid)
        {
            best = max(best, bestvalue(ratios, memo, index + 1, false, moneys * ratio, c));
            best = max(best, bestvalue(ratios, memo, index + 1, true, moneys - c, c));
        }
        else
        {
            best = max(best, bestvalue(ratios, memo, index + 1, true, moneys, c));
            best = max(best, bestvalue(ratios, memo, index + 1, false, (moneys - c) * ratio, c));
        }
    }
    else
    {
        if (liquid)
        {
            best = max(best, bestvalue(ratios, memo, index + 1, true, moneys, c));
            best = max(best, bestvalue(ratios, memo, index + 1, false, (moneys - c) * ratio, c));
        }
        else
        {
            best = max(best, bestvalue(ratios, memo, index + 1, true, moneys - c, c));
            best = max(best, bestvalue(ratios, memo, index + 1, false, moneys * ratio, c));
        }
    }
    memo[state] = best - moneys;

    return best;

}

int main()
{
    fast();

    int n;
    read(n);
    double c;
    read(c);

    double moneys = 100;
    bool liquid = true;

    vector<double> stocks;
    rep(i, n)
    {
        readpush(double, stocks);
    }

    vector<double> ratios;



    bool increasing = stocks[1] / stocks[0] > 1;
    double totalIncrease = 1;
    for (int i = 0; i < stocks.size() - 1; i++)
    {
        double ratio = stocks[i + 1] / stocks[i];
        if (ratio > 1)
        {
            if (increasing)
            {
                totalIncrease *= ratio;
            }
            else
            {
                ratios.push_back(totalIncrease);
                increasing = true;
                totalIncrease = ratio;
            }
        }
        else
        {
            if (increasing)
            {
                ratios.push_back(totalIncrease);
                increasing = false;
                totalIncrease = ratio;
            }
            else
            {
                totalIncrease *= ratio;
            }
        }
    }
    if (totalIncrease != 1)
    {
        ratios.push_back(totalIncrease);
    }

    vector<pair<double,double>> table;
    table.push_back({ -inf,100 });

    rep(i, ratios.size())
    {
        double ratio = ratios[i];

        pair<double,double> newEntry = { -1,-1 };
        if (ratio > 1)
        {
            newEntry.first = max(newEntry.first, table[i].first * ratio);
            newEntry.first = max(newEntry.first, (table[i].second-c) * ratio);

            newEntry.second = max(newEntry.second, table[i].first-c);
            newEntry.second = max(newEntry.second, table[i].second);
        }
        else
        {
            newEntry.first = max(newEntry.first, table[i].first * ratio);
            newEntry.first = max(newEntry.first, (table[i].second - c) * ratio);

            newEntry.second = max(newEntry.second, table[i].first - c);
            newEntry.second = max(newEntry.second, table[i].second);
        }
        table.push_back(newEntry);
    }

    table[table.size() - 1].first -= c;

    cout << fixed;
    cout << setprecision(9) << max(table[table.size() - 1].first, table[table.size() - 1].second);

    return 0;
}