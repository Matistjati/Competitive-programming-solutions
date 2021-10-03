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

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define repp(i, high) for (ll i = high; i >= 0; i--)
#define inf 1e9

void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

struct poir
{
    inline std::size_t operator()(const std::pair<int, int>& v) const {
        return v.first * 10000 + v.second;
    }
};

int main()
{
    fast();

    int rows;
    int columns;
    read(rows);
    read(columns);
    vector<string> map;
    rep(i, rows)
    {
        readpush(string, map);
    }


    unordered_set<pair<int, int>, poir> visited;
    queue<pair<int, int>> toVisit;
    toVisit.push({ 0,0 });
    vector<pair<int, int>> moves = { {0,1},{0,-1},{1,0},{-1,0} };


    while (toVisit.size())
    {
        pair<int, int> curr = toVisit.front();
        toVisit.pop();
        if (setcontains(visited, curr))
        {
            continue;
        }
        else
        {
            visited.insert(curr);
        }

        repe(move, moves)
        {
            pair<int, int> newPos = { curr.first + move.first, curr.second + move.second };
            if (newPos.first < 0 || newPos.first > map.size() - 1 || newPos.second < 0 || newPos.second > map[0].size())
            {
                continue;
            }
            char character = map[newPos.first][newPos.second];
            if (character == 'X')
            {
                write("Death to humans");
                return 0;
            }
            else if (character == '#')
            {
                continue;
            }

            toVisit.push(newPos);
        }
    }


    write("We are safe");

    return 0;
}