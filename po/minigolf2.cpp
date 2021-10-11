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

#define ll long long
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define vi vector<ll>
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

    ll r;
    ll c;
    ll k;
    read(r);
    read(c);
    read(k);

    vector<string> grid;
    vector<vector<ll>> n_hits(r,vector<ll>(c,inf));

    rep(i, r)
    {
        readpush(string, grid);
    }

    p2 start;
    p2 goal;
    rep(row, r)
    {
        rep(column, c)
        {
            if (grid[row][column] == 'S')
            {
                start = { row,column };
                grid[row][column] = '.';
            }
            else if (grid[row][column] == 'G')
            {
                goal = { row,column };
                grid[row][column] = '.';
            }
        }
    }

    queue<p3> toCheck;
    toCheck.push({start.first,start.second,0});

    vector<p2> directions = { {0,1},{0,-1},{1,0},{-1,0} };
    while (toCheck.size())
    {
        p3 curr = toCheck.front();
        toCheck.pop();

        if (get<0>(curr) == goal.first && get<1>(curr) == goal.second)
        {
            write(get<2>(curr));
            return 0;
        }

        repe(dir, directions)
        {
            for (int m = 1; m < k + 1; m++)
            {
                ll r1, c1, n;
                tie(r1, c1, n) = curr;
                r1 += dir.first * m;
                c1 += dir.second * m;

                if (c1 < 0 || c1 >= c || r1 < 0 || r1 >= r || grid[r1][c1] == '#' || n_hits[r1][c1] <= n)
                {
                    break;
                }
                if (n_hits[r1][c1] <= n + 1)
                {
                    continue;
                }

                n_hits[r1][c1] = n + 1;

                toCheck.push({r1,c1,n+1});
            }
        }

    }


    return 0;
}