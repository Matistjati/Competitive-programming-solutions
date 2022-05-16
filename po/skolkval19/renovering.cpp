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

int main()
{
    fast();

    int n;
    int m;
    read(n);
    read(m);
    vector<int> nails;
    vector<int> nailsNeeded;
    rep(i, n)
    {
        readpush(int, nailsNeeded);
    }
    rep(i, m)
    {
        readpush(int, nails);
    }


    sort(nails.begin(), nails.end());
    sort(nailsNeeded.rbegin(), nailsNeeded.rend());

    rep(i, nailsNeeded.size())
    {
        int nail = nailsNeeded[i];
        auto it_smallest = lower_bound(nails.begin(), nails.end(), nail);
        if (it_smallest == nails.end())
        {
            continue;
        }
        nails.erase(it_smallest);
        nailsNeeded.erase(next(nailsNeeded.begin(),i));
        i--;
    }

    sort(nailsNeeded.begin(), nailsNeeded.end());
    write(nailsNeeded.size());

    rep(i, nailsNeeded.size())
    {
        cout << nailsNeeded[i] << " ";
    }

    return 0;
}