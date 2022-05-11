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

#define p2 pair<int, int>
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

p2 shortest(map<int, set<p2>>& edges, int start, int n)
{
    vector<int> d(n+1, inf);
    d[start] = 0;

    priority_queue<p2> pq;
    pq.push({ 0,start });

    set<int> visited;

    while (pq.size())
    {
        p2 curr = pq.top();
        pq.pop();

        visited.insert(curr.second);

        repe(edge, edges[curr.second])
        {
            if (!setcontains(visited, edge.second))
            {
                int old_cost = d[edge.second];
                int new_cost = edge.first + d[curr.second];
                if (new_cost < old_cost)
                {
                    pq.push({ -new_cost ,edge.second });
                    d[edge.second] = new_cost;
                }
            }
        }

    }

    d[0] = -1;
    auto it = max_element(d.begin(), d.end());
    return {it-d.begin(),*it};
}

int main()
{
    fast();

    int n;
    int v;
    read(n);
    read(v);

    map<int, set<p2>> edges;
    rep(i, v)
    {
        int houseA;
        int houseB;
        int length;
        read(houseA);
        read(houseB);
        read(length);

        if (!setcontains(edges, houseA))
        {
            edges[houseA] = set<p2>();
        }
        if (!setcontains(edges, houseB))
        {
            edges[houseB] = set<p2>();
        }
        edges[houseA].insert({ length, houseB });
        edges[houseB].insert({ length, houseA });
    }

    int longest = -1;
    int a = -1;
    int b = -1;

    for (int i = 1; i < n + 1; i++)
    {
        p2 dist = shortest(edges, i, n);
        if (dist.second > longest)
        {
            a = i;
            b = dist.first;
            longest = dist.second;
        }
    }
    cout << a << " " << b << " " << longest*100;


    return 0;
}