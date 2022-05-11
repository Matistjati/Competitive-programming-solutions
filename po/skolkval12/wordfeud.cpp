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
    cin.tie(NULL); cout.tie(NULL);
}

int main()
{
    fast();

    int n;
    read(n);

    set<p2> dl;
    set<p2> tl;
    set<p2> dw;
    set<p2> tw;


    rep(i, n)
    {
        int x;
        int y;
        string type;
        read(x);
        read(y);
        read(type);
        if (type=="DL")
        {
            dl.insert({ x-1,y-1 });
        }
        if (type == "TL")
        {
            tl.insert({ x-1,y-1 });
        }
        if (type == "DW")
        {
            dw.insert({ x-1,y-1 });
        }
        if (type == "TW")
        {
            tw.insert({ x-1,y-1 });
        }
    }
    string word;
    read(word);

    int best = -inf;
    rep(i, 10)
    {
        rep(j, 10)
        {
            int score = 0;
            int mul = 1;
            rep(k, word.size())
            {
                if (k+i>9)
                {
                    break;
                }
                p2 pos = { i + k,j };
                if (setcontains(dl, pos))
                {
                    score += (word[k]-'0') * 2;
                    continue;
                }
                if (setcontains(tl, pos))
                {
                    score += (word[k] - '0') * 3;
                    continue;
                }
                if (setcontains(dw, pos))
                {
                    mul *= 2;
                }
                if (setcontains(tw, pos))
                {
                    mul *= 3;
                }
                score += (word[k] - '0');
            }
            score *= mul;
            best = max(best, score);
        }
    }

    rep(i, 10)
    {
        rep(j, 10)
        {
            int score = 0;
            int mul = 1;

            rep(k, word.size())
            {
                if (k + j > 9)
                {
                    break;
                }
                p2 pos = { i,j+k };
                if (setcontains(dl, pos))
                {
                    score += (word[k] - '0') * 2;
                    continue;
                }
                if (setcontains(tl, pos))
                {
                    score += (word[k] - '0') * 3;
                    continue;
                }
                if (setcontains(dw, pos))
                {
                    mul *= 2;
                }
                if (setcontains(tw, pos))
                {
                    mul *= 3;
                }
                score += (word[k] - '0');
            }
            score *= mul;
            best = max(best, score);
        }
    }

    write(best);

    return 0;
}