#include <bits/stdc++.h>

using namespace std;
#define rep(i,n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef pair<int, int> p2;
int main()
{
    cin.tie(NULL);

    int n;
    cin >> n;

    vi row1(n);
    rep(i, n) cin >> row1[i];
    vi row2(n);
    rep(i, n) cin >> row2[i];
    set<int> unique;
    rep(i, n) unique.insert(row1[i]);
    rep(i, n) unique.insert(row2[i]);
    unique.insert(0);
    unordered_map<int, int> reduce;
    vi redo;
    for (auto& v : unique)
    {
        reduce[v] = reduce.size();
        redo.push_back(v);
    }
    rep(i, n)
    {
        row1[i] = reduce[row1[i]];
    }
    rep(i, n)
    {
        row2[i] = reduce[row2[i]];
    }
    vector<p2> where(n + 1, p2(-1, -1));

    rep(i, n)
    {
        if (where[row1[i]].first == -1) where[row1[i]].first = 0;
        else where[row1[i]].second = 0;
    }
    rep(i, n)
    {
        if (where[row2[i]].first == -1) where[row2[i]].first = 1;
        else where[row2[i]].second = 1;
    }

    int lo = -1;
    rep(i, n)
    {
        if (where[i].first != where[i].second)
        {
            lo = max(lo, i);
        }
    }

    lo = -1;
    int hi = n;
    int HIGH = int(1e6 + 10);
    vi rrow1(HIGH);
    vi rrow2(HIGH);
    int sz1 = 0;
    int sz2 = 0;
    while (lo + 1 < hi)
    {
        sz1 = 0;
        sz2 = 0;
        int mid = (lo + hi) / 2;

        rep(i, n) if (row1[i] > mid) rrow1[sz1++] = (row1[i]);
        rep(i, n) if (row2[i] > mid) rrow2[sz2++] = (row2[i]);
        bool works = 1;
        works &= sz1 % 2 == 0;
        works &= sz2 % 2 == 0;
        if (works)
        {
            for (int i = 0; i < sz1; i += 2)
            {
                works &= rrow1[i] == rrow1[i + 1];
                if (!works) break;
            }
            for (int i = 0; i < sz2; i += 2)
            {
                works &= rrow2[i] == rrow2[i + 1];
                if (!works) break;
            }
        }
        if (works)
        {
            hi = mid;
        }
        else lo = mid;
    }

    cout << redo[hi];


}