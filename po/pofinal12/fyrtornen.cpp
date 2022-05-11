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

vector<vector<int>*> xSort(300001, nullptr);
vector<vector<int>*> ySort(300001, nullptr);
vector<int> ans(300001, 0);
vector<unordered_set<int>> neighbours(500001, unordered_set<int>());
vector<int> groups(500001, -1);

int dfs(vector<unordered_set<int>>& neighbours, vector<int>& seen, int c, int color)
{
    if (seen[c] != -1)
    {
        return 0;
    }
    else
    {
        seen[c] = color;
    }

    int ret = 1;
    repe(neighbour, neighbours[c])
    {
        ret += dfs(neighbours, seen, neighbour, color);
    }
    return ret;
}



int main()
{
    fast();

    int n;
    int m;
    int k;
    read(n);
    read(m);
    read(k);

    rep(i, m)
    {
        int x;
        int y;
        cin >> x;
        cin >> y;

        if (xSort[x] != nullptr)
        {
            xSort[x]->push_back(i);
        }
        else
        {
            xSort[x] = new vector<int>({ int(i) });
        }

        if (ySort[y] != nullptr)
        {
            ySort[y]->push_back(i);
        }
        else
        {
            ySort[y] = new vector<int>({ int(i) });
        }
    }







    int curr = -1;
    repe(i, xSort)
    {
        if (i != nullptr)
        {
            repe(a, *i)
            {
                repe(b, *i)
                {
                    if (a==b)
                    {
                        continue;
                    }
                    neighbours[a].insert(b);
                    neighbours[b].insert(a);
                }
            }
        }
    }

    repe(i, ySort)
    {
        if (i != nullptr)
        {
            repe(a, *i)
            {
                repe(b, *i)
                {
                    if (a == b)
                    {
                        continue;
                    }
                    neighbours[a].insert(b);
                    neighbours[b].insert(a);
                }
            }
        }
    }


    rep(n, neighbours.size())
    {
        if (groups[n] != -1)
        {
            continue;
        }
        int size = dfs(neighbours, groups, n, n);
        if (size != -1)
        {
            ans[size]++;
        }
    }



    int s = 0;
    per(i, 300000)
    {
        if (ans[i] != 0)
        {
            int l = min(ans[i],k);
            s += (l)*i;
            k-=l;
            if (k == 0)
            {
                break;
            }
        }
    }

    write(s);

    return 0;
}