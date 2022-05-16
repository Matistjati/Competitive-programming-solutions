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

int n_reg(map<tuple<int, int, int>, int>& memo, vector<int>& nums, int& t, int index, int su, int sm)
{
    tuple<int, int, int> state = { index,su,sm };
    if (setcontains(memo, state))
    {
        return memo[state];
    }

    if (su>t-su)
    {
        if ((su-sm) <= t - (su-sm))
        {
            return 1;
        }
        return 0;
    }
    if (index == nums.size())
    {
        return 0;
    }

    int ret = 0;

    ret += n_reg(memo, nums, t, index + 1, su + nums[index], min(sm, nums[index]));
    ret += n_reg(memo, nums, t, index + 1, su, sm);

    memo[state] = ret;

    return ret;
}


int main()
{
    fast();

    int n;
    read(n);

    vector<int> nums;
    rep(i, n)
    {
        readpush(int, nums);
    }

    map<tuple<int, int, int>, int> memo;
    int t = accumulate(all(nums), 0);
    int s = n_reg(memo, nums, t, 0, 0, inf);
    write(s);

    return 0;
}
