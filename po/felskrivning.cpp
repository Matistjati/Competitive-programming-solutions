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
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int ans(map<pair<set<string>, int>, int>& memo, string& s, string& mistake, set<string>& mistakesDone, int index)
{
    pair<set<string>, int> state = { mistakesDone, index };
    if (setcontains(memo, state))
    {
        return memo[state];
    }
    if (index == s.size())
    {
        return 1;
    }

    int ret = 0;

    char c = s[index];

    if (stringcontains(mistake, c))
    {
        string mistCopy = mistake;
        mistCopy.erase(remove(all(mistCopy), c), mistCopy.end());
        repe(mistakeMade, mistCopy)
        {
            string mist = string(1, c) + string(1, mistakeMade);
            if (!setcontains(mistakesDone, mist))
            {
                set<string> copy(mistakesDone);
                copy.insert(mist);


                ret += ans(memo, s, mistake, copy, index + 1);
            }
        }
    }

    ret += ans(memo, s, mistake, mistakesDone, index + 1);
    memo[state] = ret;

    return ret;
}

int main()
{
    fast();

    string site;
    read(site);

    int n;
    read(n);
    vector<string> replacements;
    rep(i, n)
    {
        string s;
        read(s);

        replacements.push_back(s);
    }

    set<string> mistakes;

    int answer = 1;
    repe(mistake, replacements)
    {
        map<pair<set<string>, int>, int> memo;
        answer *= ans(memo, site, mistake, mistakes, 0);
    }
    write(answer-1);


    return 0;
}