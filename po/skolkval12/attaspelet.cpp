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

    vector<int> board = { 1,2,3,4,5,6,7,8,0 };

    map<vector<int>, int> boards;
    queue<vector<int>> toCheck;
    toCheck.push(board);
    boards[board] = 0;

    vector<p2> directions = { {1,0},{-1,0},{0,1},{0,-1} };


    while (toCheck.size())
    {
        vector<int> curr = toCheck.front();
        toCheck.pop();

        int depth = boards[curr];
        if (depth >= 31)
        {
            break;
        }

        p2 open;
        rep(i, 3)
        {
            rep(j, 3)
            {
                if (!curr[i*3+j])
                {
                    open = { i,j };
                    goto done;
                }
            }
        }
    done:

        depth++;
        if (open.first - 1 >= 0)
        {
            vector<int> c(curr);
            swap(c[open.first * 3 + open.second], c[(open.first - 1) * 3 + open.second]);
            if (!setcontains(boards, c))
            {
                boards[c] = depth;
                toCheck.push(c);
            }
        }
        if (open.first + 1 < 3)
        {
            vector<int> c(curr);
            swap(c[open.first * 3 + open.second], c[(open.first + 1) * 3 + open.second]);
            if (!setcontains(boards, c))
            {
                boards[c] = depth;
                toCheck.push(c);
            }
        }

        if (open.second + 1 < 3)
        {
            vector<int> c(curr);
            swap(c[open.first * 3 + open.second], c[(open.first) * 3 + open.second + 1]);
            if (!setcontains(boards, c))
            {
                boards[c] = depth;
                toCheck.push(c);
            }
        }

        if (open.second - 1 >= 0)
        {
            vector<int> c(curr);
            swap(c[open.first * 3 + open.second], c[(open.first) * 3 + open.second - 1]);
            if (!setcontains(boards, c))
            {
                boards[c] = depth;
                toCheck.push(c);
            }
        }


    }

    vector<int> state(9);
    repe(num, state)
    {
        read(num);
    }

    write(boards[state]);

    return 0;
}