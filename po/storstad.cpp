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

int main()
{
    fast();

    int n;
    int m;
    read(n);
    read(m);

    pair<double,double> avg = { 0,0 };
    vector<p2> friends;
    rep(i, n)
    {
        int x;
        int y;
        read(x);
        read(y);
        avg.first += x;
        avg.second += y;
        friends.push_back({ x,y });
    }
    avg.first /= n;
    avg.second /= n;

    vector<pair<double, p2>> houses;
    rep(i, m)
    {
        double x;
        double y;
        read(x);
        read(y);

        houses.push_back({ sqrt(pow(x - avg.first,2) + pow(y - avg.second,2)), {x,y} });

    }
    sort(all(houses));

    ll ans = 1e12;

    auto Start = std::chrono::high_resolution_clock::now();

    rep(i, m)
    {
        p2 ansHouse = { houses[i].second.first, houses[i].second.second };

        ll s = 0;
        repe(house, friends)
        {
            s += abs(ansHouse.first - house.first) + abs(ansHouse.second - house.second);
        }
        ans = min(ans, s);

        auto End = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> Elapsed = End - Start;
        if (Elapsed.count() >= 850.0)
            break;

    }


    cout << ans;

    return 0;
}