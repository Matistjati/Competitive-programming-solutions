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

int least_crosswalks(string& crosswalks, map<p2, int>& memo, int index, int side, int crossed)
{
    if (index==crosswalks.size())
    {
        return (side==1) ? crossed : crossed+1;
    }
    p2 state = { index,side };
    if (setcontains(memo,state))
    {
        return memo[state]+crossed;
    }

    int ret = inf;
    if (crosswalks[index] == 'B')
    {
        ret = min(ret, least_crosswalks(crosswalks, memo, index + 1, side, crossed + 1));
        ret = min(ret, least_crosswalks(crosswalks, memo, index + 1, !side, crossed + 2));
        memo[state] = ret-crossed;
    }
    else if (crosswalks[index] == 'N')
    {
        ret = min(ret, least_crosswalks(crosswalks, memo, index + 1, side, crossed + side));
        ret = min(ret, least_crosswalks(crosswalks, memo, index + 1, !side, crossed + 1 + !side));
        memo[state] = ret-crossed;
    }
    else if (crosswalks[index] == 'S')
    {
        ret = min(ret, least_crosswalks(crosswalks, memo, index + 1, side, crossed + !side));
        ret = min(ret, least_crosswalks(crosswalks, memo, index + 1, !side, crossed + 1 + side));
        memo[state] = ret-crossed;
    }
    return ret;
}


int main()
{
    fast();

    string crosswalks;
    read(crosswalks);

    map<p2, int> memo;
    write(least_crosswalks(crosswalks, memo, 0, 1, 0));

    return 0;
}
