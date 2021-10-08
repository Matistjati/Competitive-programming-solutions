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

int main()
{
    fast();

    map<int, bool> actions;
    int n;
    read(n);

    rep(i, n)
    {
        int time;
        read(time);
        string type;
        string action;
        read(type);
        read(action);

        if (type == "mobile")
        {
            time += 100;
        }

        actions[time] = action == "play";
    }

    bool playing = false;
    int startTime = -inf;

    int totTime = 0;

    repe(action, actions)
    {
        if (action.second)
        {
            if (!playing)
            {
                playing = true;
                startTime = action.first;
            }
        }
        else
        {
            if (playing)
            {
                totTime += action.first - startTime;
                playing = false;
            }
        }
    }

    write(totTime);

    return 0;
}