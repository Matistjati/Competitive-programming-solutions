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
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

double distance(vector<pair<double, double>>& points, double x)
{
    double d = 0;
    repe(point, points)
    {
        d += 2*sqrt((point.first - x) * (point.first - x) + point.second * point.second);
    }
    return d;
}

double ddistance(vector<pair<double, double>>& points, double x)
{
    double d = 0;
    repe(point, points)
    {
        d += -(point.first - x) / sqrt((point.first - x) * (point.first - x) + point.second * point.second);
    }
    return d;
}


int main()
{
    fast();

    int n;
    read(n);

    vector<pair<double, double>> points(n);
    rep(i, n)
    {
        double x;
        double y;
        read(x);
        read(y);
        points[i] = { x,y };
    }


    double low = -100;
    double high = 100;

    while (abs(high - low) > 1e-4)
    {
        double mid = (high + low) / 2;

        if (ddistance(points, mid) < 0)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }

    cout << fixed << setprecision(15) << distance(points, (high+low)/2);

    return 0;
}