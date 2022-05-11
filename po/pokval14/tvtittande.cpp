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

using namespace std;

#define ll long long
#define p2 pair<ll, ll>
#define p3 vector<ll>
#define p4 vector<ll>
#define vi vector<ll>
#define inf 1e9

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


int main()
{
    fast();

    int n;
    read(n);

    vector<int> timeWatched(n);
    map<int, vector<p2>> adMap;
    rep(i, n)
    {
        int n_ads;
        read(n_ads);

        rep(j, n_ads)
        {
            string duration;
            read(duration);
            char sep = duration.find('-');
            string first = duration.substr(0, sep);
            string second = duration.substr(sep + 1, duration.size() - sep - 1);

            p2 time = { stoi(first.substr(0,2)) * 60 + stoi(first.substr(3,2)), stoi(second.substr(0,2)) * 60 + stoi(second.substr(3,2)) };
            if (!setcontains(adMap,i))
            {
                adMap[i] = {};
            }
            adMap[i].push_back(time);

        }
    }

    int totTime = 0;
    int lastTime = 0;
    int channel = 0;
    int switching = false;

    rep(i, 1440)
    {
        if (switching)
        {
            switching = false;
            channel++;
            channel = channel % n;
        }
        repe(ad, adMap[channel])
        {
            if (i >= ad.first && i <= ad.second)
            {
                switching = true;
                break;
            }
        }

        if (!switching)
        {
            timeWatched[channel]++;
        }
    }

    rep(i, n)
    {
        write(timeWatched[i]);
    }

    return 0;
}