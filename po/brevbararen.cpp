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
#define fract(a) (a-floor(a))

inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

pair<ll,string> longestIncreasing(map<p2, pair<ll,string>>& memo, string& letters, string str, int index, int n)
{
    p2 state = { index,str[str.size()-1] };
    /*if (setcontains(memo, state))
    {
        return n + memo[state];
    }*/
    if (index == letters.size())
    {
        return { n,str };
    }

    pair<ll, string> best = { -inf,"" };
    if (letters[index] > str[str.size()-1])
    {
        pair<ll, string> s = longestIncreasing(memo, letters, str + letters[index], index + 1, n + 1);
        if (s.first > best.first)
        {
            best = s;
        }
    }

    pair<ll, string> s = longestIncreasing(memo, letters, str, index + 1, n);
    if (s.first > best.first)
    {
        best = s;
    }

    //memo[state] = best - n;

    return best;
}

int main()
{
    fast();

    string s;
    read(s);

    map<p2, pair<ll,string>> memo;
    pair<ll, string> ans = longestIncreasing(memo, s, "!", 0, 0);
    ans.second.erase(begin(ans.second));
    write(ans.second);

    return 0;
}
