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

int winning(string& board, char player)
{
    if (
        (board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player) ||
        (board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player) ||
        (board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void display(string board)
{
    cout << board[0] << board[1] << board[2] << endl;
    cout << board[3] << board[4] << board[5] << endl;
    cout << board[6] << board[7] << board[8] << endl;;// << endl;
}

p2 sequence(string board, bool computer, int depth)
{
    p2 best = { -1, (computer) ? -inf : inf };
    if (winning(board, 'x'))
    {
        return best;
    }
    else if (winning(board, 'o'))
    {
        return best;
    }
    int n = 0;

    rep(i, 9)
    {
        if (board[i] == '.')
        {
            n++;
            break;
        }
    }

    if (n == 0)
    {
        return { -1,0 };
    }


    rep(i,9)
    {
        string c(board);
        if (c[i] == '.')
        {
            n++;
            if (computer)
            {
                c[i] = 'x';
            }
            else
            {
                c[i] = 'o';
            }
        }
        else
        {
            continue;
        }
        p2 v = sequence(c, !computer, depth + 1);
        v.first = i;
        if (computer)
        {
            if (v.second > best.second)
            {
                best = v;
            }
        }
        else
        {
            if (v.second < best.second)
            {
                best = v;
            }
        }
    }



    return best;
}

int main()
{
    fast();

    string order;
    read(order);

    string board = ".........";

    if (order == "second")
    {
        string t1;
        string t2;
        string t3;
        read(t1);
        read(t2);
        read(t3);
        board = t1 + t2 + t3;
    }
    else
    {
        board[0] = 'x';
        string t1;
        string t2;
        string t3;
        read(t1);
        read(t2);
        read(t3);
        board = t1 + t2 + t3;
    }

    while (true)
    {
        int best = -inf;

        p2 move = sequence(board, true, 0);

        board[move.first] = 'x';
        display(board);
        if (winning(board, 'x') || winning(board, 'o'))
        {
            break;
        }
        int n = 0;
        rep(i, 9)
        {
            if (board[i] != '.')
            {
                n++;
            }
        }
        if (n == 9)
        {
            break;
        }

        string t1;
        string t2;
        string t3;
        read(t1);
        read(t2);
        read(t3);
        board = t1 + t2 + t3;
        if (winning(board, 'x') || winning(board, 'o'))
        {
            break;
        }
        n = 0;
        rep(i, 9)
        {
            if (board[i] != '.')
            {
                n++;
            }
        }
        if (n==9)
        {
            break;
        }
    }

    return 0;
}