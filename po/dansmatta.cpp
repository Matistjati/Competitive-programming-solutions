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

int main()
{
    fast();

    int n;
    read(n);

    vector<string> moves;

    rep(i, n)
    {
        readpush(string, moves);
    }

    map<string, int> oldMoves = { {"VH",0} };
    vector<char> directions = { 'U','V','N','H' };
    repe(move, moves)
    {
        if (move.size() == 2)
        {
            int ans = inf;
            repe(oldMove, oldMoves)
            {
                int cost = (oldMove.first.find(move[0]) == string::npos) + (oldMove.first.find(move[1]) == string::npos);
                ans = min(ans, cost + oldMove.second);
            }
            oldMoves = { {move,ans} };
        }
        else
        {
            map<string, int> newMoves = {};
            vector<string> validEnds;
            repe(direction, directions)
            {
                if (direction != move[0])
                {
                    validEnds.push_back({ string(1,move[0]) + string(1,direction) });
                }
            }
            repe(goal, validEnds)
            {
                int ans = inf;
                repe(oldMove, oldMoves)
                {
                    int cost = (oldMove.first.find(goal[0]) == string::npos) + (oldMove.first.find(goal[1]) == string::npos);
                    ans = min(ans, cost + oldMove.second);
                }
                newMoves[goal] = ans;
            }
            oldMoves = newMoves;
        }

    }

    int ans = inf;
    repe(oldMove, oldMoves)
    {
        ans = min(ans, oldMove.second);
    }

    write(ans);

    return 0;
}