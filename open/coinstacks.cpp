#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(ind, hi) for(int ind = 0;ind<hi;ind++)


int main()
{
    int n;
    cin >> n;

    priority_queue<pair<int, int>> stacks;
    rep(i, n)
    {
        int k;
        cin >> k;
        if (k == 0) continue;
        stacks.push({ k,i });
    }

    vector<pair<int, int>> ans;
    while (stacks.size() > 1)
    {
        auto a = stacks.top();
        stacks.pop();
        auto b = stacks.top();
        stacks.pop();
        ans.push_back({ a.second,b.second });
        if (a.first > 1) stacks.push({ a.first - 1,a.second });
        if (b.first > 1) stacks.push({ b.first - 1,b.second });
    }

    if (stacks.size() > 0)
    {
        cout << "no";
    }
    else
    {
        cout << "yes\n";
        for (auto m : ans) cout << m.first + 1 << " " << m.second + 1 << "\n";
    }

    return 0;
}
