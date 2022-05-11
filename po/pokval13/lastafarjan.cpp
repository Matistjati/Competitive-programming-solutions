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

int best(vector<vector<vector<vector<int>>>>& memo, vector<int>& cars, int& l, int index, p4& lanes, int sum)
{
    int& ans = memo[lanes[0]][lanes[1]][lanes[2]][lanes[3]];

    if (ans != -1)
    {
        return ans;
    }
    if (index == cars.size())
    {
        return sum;
    }

    ans = max(sum,ans);

    rep(i, 4)
    {
        if (lanes[i]+cars[index] <= l)
        {
            lanes[i] += cars[index] + 1;
            ans = max(ans, best(memo, cars, l, index + 1, lanes, sum + 1));
            lanes[i] -= cars[index] + 1;
        }
    }

    return ans;
}

vector<vector<vector<vector<int>>>> memo(62, vector<vector<vector<int>>>(62, vector<vector<int>>(62, vector<int>(62,-1))));

int main()
{
    fast();

    int n;
    int l;
    read(n);
    read(l);

    vector<int> cars;
    rep(i, n)
    {
        readpush(int, cars);
    }


    p4 lanes = { 0,0,0,0 };

    write(best(memo, cars, l, 0, lanes, 0));

    return 0;
}