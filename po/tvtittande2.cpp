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


using namespace std;

#define ll long long
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define vi vector<ll>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

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
    int k;
    read(n);
    read(k);

    vi series;
    series.push_back(inf);
    rep(i, k)
    {
        readpush(int, series);
    }


    vector<pair<int, vi>> birthdays;
    rep(i, n)
    {
        int d;
        int c;
        read(d);
        read(c);

        vi series;
        rep(j, c)
        {
            readpush(int, series);
        }
        birthdays.push_back({ d,series });
    }

    sort(all(birthdays));

    int prev = 0;
    int savedHours = 0;
    rep(i, birthdays.size())
    {
        int hoursAvailable = (birthdays[i].first - prev) * 10+savedHours;
        savedHours = 0;
        prev = birthdays[i].first+1;

        vi daySeries = birthdays[i].second;
        rep(j, daySeries.size())
        {
            int seriesIndex = daySeries[j];
            if (series[seriesIndex] > 0)
            {
                if (hoursAvailable < series[seriesIndex])
                {
                    write("Nej");
                    return 0;
                }
                else
                {
                    hoursAvailable -= series[seriesIndex];
                    series[seriesIndex] = 0;
                }
            }
        }

        if (hoursAvailable > 0)
        {
            savedHours = hoursAvailable;
        }
    }



    write("Ja");

    return 0;
}