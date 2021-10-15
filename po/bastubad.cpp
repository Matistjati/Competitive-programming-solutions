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
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define p4 tuple<ll, ll, ll, ll>
#define vi vector<ll>
#define vii vector<vi>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define deb nothing();

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)

inline void nothing() {}

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
    vii finnish;

    rep(i, n)
    {
        int a;
        int b;
        int c;
        int t;
        read(a);
        read(b);
        read(c);
        read(t);
        finnish.push_back({ a,b,c,t });
    }

    double a=0;
    double b=0;
    double c=0;

    sort(finnish.begin(), finnish.end(), [](const vi& lhs, const vi& rhs)
        {
            return lhs[3] < rhs[3];
        });


    double maxValue = -inf;

    rep(i, finnish.size())
    {
        a += finnish[i][0];
        b += finnish[i][1];
        c += finnish[i][2];
    }

    rep(i, finnish.size())
    {
        double mx = -b / (2 * a);
        double my = a * mx * mx + b * mx + c;
        if (mx > 0 && mx < finnish[i][3])
        {
            maxValue = max(maxValue, my);
        }

        my = a * finnish[i][3] * finnish[i][3] + b * finnish[i][3] + c;
        maxValue = max(maxValue, my);

        maxValue = max(maxValue, c);

        a -= finnish[i][0];
        b -= finnish[i][1];
        c -= finnish[i][2];


    }

    cout << fixed;
    cout << setprecision(15) << maxValue;
    deb

    return 0;
}