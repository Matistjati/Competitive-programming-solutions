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
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define inf 2e9

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
    read(n);

    queue<int> in;
    rep(i, n)
    {
        in.push(i+1);
    }

    stack<int> stick;

    vector<int> order;
    int i = 0;
    rep(i, n)
    {
        readpush(int, order);
    }

    while (in.size())
    {
        while (stick.size() && stick.top()==order[i])
        {
            i++;
            stick.pop();
        }
        stick.push(in.front());
        in.pop();

    }

    while (stick.size() && stick.top() == order[i])
    {
        i++;
        stick.pop();
    }

    if (i == n)
    {
        write("JA");
    }
    else
    {
        write("NEJ");
    }


    return 0;
}