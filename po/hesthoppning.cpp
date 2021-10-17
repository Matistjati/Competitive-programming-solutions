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


int main()
{
    fast();

    int n;
    int m;
    read(n);
    read(m);

    vector<string> area;
    rep(i, n)
    {
        readpush(string, area);
    }

    p2 h1 = { -1,-1 };
    p2 h2 = { -1,-1 };
    rep(i, n)
    {
        rep(j, n)
        {
            if (area[i][j] == 'H')
            {
                if (h1.first == -1)
                {
                    h1 = { i,j };
                    area[i][j] = '.';
                }
                else
                {
                    h2 = { i,j };
                    area[i][j] = '.';
                }
            }
        }
    }

    vector<bool> visited(502*502);

    queue<p2> horseQueue;
    horseQueue.push(h1);

    vector<p2> moves = { {1,2},{-1,2},{1,-2},{-1,-2},{2,1},{-2,1},{2,-1},{-2,-1} };
    while (horseQueue.size())
    {
        p2 curr = horseQueue.front();
        horseQueue.pop();
        if (!visited[curr.first*501+curr.second])
        {
            visited[curr.first * 501 + curr.second] = true;
        }
        else
        {
            continue;
        }

        repe(move, moves)
        {
            p2 newPos(curr);
            newPos.first += move.first;
            newPos.second += move.second;

            if (newPos.first < 0 || newPos.first >= n || newPos.second < 0 || newPos.second >= m || area[newPos.first][newPos.second] == '#')
            {
                continue;
            }
            else
            {
                horseQueue.push(newPos);
            }
        }

    }

    horseQueue.push(h2);

    vector<bool> prevVisited(502 * 502);

    while (horseQueue.size())
    {
        p2 curr = horseQueue.front();
        horseQueue.pop();
        if (visited[curr.first * 501 + curr.second])
        {
            write("JA");
            return 0;
        }

        if (prevVisited[curr.first * 500 + curr.second])
        {
            continue;
        }
        else
        {
            prevVisited[curr.first * 500 + curr.second] = true;
        }

        repe(move, moves)
        {
            p2 newPos(curr);
            newPos.first += move.first;
            newPos.second += move.second;

            if (newPos.first < 0 || newPos.first >= n || newPos.second < 0 || newPos.second >= m || area[newPos.first][newPos.second] == '#')
            {
                continue;
            }
            else
            {
                horseQueue.push(newPos);
            }
        }

    }

    write("NEJ");

    return 0;
}