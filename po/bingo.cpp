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
#define vvi vector<vi>
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
    int k;
    read(n);
    read(k);

    vvi board;
    rep(i, n)
    {
        vi row;
        rep(j, n)
        {
            readpush(ll, row);
        }
        board.push_back(row);
    }

    vector<map<int, int>> rows;
    rep(rowIndex, n)
    {
        map<int, int> row;
        rep(j, n)
        {
            row[board[rowIndex][j]]++;
        }

        rows.push_back(row);
    }

    rep(rowIndex, n)
    {
        map<int, int> col;
        rep(j, n)
        {
            col[board[j][rowIndex]]++;
        }

        rows.push_back(col);
    }

    map<int, int> diag;
    rep(i, n)
    {
        diag[board[i][i]]++;
    }
    rows.push_back(diag);

    diag.clear();
    rep(i, n)
    {
        diag[board[i][n-i-1]]++;
    }
    rows.push_back(diag);

    rep(i, k)
    {
        int ball;
        read(ball);

        repe(potential, rows)
        {
            if (setcontains(potential, ball))
            {
                potential[ball]--;
                if (potential[ball] == 0)
                {
                    potential.erase(ball);
                    if (potential.size() == 0)
                    {
                        write(i+1);
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}