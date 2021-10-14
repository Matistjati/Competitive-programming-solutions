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



    ll n;
    ll m;
    read(n);
    read(m);

    queue<ll> teams;
    rep(i, n)
    {
        ll t;
        read(t);
        teams.push(t * m);
    }
    priority_queue<ll, vector<ll>, greater<ll>> wheel;


    ll i = 0;

    while (wheel.size() < m && teams.size())
    {
        wheel.push(teams.front() + i);
        teams.pop();
        i++;
    }


    while (true)
    {
        i = wheel.top();
        wheel.pop();
        if (teams.size() == 0 && wheel.size() == 0)
        {
            break;
        }

        if (teams.size())
        {
            wheel.push(teams.front() + i);
            teams.pop();
        }
    }


    write(i);

    return 0;
}