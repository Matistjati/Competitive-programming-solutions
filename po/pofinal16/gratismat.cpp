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

int n_can_buy(map<int, set<int>>& edges, vector<bool>& table, vector<bool>& visited, int node)
{
    if (table[node])
    {
        return 1;
    }
    if (visited[node])
    {
        return 0;
    }
    else
    {
        visited[node] = true;
    }

    int ret = 0;

    repe(edge,edges[node])
    {
        ret += n_can_buy(edges, table, visited, edge);
    }

    return ret;
}

int main()
{
    fast();

    int n;
    int m;
    read(n);
    read(m);

    map<int, set<int>> connections;
    vector<bool> employees(n+1);
    int start = -1;
    rep(i, n)
    {
        int temp;
        read(temp);
        temp--;
        if (temp == -1)
        {
            start = i;
            continue;
        }
        if (!setcontains(connections,temp))
        {
            connections[temp] = {};
        }
        if (!setcontains(connections,i))
        {
            connections[i] = {};
        }

        connections[temp].insert(i);
        connections[i].insert(temp);
    }
    rep(i, m)
    {
        int temp;
        read(temp);
        temp--;
        employees[temp] = 1;
    }

    vector<bool> visited(n+1);
    write(n_can_buy(connections, employees, visited, start));

    return 0;
}