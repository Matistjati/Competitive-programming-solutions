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

bool check(int n, p3 holes, vi correct)
{
    vi beavers;
    for (int i = n; i >= 1; i--)
    {
        beavers.push_back(i);
    }

    stack<ll> holed;

    int minI = beavers.size() - get<0>(holes);
    for (int i = beavers.size() - 1; i >= minI; i--)
    {
        holed.push(beavers[i]);
        beavers.resize(beavers.size()-1);
    }

    while (holed.size())
    {
        int v = holed.top();
        holed.pop();
        beavers.insert(beavers.begin(), v);
    }

    //
    minI = beavers.size() - get<1>(holes);
    for (int i = beavers.size() - 1; i >= minI; i--)
    {
        holed.push(beavers[i]);
        beavers.resize(beavers.size() - 1);
    }

    while (holed.size())
    {
        int v = holed.top();
        holed.pop();
        beavers.insert(beavers.begin(), v);
    }

    //
    minI = beavers.size() - get<2>(holes);
    for (int i = beavers.size() - 1; i >= minI; i--)
    {
        holed.push(beavers[i]);
        beavers.resize(beavers.size() - 1);
    }

    while (holed.size())
    {
        int v = holed.top();
        holed.pop();
        beavers.insert(beavers.begin(), v);
    }


    return beavers == correct;
}

int main()
{
    fast();

    int n;
    read(n);

    vi correct;
    rep(i, n)
    {
        readpush(int, correct);
    }


    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            for (int k = 1; k < n; k++)
            {
                if (check(n, { i,j,k }, correct))
                {
                    cout << i << " " << j << " " << k;
                    return 0;
                }
            }
        }
    }

    return 0;
}