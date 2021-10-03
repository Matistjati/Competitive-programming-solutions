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

int main()
{
    fast();
    string sHalsband;
    read(sHalsband);
    vector<int> halsband;
    rep(i, sHalsband.size())
    {
        halsband.push_back((sHalsband[i] == 'B') ? 1 : 0);
    }

    int half = 0;
    rep(i, halsband.size() / 2)
    {
        half += halsband[i];
    }

    int best = -1;
    rep(i, halsband.size())
    {
        if (half > best)
        {
            best = half;
        }
        half -= halsband[i];
        half += halsband[(i + halsband.size() / 2) % halsband.size()];

    }

    write(best);

    return 0;
}