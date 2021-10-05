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



void best_sequence(vector<string>& area, map<char, pair<int, int>>& directions, int& maxValue, string& bestSequnce,
    vector<vector<bool>>& bestSweeped, pair<int,int>& bestPos, vector<vector<bool>>sweeped, pair<int, int> pos, int depth,
    int score, string sequence, int targetLength)
{
    if (depth == 0)
    {
        if (score > maxValue)
        {
            maxValue = score;
            bestSequnce = sequence;
            bestSweeped = sweeped;
            bestPos = pos;
        }
        else if (sequence.size() < targetLength)
        {
            bestSequnce = sequence;
        }
        return;
    }

    if (sequence.size())
    {
        char command = sequence[sequence.size() - 1];

        int d = 0;
        int xDir = directions[command].first;
        int yDir = directions[command].second;
        while (true)
        {
            if (!sweeped[pos.first][pos.second])
            {
                sweeped[pos.first][pos.second] = true;
                score++;
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
        if (d < 1)
        {
            return;
        }
    }





    best_sequence(area, directions, maxValue, bestSequnce, bestSweeped, bestPos, sweeped, pos, depth - 1, score, sequence+'^', targetLength);
    best_sequence(area, directions, maxValue, bestSequnce, bestSweeped, bestPos, sweeped, pos, depth - 1, score, sequence+'v', targetLength);
    best_sequence(area, directions, maxValue, bestSequnce, bestSweeped, bestPos, sweeped, pos, depth - 1, score, sequence+'>', targetLength);
    best_sequence(area, directions, maxValue, bestSequnce, bestSweeped, bestPos, sweeped, pos, depth - 1, score, sequence+'<', targetLength);


}

int main()
{
    fast();

    int n;
    int w;
    int d;
    read(n);
    read(w);
    read(d);

    vector<int> sticks(n);
    repe(stick, sticks)
    {
        read(stick);
    }

    int n_full = 0;

    repe(stick, sticks)
    {
        if (n_full >= d)
        {
            write("Papperskorgen");
        }
        else
        {
            if (stick > w)
            {
                write("Papperskorgen");
            }
            else
            {
                write("Asken");
                n_full++;
            }
        }
    }


    return 0;
}