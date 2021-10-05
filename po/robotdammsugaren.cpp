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

inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}



int n_sweeped(vector<string>& area, map<char, pair<int, int>>& directions, pair<int, int> pos, string& sequence)
{


    int sweepSum = 0;
    vector<vector<bool>> sweeped(area.size(), vector<bool>(area[0].size(), false));
    repe(command, sequence)
    {

        int xDir = directions[command].first;
        int yDir = directions[command].second;
        int d = 0;
        while (true)
        {
            if (!sweeped[pos.first][pos.second])
            {
                sweeped[pos.first][pos.second] = true;
                sweepSum++;
            }
            pos.first += xDir;
            pos.second += yDir;
            if (area[pos.first][pos.second] == '#')
            {
                pos.first -= xDir;
                pos.second -= yDir;
                break;
            }

            d++;
        }
    }

    return sweepSum;
}

int main()
{
    fast();

    int r;
    int c;
    int n;
    read(r);
    read(c);
    read(n);

    string sequence;
    read(sequence);

    vector<string> area;

    rep(i, r)
    {
        readpush(string, area);
    }

    pair<int, int> startPos;


    rep(row, r)
    {
        rep(column, c)
        {
            pair<int, int> pos = { row,column };
            if (area[row][column] == 'O')
            {
                startPos = pos;
            }

        }
    }

    map<char, pair<int, int>> directions = { {'>',{0,1}},{'<',{0,-1}},{'^',{-1,0}},{'v',{1,0}} };

    write(n_sweeped(area, directions, startPos, sequence));

    return 0;
}