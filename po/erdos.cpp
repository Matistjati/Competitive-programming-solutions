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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}



int main()
{
    fast();

    int n;
    int m;
    read(n);
    read(m);

    vector<vector<string>> publications;

    map<string, set<string>> neighbours;
    rep(i, m)
    {
        int k;
        read(k);
        vector<string> authors;
        rep(i, k)
        {
            readpush(string, authors);
        }
        repe(a, authors)
        {
            repe(b, authors)
            {
                if (!setcontains(neighbours, a))
                {
                    neighbours[a] = {};
                }
                if (!setcontains(neighbours, b))
                {
                    neighbours[b] = {};
                }
                neighbours[a].insert(b);
                neighbours[b].insert(a);
            }
        }
    }

    map<string, int> scientists;

    queue<pair<string, int>> toDo;
    toDo.push({ "ERDOS",0 });

    while (toDo.size())
    {
        pair<string, int> curr = toDo.front();
        toDo.pop();

        if (setcontains(scientists, curr.first))
        {
            continue;
        }
        else
        {
            scientists[curr.first] = curr.second;
        }


        repe(con, neighbours[curr.first])
        {
            toDo.push({ con,curr.second + 1 });
        }
    }




    repe(author, scientists)
    {
        cout << author.first << " " << author.second << "\n";
    }


    return 0;
}