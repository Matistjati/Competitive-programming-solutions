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

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
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

int main()
{
    fast();

    ll M;
    ll N;

    read(M);
    read(N);

    ll m = M;
    ll n = N;
    double sqrtm = sqrt(m);
    double sqrtn = sqrt(n);

    if (floor(sqrtm)+1<sqrtn)
    {
        cout << floor(sqrtm) + 1 << " " << floor(sqrtm) + 1;
        return 0;
    }

    ll up = pow(ceil(sqrt(n)), 2);
    ll down = pow(floor(sqrt(m)), 2);

    ll bestDiff = linf;
    ll bestB = -1;
    ll bestL = -1;

    for (ll b = 1; b < sqrtn+1; b++)
    {
        ll l = m / b;

        if (b*l < m)
        {
            l++;
        }

        if (b*l>n)
        {
            l--;
        }

        if (b*l>=m && b*l<=n && abs(b - l) < bestDiff)
        {
            bestDiff = abs(b - l);
            bestB = b;
            bestL = l;
        }
    }

    for (ll b = 1; b < sqrtn + 1; b++)
    {
        ll l = n / b;

        if (b * l < m)
        {
            l++;
        }

        if (b * l > n)
        {
            l--;
        }

        if (b * l >= m && b * l <= n && abs(b - l) < bestDiff)
        {
            bestDiff = abs(b - l);
            bestB = b;
            bestL = l;
        }
    }

    cout << bestB << " " << bestL;

    return 0;
}
