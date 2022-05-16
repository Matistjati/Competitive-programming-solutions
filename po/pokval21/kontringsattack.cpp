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

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define repp(i, high) for (ll i = high; i >= 0; i--)
#define inf 1e9

void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int sign(int a)
{
    if (a > 0)
    {
        return 1;
    }
    else if (a < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    fast();

    int n;
    read(n);

    vector<pair<int, int>> matches;
    rep(i, n)
    {
        int f;
        int s;
        read(f);
        read(s);
        matches.push_back({ f,s });
    }

    map<int,int> pointDiffMap;
    int score = 0;

    rep(i, matches.size())
    {
        int diff = abs(matches[i].first - matches[i].second);
        if (!setcontains(pointDiffMap, diff))
        {
            pointDiffMap[diff] = 0;
        }
        int signV = sign(matches[i].first - matches[i].second);
        pointDiffMap[diff] += signV;
        score += signV;
    }

    pointDiffMap.insert({ 0,0 });

    int bestK = inf;
    int bestScore = -inf;
    repe(i, pointDiffMap)
    {
        score -= i.second;
        if (score > bestScore)
        {
            bestScore = score;
            bestK = i.first;
        }
    }

    write(bestK);

    return 0;
}