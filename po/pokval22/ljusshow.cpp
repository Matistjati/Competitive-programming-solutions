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

#define p2 pair<ll, ll>
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

    ll r;
    ll c;
    read(r);
    read(c);

    string top;
    string right;
    string bot;
    string left;
    read(top);
    read(right);
    read(bot);
    read(left);

    ll rg = 0;
    ll rb = 0;
    ll rr = 0;
    ll gb = 0;
    ll gg = 0;
    ll bb = 0;

    rep(i, top.size())
    {
        if (top[i] == 'R')
        {
            if (bot[i] == 'R')
            {
                rr++;
            }
            else if (bot[i] == 'G')
            {
                rg++;
            }
            else if (bot[i] == 'B')
            {
                rb++;
            }
        }
        else if (top[i] == 'G')
        {
            if (bot[i] == 'R')
            {
                rg++;
            }
            else if (bot[i] == 'G')
            {
                gg++;
            }
            else if (bot[i] == 'B')
            {
                gb++;
            }
        }
        else if (top[i] == 'B')
        {
            if (bot[i] == 'R')
            {
                rb++;
            }
            else if (bot[i] == 'G')
            {
                gb++;
            }
            else if (bot[i] == 'B')
            {
                bb++;
            }
        }
    }

    ll white = 0;

    rep(i, left.size())
    {
        char a = left[i];
        char b = right[i];
        if (a == 'R')
        {
            white += gb;
        }
        else if (a == 'G')
        {
            white += rb;
        }
        else if (a == 'B')
        {
            white += rg;
        }

        if (a != b)
        {
            if (b == 'R')
            {
                white += gb;
            }
            else if (b == 'G')
            {
                white += rb;
            }
            else if (b == 'B')
            {
                white += rg;
            }
        }
        if (a == 'R' && b == 'G')
        {
            white += bb;
        }
        else if (a == 'G' && b == 'R')
        {
            white += bb;
        }

        if (a == 'B' && b == 'G')
        {
            white += rr;
        }
        else if (a == 'G' && b == 'B')
        {
            white += rr;
        }

        if (a == 'R' && b == 'B')
        {
            white += gg;
        }
        else if (a == 'B' && b == 'R')
        {
            white += gg;
        }
    }

    write(white);

    return 0;
}