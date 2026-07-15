#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

ll winning(string& board, char player) {
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
    cout << board[6] << board[7] << board[8] << endl;
}

p2 sequence(string board, bool computer, ll depth)
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
    ll n = 0;

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string order;
    cin >> order;

    string board = ".........";

    if (order == "second")
    {
        string t1;
        string t2;
        string t3;
        cin >> t1;
        cin >> t2;
        cin >> t3;
        board = t1 + t2 + t3;
    }
    else
    {
        board[0] = 'x';
        string t1;
        string t2;
        string t3;
        cin >> t1;
        cin >> t2;
        cin >> t3;
        board = t1 + t2 + t3;
    }

    while (true)
    {
        ll best = -inf;

        p2 move = sequence(board, true, 0);

        board[move.first] = 'x';
        display(board);
        if (winning(board, 'x') || winning(board, 'o'))
        {
            break;
        }
        ll n = 0;
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

        string t1, t2, t3;
        cin >> t1 >> t2 >> t3;
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
