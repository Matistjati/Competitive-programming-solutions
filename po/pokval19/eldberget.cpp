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

inline ll hashV(p3 const& c)
{
    return c[0] + c[1] * 102 + c[2] * 102 * 203;
}

int main()
{
    fast();

    int r;
    int c;
    int k;
    read(r);
    read(c);
    read(k);

    vector<string> rows;

    rep(i, r)
    {
        readpush(string, rows);
    }


    queue<pair<p3,ll>> toDo;
    toDo.push({ {0,0,0},0 });


    vector<bool> visited(101*101*204*200);

    vector<p2> directions = { {0,1},{0,-1},{1,0},{-1,0} };
    while (toDo.size())
    {
        pair<p3, ll> pos = toDo.front();
        toDo.pop();

        if (pos.first[0] == r - 1 && pos.first[1] == c - 1)
        {
            write(pos.second);
            return 0;
        }

        repe(dir, directions)
        {
            p3 newPos(pos.first);
            newPos[0] += dir.first;
            newPos[1] += dir.second;
            if (newPos[0] < 0 || newPos[0] >= r || newPos[1] < 0 || newPos[1] >= c)
            {
                continue;
            }

            if (rows[newPos[0]][newPos[1]] == '#')
            {
                if (newPos[2] < k)
                {
                    newPos[2]++;


                    ll hash = hashV(newPos);
                    if (!visited[hash])
                    {
                        visited[hash] = true;
                        toDo.push({ newPos,pos.second +1});
                    }
                }
            }
            else
            {

                ll hash = hashV(newPos);
                if (!visited[hash])
                {
                    visited[hash] = true;
                    toDo.push({ newPos,pos.second+1});
                }

            }
        }
    }

    write("nej");
    return 0;
}