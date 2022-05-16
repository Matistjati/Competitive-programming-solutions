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

int possible(vector<int> heights, int extra)
{
    heights[0] += extra;
    rep(i, heights.size()-1)
    {
        int avg = (heights[i] + heights[i + 1]) / 2;
        if (avg < heights[i+1])
        {
            return 0;
        }
        heights[i + 1] = avg;
    }

    return 1;
}

int main()
{
    fast();

    int n;
    read(n);
    vector<int> heights;
    vector<int> extra;
    rep(i, n)
    {
        readpush(int, heights);
        extra.push_back(0);
    }

    int high = inf;
    int low = 0;
    while (true)
    {
        int mid = (high + low) / 2;

        int p = possible(heights, mid);
        if (p)
        {
            high = mid;
        }
        else
        {
            low = mid+1;
        }

        if (low==high)
        {
            write(high);
            return 0;
        }
    }

    return 0;
}