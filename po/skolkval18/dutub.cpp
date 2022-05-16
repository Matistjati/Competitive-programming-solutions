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

int best(vector<pair<int,int>>& videos, int& goal, map<p2, int>& memo, int sum, int completed, int n)
{
    if (completed == goal)
    {
        return sum;
    }
    if (n == videos.size())
    {
        return inf;
    }



    p2 state = { completed,n };
    if (setcontains(memo, state))
    {
        return memo[state]+sum;
    }
    else
    {
        int ret = inf;
        ret = min(ret, best(videos, goal, memo, sum + videos[n].first, completed | videos[n].second, n + 1));
        ret = min(ret, best(videos, goal, memo, sum, completed, n + 1));
        memo[state] = ret-sum;
        return ret;
    }
}

int main()
{
    fast();

    int n;
    read(n);
    map<string, int> videos;
    set<char> categories;
    rep(i, n)
    {
        int duration;
        string type;
        read(duration);
        read(type);
        if (!setcontains(videos, type))
        {
            videos[type] = inf;
        }
        videos[type] = min(duration, videos[type]);
        rep(j, type.size())
        {
            categories.insert(type[j]);
        }
    }

    vector<pair<int, int>> videosNew;
    repe(video, videos)
    {
        int mask = 0;
        rep(i, video.first.size())
        {
            mask |= (1 << (video.first[i] - 'a'));
        }
        videosNew.push_back({ video.second, mask });
    }

    int least = inf;
    int goal = 0;
    repe(category, categories)
    {
        goal |= (1 << (category - 'a'));
    }
    map<p2, int> memo;
    write(best(videosNew, goal, memo, 0, 0, 0));

    return 0;
}