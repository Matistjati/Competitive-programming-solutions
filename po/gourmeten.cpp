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

#define p2 pair<int, int>
#define ll long long
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

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

int answer(map<int, int>& memo, vector<int>& foods, int sum, int& m)
{
    if (m == sum)
    {
        return 1;
    }
    else if (sum>m)
    {
        return 0;
    }

    int ret = 0;
    rep(i, foods.size())
    {
        int newSum = sum + foods[i];
        if (setcontains(memo,newSum))
        {
            ret += memo[newSum];
        }
        else
        {
            int v = answer(memo, foods, newSum, m);
            memo[newSum] = v;
            ret += v;
        }
    }

    return ret;
}

int main()
{
    fast();


    int m;
    int n;
    read(m);
    read(n);

    vector<int> foods;
    rep(i, n)
    {
        readpush(int, foods);
    }
    int ans = 0;

    map<int, int> memo;
    rep(i, n)
    {
        ans += answer(memo, foods, foods[i], m);
    }
    write(ans);
    return 0;
}