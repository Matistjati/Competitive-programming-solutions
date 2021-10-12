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



ll m;
ll n;

ll dp(ll layer, ll open, vector<vector<ll>>& states, map<p2, ll>& memo)
{
    if (layer == n)
    {
        return open > 0;
    }

    ll ret = 0;

    rep(i, m)
    {
        ll newOpen = open & states[layer][i];
        p2 state = { layer,newOpen };
        if (setcontains(memo, state))
        {
            ret += memo[state];
        }
        else
        {
            ll n = dp(layer + 1, open & states[layer][i], states, memo);
            memo[state] = n;
            ret += n;
        }

    }

    return ret;
}

int main()
{
    fast();

    read(n);
    read(m);

    vector<string> lock;
    vector<vector<ll>> states;
    states.resize(n, vector<ll>());

    rep(i, n)
    {
        string row;
        read(row);
        lock.push_back(row);
    }


    rep(i, n)
    {
        string s = lock[i];

        rep(k, m)
        {
            ll open = 0;
            rep(j, s.size())
            {
                if (s[j]=='.')
                {
                    open += 1 << j;
                }
            }
            states[i].push_back(open);
            std::rotate(s.begin(), s.begin() + 1, s.end());
        }

    }

    ll ans = 0;

    map<p2, ll> memo;
    ans += dp(0, pow(2,30)-1, states, memo);
    write(ans);

    return 0;
}