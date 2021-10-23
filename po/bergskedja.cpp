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
#define linf 1e17

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
    vector<p2> triangles;
    rep(i, n)
    {
        ll x;
        ll y;
        read(x);
        read(y);
        triangles.push_back({ x,y });
    }

    double totArea = 0;
    vector<p2> coords;
    rep(i, n)
    {
        coords.push_back({ {triangles[i].first - triangles[i].second}, {triangles[i].first + triangles[i].second} });
    }
    sort(all(coords));

    p2 curr = coords[0];

    for (int i = 1; i < coords.size(); i++)
    {
        p2 tring = coords[i];
        if (tring.second < curr.second)
        {
            continue;
        }

        double base = (curr.second - curr.first);
        totArea += base*base/4;
        if (tring.first < curr.second)
        {
            double interSectionLength = (curr.second - tring.first);
            totArea -= max(double(0), (interSectionLength * interSectionLength) / 4);
        }

        curr = tring;
    }
    totArea += pow(curr.second - curr.first,2)/4;

    cout << fixed << setprecision(5) << (totArea);

    return 0;
}