#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <iterator>
#include <queue>

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define notsetcontains(set, x) set.find(x) == set.end()

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto const& i : container)
#define inf 1e9

bool answer(map<int, set<int>>& tree, int curr, int many, set<int>& ans, set<int>& visited, set<int>& nuts)
{
    bool yes = false;
    if (setcontains(nuts, curr))
    {
        nuts.erase(curr);
        yes = true;
        ans.insert(curr);
    }


    int minAns = 0;

    repe(branch, tree[curr])
    {
        if (!setcontains(visited, branch))
        {
            visited.insert(branch);
            if (answer(tree, branch, many + 1, ans, visited, nuts))
            {
                yes = true;
                ans.insert(curr);
            }
        }
    }

    return yes;
}

int main()
{

    int n, k;
    read(n);
    read(k);

    set<int> nuts;
    map<int, set<int>> tree;

    rep(i, k)
    {
        readinsert(int, nuts);
    }

    rep(i, n-1)
    {
        int a;
        int b;
        read(a);
        read(b);
        if (!setcontains(tree, a))
        {
            tree[a] = set<int>();
        }
        tree[a].insert(b);
        if (!setcontains(tree, b))
        {
            tree[b] = set<int>();
        }
        tree[b].insert(a);
    }

    set<int> visited;
    visited.insert(1);
    set<int> ans = set<int>();
    (answer(tree, 1, 0, ans, visited, nuts));
    write((ans.size()-1)*2);

}