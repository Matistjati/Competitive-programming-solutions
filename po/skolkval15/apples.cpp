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
#define p3 vector<ll>
#define p4 vector<ll>
#define vi vector<ll>
#define inf 1e9

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



int most(vector<vector<int>>& top, int& k, p2 start, set<p2> visited, int moves, int eaten)
{
    if (moves == k)
    {
        return eaten;
    }
    if (setcontains(visited, start))
    {
        return 0;
    }
    else
    {
        visited.insert(start);
    }
    vector<p2> dir = { {1,0},{-1,0},{0,1},{0,-1} };

    int ret = 0;

    repe(direction, dir)
    {
        p2 n(start);
        n.first += direction.first;
        n.second += direction.second;
        if (n.first < 0 || n.first >= 2 || n.second < 0 || n.second >= top[0].size() || setcontains(visited, n))
        {
            continue;
        }
        ret = max(ret, most(top, k, n, visited, moves + 1, eaten + top[n.first][n.second]));
    }
    return ret;
}

int main()
{
    fast();

    int n;
    int k;
    read(n);
    read(k);

    vector<vector<int>> top(2,vector<int>());

    p2 start = { 1,0 };
    rep(i, n)
    {
        readpush(int, top[0]);
    }
    rep(i, n)
    {
        readpush(int, top[1]);
    }

    set<p2> visited;
    if (k > 2*n)
    {
        write(accumulate(all(top[0]), 0) + accumulate(all(top[1]),0));
    }
    else
    {
        write(most(top, k, start, visited, 1, top[1][0]));
    }


    return 0;
}