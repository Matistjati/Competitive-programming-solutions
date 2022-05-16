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
#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)
#define inf 1e9
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

    int rows;
    int columns;
    read(rows);
    read(columns);
    string encrypted;
    read(encrypted);

    vector<vector<int>> grid(rows, vector<int>(columns, -1));
    pair<int, int> pos = { 0,0 };
    pair<int, int> direction = { -1, -1 };


    rep(i, encrypted.size())
    {
        if (grid[pos.first][pos.second] == -1)
        {
            grid[pos.first][pos.second] = i;
        }
        else
        {
            i--;
        }
        if (pos.first + direction.first >= grid.size())
        {
            direction.first *= -1;
        }
        if (pos.first + direction.first < 0)
        {
            direction.first *= -1;
        }

        if (pos.second + direction.second >= grid[0].size())
        {
            direction.second *= -1;
        }
        if (pos.second + direction.second < 0)
        {
            direction.second *= -1;
        }
        pos.first += direction.first;
        pos.second += direction.second;
    }

    vector<pair<int,int>> permutation;
    int n = 0;
    rep(row, rows)
    {
        rep(column, columns)
        {

            int index = grid[row][column];
            if (index >= 0)
            {
                permutation.push_back({ row,column });
                n++;
            }
        }
    }

    string ans = string(n, '-');

    rep(perm, permutation.size())
    {
        ans[grid[permutation[perm].first][permutation[perm].second]] = encrypted[perm];
    }

    write(ans);

    return 0;
}